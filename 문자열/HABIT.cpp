#include <iostream>
#include <string>
using namespace std;
// 연설문의 부분 문자열 중, K 번 이상 출현한 것들 중에 가장 긴 말버릇의 길이 구하기
/**
 * 1. suffix array 를 만든다.
 * 2. suffix array 원소의 접두사들이 부분 문자열이다.
 * 3. 이 부분문자열들을 전부 구한 후, 각 부분문자열의 출현 횟수를 보면서 K 번 이상인 것들 중 길이가 더 큰 것을 구해서 최대값을 구한다.
 * arr[i]: 부분분자열끼리 비교했을 때 i번째 문자가 같을때 최대 횟수
 * 겹치는게 없을 때 global 로 저장하고 새거 만들어 저장
 * 각 그룹 끝날 때 기존 global 과 비교해서 더 크면 저장
 * K 번이상 등장한 문자열 중 최대길이를 구하는거니까 교체 규칙은 저 최대길이가 기준임. 
*/

int K;
string script;

int getCommonPrefixSize(const string& s, int idx1, int idx2) {
    int cp = 0;
    while (idx1 < s.size() && idx2 < s.size() && s[idx1] == s[idx2]) {
        ++idx1;
        ++idx2;
        ++cp;
    }
    return cp;
}

struct Comparator {
    const vector<int>& group;
    int t;
    Comparator(const vector<int>& _group, int _t) : group(_group), t(_t) {}    
    bool operator () (int idx1, int idx2) { // string에서 idx1에서 시작하는 접미사가 속한 그룹과 idx2에서 시작하는 접미사가 속한 그룹 비교 
        if (group[idx1] != group[idx2]) return group[idx1] < group[idx2]; // 다른 그룹이면 그룹번호로 간단히 정렬 가능
        // 같은 그룹이면, 각각 t만큼 뒤에 있는 접미사가 속해 있는 그룹끼리 비교하면 된다.
        // 왜냐하면, 0~t 까지는 위 조건을 통해 같고, t~2t 는 이미 구했었으므로, 아래 조건에서 idx1 + t, idx2 + t 가 속한 그룹의 크기는 t 이고 이걸 사용하면 logN 회만 수행하면 된다.
        return group[idx1 + t] < group[idx2 + t];  
    }
};

// 접미사 사전순 정렬했을 때 각 접미사의 시작 인덱스가 담기는 vector 리턴
vector<int> getSuffixArray(const string& s) {
    int n = s.size();
    int t = 1;
    vector<int> group(n + 1);
    for (int i = 0; i < n; ++i) {
        group[i] = s[i];
    } 
    group[n] = -1;
    vector<int> ret(n);    
    // 일단 무정렬 상태로 만든다.
    for (int i = 0; i < n; ++i) {
        ret[i] = i;
    }
    while (t < n) {
        // 비교자 생성
        Comparator comp(group, t);
        // 정렬
        sort(ret.begin(), ret.end(), comp);        

        t *= 2;
        // 새 그룹 생성
        vector<int> new_group(n + 1, 0);
        new_group[n] = -1;
        new_group[ret[0]] = 0;
        for (int i = 1; i < n; ++i) {
            if (comp(ret[i - 1], ret[i])) { // ret[i-1]는 ret[i] 보다 앞에 있어야 한다. 즉 다른 그룹이다.
                new_group[ret[i]] = new_group[ret[i - 1]] + 1;
            } else { // ret[i-1] 은 ret[i] 앞에 있을 필요 없다. 즉 같은 그룹이다.
                new_group[ret[i]] = new_group[ret[i - 1]];
            }
        }
        group = new_group;
    }
    return ret;
}

vector<int> answer;

int main() {
    int C;
    cin >> C;
    while (C--) {
        cin >> K;
        cin >> script;

        vector<int> suffix_array = getSuffixArray(script);
        // for (int i = 0; i < suffix_array.size(); ++i) {
        //     cout << script.substr(suffix_array[i]) << endl;
        // }
        // common prefix 크기 구해서 K보다 크면 K~common prefix size 까지 +1 해준다.
        // key:size, value:cnt
        unordered_map<int, int> um1;
        unordered_map<int, int> um2;
        int maxval_prev = 0;
        um2[1] = 1;
        for (int i = 1; i < suffix_array.size(); ++i) {
            // cout << maxval_prev << " " << endl;
            int cp_size = getCommonPrefixSize(script, suffix_array[i - 1], suffix_array[i]);
            // // cout << cp_size << " " << endl;

            if (um2.find(script.size() - suffix_array[i]) == um2.end()) {
                um2[script.size() - suffix_array[i]] = 1;
            }
            
            if (cp_size == 0) { // 다른 그룹. 교체 필요시 교체(um2를 um1에 할당하고 새 um2 생성)
                // 교체가 필요하다는건 더 좋은 조건 -> K 번 이상 등장한 부분 문자열 최고 길이가 더 김.
                int maxval = -1;

                for (auto it = um2.begin(); it != um2.end(); ++it) {
                    // cout << it->first << " " << it->second << endl;
                    if (it->second >= K) {
                        maxval = max(maxval, it->first);
                    }
                }
                if (maxval_prev < maxval) {
                    maxval_prev = maxval;
                    um1 = um2;
                    
                    um2 = unordered_map<int, int>();

                    // if (um2.find(script.size() - suffix_array[i]) == um2.end()) {
                    //     um2[script.size() - suffix_array[i]] = 1;
                    // }
                }

            }
            else { // 같은 그룹
                for (int j = 1; j <= cp_size; ++j) {
                    if (um2.find(j) == um2.end()) {
                        um2[j] = 1;
                    } else {
                        um2[j] += 1;
                    }
                }
            }
        }

        for (auto it = um2.begin(); it != um2.end(); ++it) {
            if (it->second >= K) {
                maxval_prev = max(maxval_prev, it->first);
            }
        }

        answer.push_back(maxval_prev);
    }
    for (auto& ans : answer) {
        cout << ans << endl;
    }
}
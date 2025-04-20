/**
 * <suffix array>
 * suffix array 한 문자열로 만들 수 있는 모든 접미사를 사전순으로 정렬한 배열이다.
 * 단순하게 본다면, 각 문자: O(N), 부분문자열 생성: O(N), 정렬: O(N^2logN) => 총 O(N^2 + N^2logN) 
 * 
 * suffix array 로 할 수 있는 것
 * 문자열 B가 문자열 A 에 있는지 찾을 때 O(BlogA) 로 찾을 수 있다.
 * KMP 는 O(A + B) 였다. A+B<BlogA -> A<B(logA-1) A/B<logA-1, 일반적으로 B가 더 크므로 좌변은 0.xx이다. 1 이동하면 1.xx < logA, A 는 10^1.xx 이상이어야 suffix array 사용하는게 이득
 * 
 * suffix array 구하는 법
 * group size 를 1->2->4->8->16->... 이런식으로 2배씩 증가시키면서 그룹을 나누면서 정렬한다.
 * 매순간 newgroup 을 생성하고, t 를 2배씩 증가시키면서 확인한다.
 * group index 기반으로 사전순서를 평가한다.
 * 아 정렬을 직접 수행한다. 정렬은 group 값을 기준으로 수행한다. 별도의 비교함수를 만들어서.
 * O(NlogN) 필요하다. 근데 t*=2 로 되므로 전체 시행횟수는 logN 이므로 총 시간복잡도=O(Nlog^2(N)) 이 된다.
 * newgroup 생성받법은 a+t 했을 때의 group 값을 기준으로 같으면 같은 그룹이고, 다르면 새 그룹번호를 배정해준다.
*/

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

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


int main() {
    string str = "helloworld";
    vector<int> ret = getSuffixArray(str);
    for (auto& idx : ret) {
        cout << str.substr(idx) << endl;
    }
}
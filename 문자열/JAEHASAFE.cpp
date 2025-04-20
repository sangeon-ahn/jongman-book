#include <string>
#include <iostream>
#include <vector>
using namespace std;

int N;
vector<string> states;
vector<string> originals;
void init() {
    states = vector<string>();
}

vector<int> getPartialMatches(const string& needle) {
    vector<int> ret(needle.size(), 0);
    int n = needle.size(), matched = 0, begin = 1;

    while (begin + matched < n) {
        // cout << begin << " " << matched << endl;
        if (needle[begin + matched] == needle[matched]) {
            ++matched;
            ret[begin + matched - 1] = matched;
        } else {
            if (matched == 0) {
                ++begin;
            } else {
                begin = begin + matched - ret[matched - 1];
                matched = ret[matched - 1];
            }
        }
    }
    return ret;
}

int kmpSearch(const string& heystack, const string& needle, int dir) {
    int begin = 0, matched = 0;
    int h = heystack.size(), n = needle.size();
    int ret;

    vector<int> pi = getPartialMatches(needle);

    // begin = 0, n = 2, h = 2면
    // needle = [a, b]
    // heystack = [a, b] 라서 한번 검사 가능하니까 < 아니고 <= 해야함
    while (begin + n <= h) {
        if (matched < n && heystack[begin + matched] == needle[matched]) { // 매칭되면 더하기
            ++matched;

            if (matched == n) {
                if (dir == 1) { // 시계방향이면 바로 리턴
                    return begin;
                }
                // 시계 반대방향이면 값 갱신
                ret = begin;
            }
        } else { // 매칭 안됐었으면 이동
            if (matched == 0) {
                ++begin;
            } else {
                begin = begin + matched - pi[matched - 1]; // 인덱스 여기서 begin + matched - 1 이렇게 잘못 넣었었다.
                matched = pi[matched - 1];
            }
        } 
    }
    return (h - ret) - n; // 시계 반대방향인 경우
}

int main() {
    int C;
    cin >> C;
    while (C--) {
        cin >> N;
        string temp;
        int ans = 0;
        for (int i = 0; i < N + 1; ++i) {
            cin >> temp;
            originals.push_back(temp);

            if (i % 2 != 0) { // 시계방향
                temp += temp.substr(0, temp.size() - 1);
            } else { // 시계 반대방향
                temp = temp.substr(1, temp.size() - 1) + temp;
            }
            states.push_back(temp);
        }
        
        // 이제 kmp로 매칭되는거 구하기.
        // 시계방향이면 최소 idx 구해야 하고,
        // 시계 반대방향이면 최대 idx 구해야 함.
        
        for (int i = 1; i < states.size(); ++i) {
            // 시계 방향(홀수)이면 최소 index가 답이고, 시계 반대방향(짝수)이면 최대 index 구한다.
            int val = 0;
            if (i % 2 != 0) {
                val = kmpSearch(states[i], originals[i - 1], 1);
            } else {
                val = kmpSearch(states[i], originals[i - 1], 0);
            }
            // cout << val << endl;
            ans += val;
        }
        cout << ans << endl;
    }
}
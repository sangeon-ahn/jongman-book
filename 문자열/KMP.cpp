/**
 * KMP 알고리즘은 문자열 A에 문자열 B가 속하는지를 빠른 시간복잡도 내에 찾을 수 있게 하는 알고리즘이다.
 * 간단하게 생각해보면, 문자열 A 에서 A[a:b] 문자열이 B인지를 매번 검사하면 B가 A 에 속하는지 알 수 있다.
 * 이는 [0:N] 내의 a에 대해 [1:N]의 b 가 후보가 될 수 있으므로 O(N^2) 의 시간복잡도를 가진다.  
 * KMP 알고리즘이 그래서 뭔가?
 * 문자열 B가 [a, a, d, a, a, d] 이렇게 있으면, [0:0], [0:1], [0:2], ... , [0:5] 이 부분문자열에서 접두사와 접미사가 같을 때 최대 길이를 저장해두었다가, 실제로 A와 B를 대조해볼 때 3번 째 인덱스까지는 똑같고 4번째부터 다르다면, B[0:3] 문자열의 최대 접두사까지 이동시키는 것이다.
 * 이렇게 하면, A 문자 낭비를 최대한 줄이면서 B를 찾을 수 있어서 그리디한 방법으로 찾을 수 있다.
 * 매칭되는게 없다면 한칸 이동하고, 겹치는 문자열에서 접미사 == 접두사 인게 없으면 겹치는 것을 다 점프하므로, 대조하는 로직은 O(N)이다.
 * 최대접두사 길이 구하는 로직은 O(N) 이다. 
*/
// 각 위치에서의 최대 접두사=접미사인 경우의 길이를 구해보자.
#include <string>
#include <vector>
#include <iostream>
using namespace std;

vector<int> getPartialMatch(const string& str) {
    int n = str.size();
    vector<int> ret(n, 0);

    int begin = 1, matched = 0;
    while (begin + matched < n) {
        // 같은지 검사
        // a'a'
        // 'a'a
        if (str[matched] == str[begin + matched]) {
            ++matched;
            ret[begin + matched - 1] = matched; // 인덱스 잘 따져봐야 함.
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

vector<int> kmpSearch(const string& hey, const string& str) {
    int h = hey.size(), n = str.size();
    vector<int> ret;

    vector<int> presuff_maxlen = getPartialMatch(str); // arr[i] = str[...i] 의 최대 접두사==접미사 길이
    
    // begin 은 매칭 시작지점. 
    int begin = 0, matched = 0;
    while (begin <= h - n) { // begin == h-n 이면 그래도 heystack 끝까지 비교하면 1회 매칭여부 확인 가능
        if (matched < n && hey[begin + matched] == str[matched]) { // 문자 일치하면
            ++matched;
        
            // 다 매칭됐으면 결과에 추가해줘야지
            if (matched == n) {
                ret.push_back(begin);
            }
        } else { // 다 매칭됐거나 매칭 안됐으면
            if (matched == 0) { // 하나도 매칭 안됐으면 begin 이동
                ++begin;
            } else { // 몇개 매칭된거 있으면 최대접두사길이 구해서 이동
                begin = begin + matched - presuff_maxlen[matched - 1]; // 길이가 matched 인 문자열에 해당하는 값은 matched-1 인덱스에 위치한다.
                matched = presuff_maxlen[matched - 1];
            }
        }
    }
    return ret;
} 

int main() {
    string heystack = "hellohello";
    string str = "hello";
    vector<int> ret = kmpSearch(heystack, str);
    for (auto& ans : ret) {
        cout << ans << " ";
    }
}


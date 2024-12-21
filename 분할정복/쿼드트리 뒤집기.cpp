#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

// 문제: 압축된 문자열이 입력으로 주어지면 이를 해석해서 쿼드트리 모양 구한 후 상하 뒤집은 쿼드트리의 압축된 문자열을 구해라
// 풀이: 압축된 문자열은 2사->1사->3사->4사 순서로 출력된다. 상하로 뒤집으면 3사->4사->2사->1사 순으로 출력되는 것이다.

int last_char_idx(string& str, int st)
{
    int idx = st;
    int count = 0;

    while (idx < str.size())
    {
        if (str[idx] == 'b' || str[idx] == 'w') {
            ++count;
        } else {
            idx = last_char_idx(str, idx + 1);
            ++count;
        }

        if (count == 4) {
            return idx;
        }

        ++idx;
    }

    return -1;
}

string recur(string& str, int st, int en) // st번째는 무조건 x임.
{
    if (st == en) return str.substr(st, 1);

    // 4개로 나눔(시작, 끝)
    vector<pair<int, int>> sectors; // 0: 2사, 1: 1사, 2: 3사, 3: 4사

    // 4개로 나누기
    int idx = st + 1;

    while (idx <= en)
    {
        if (str[idx] == 'x') {
            int last_idx = last_char_idx(str, idx + 1);
            sectors.push_back(make_pair(idx, last_idx));
            idx = last_idx + 1;
        } else {
            sectors.push_back(make_pair(idx, idx));
            ++idx;
        }
    }

    for (int i = 0; i < sectors.size(); ++i) {
        cout << sectors[i].first << " " << sectors[i].second << endl;
    }

    string result = "x";
    result += recur(str, sectors[2].first, sectors[2].second);
    result += recur(str, sectors[3].first, sectors[3].second);
    result += recur(str, sectors[0].first, sectors[0].second);
    result += recur(str, sectors[1].first, sectors[1].second);

    return result;
}

int main()
{
    int C;
    cin >> C;

    while (C--)
    {
        string s;
        cin >> s;

        if (s.size() == 1) {
            cout << s << endl;
            continue;
        }

        cout << recur(s, 0, s.length() - 1);        
    }
}
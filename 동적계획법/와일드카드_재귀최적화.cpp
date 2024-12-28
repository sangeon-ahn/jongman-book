#include <string>
#include <iostream>
#include <vector>
using namespace std;

int isMatched[101][101];
string W;
string S;
vector<string> answer;

bool canMatch(int wIdx, int sIdx)
{
    int& ret = isMatched[wIdx][sIdx];

    if (ret != -1) return ret;

    if (wIdx < W.size() && sIdx < S.size() && (W[wIdx] == '?' || W[wIdx] == S[sIdx])) {
        return ret = canMatch(wIdx + 1, sIdx + 1);
    }

    if (wIdx == W.size()) {
        return ret = sIdx == S.size();
    }

    if (W[wIdx] == '*') {
        if (canMatch(wIdx + 1, sIdx) || (sIdx < S.size() && canMatch(wIdx, sIdx + 1))) {
            return ret = 1;
        }
    }

    return ret = 0;
}

void initialize()
{
    for (int i = 0; i < 101; ++i) {
        for (int j = 0; j < 101; ++j) {
            isMatched[i][j] = -1;
        }
    }
}

int main()
{
    int C;
    cin >> C;
    while (C--)
    {
        cin >> W;

        int n;
        cin >> n;

        for (int i = 0; i < n; ++i) {
            cin >> S;

            initialize();

            if (canMatch(0, 0)) {
                answer.push_back(S);
            }
        }
    }

    for (string s : answer) {
        cout << s << endl;
    }
}
#include <string>
using namespace std;

int isMatched[101][101];

string W;
string N;

bool canMatch(int cardIdx, int nameIdx)
{
    int w = cardIdx;
    int n = nameIdx;

    int& ret = isMatched[w][n];

    if (ret != 1) return ret;

    while (w < W.size() && n < N.size() && (W[w] == '?' || W[w] == N[n])) {
        ++w;
        ++n;
    }

    if (w == W.size()) {
        ret = w == N.size();
        return ret = (n == N.size());
    }

    if (W[w] == '*') {
        for (int jump = 0; n + jump <= N.size(); ++jump) {
            if (canMatch(w + 1, n + jump)) {
                return ret = 1;
            }
        }
    }
    
    return ret = 0;
}
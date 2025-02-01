#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
const int MOD = 1000000007;

string e, digits;
int n;
int m;
int cached[1<<14][20][2];

void init()
{
    n = e.size();
    digits = e;
    sort(digits.begin(), digits.end());
    for (int i = 0; i < 1<<14; ++i) {
        for (int j = 0; j < 20; ++j) {
            for (int k = 0; k < 2; ++k) {
                cached[i][j][k] = -1;
            }
        }
    }
}

// (cnt: 사용된 숫자 개수, usedBits: 사용된 숫자 비트on off, remained: 누적 나머지, less: 원본보다 작은지 여부)
int zimba(int cnt, int usedBits, int remained, int less)
{
    if (cnt == n) {
        if (remained == 0 && less) return 1;
        return 0;
    }

    int& res = cached[usedBits][remained][less];

    if (res != -1) return res;

    res = 0;

    for (int i = 0; i < n; ++i) {
        if ((usedBits & (1<<i)) != 0) continue;
        if (!less && e[cnt] < digits[i]) continue;
        if (0 < i && digits[i - 1] == digits[i] && (usedBits & (1<<(i-1)) == 0)) continue;

        int nextUsedBits = usedBits | (1<<i);
        int nextRemained = (remained * 10 + (digits[i] - '0')) % m;
        int nextLess = less || e[cnt] > digits[i]; 
        res += zimba(cnt + 1, nextUsedBits, nextRemained, nextLess);
        res %= MOD;
    }

    return res;
}


int main()
{
    int C;
    cin >> C;
    while (C--)
    {
        cin >> e >> m;

        init();  

        cout << zimba(0, 0, 0, 0);
    }
}
#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1000000007;
vector<int> answers;
int cache[101];

int tiling(int n)
{
    if (n <= 1) return 1;
    int& res = cache[n];
    if (res != -1) return res;
    return res = (tiling(n - 1) + tiling(n - 2)) % MOD;
}

int asymTiling(int n)
{
    if (n <= 2) return 0;

    int res;
    if (n % 2 == 0) {
        res = ((tiling(n) - tiling(n / 2) + MOD) % MOD - tiling((n / 2) - 1) + MOD) % MOD;
    } else {
      res = (tiling(n) - tiling(n / 2) + MOD) % MOD;  
    }

    return res;
}

void init()
{
    for (int i = 0; i < 101; ++i) {
        cache[i] = -1;
    }
}

int main()
{
    int C;
    cin >> C;

    int n;
    while (C--)
    {
        cin >> n;

        init();

        answers.push_back(asymTiling(n));
    }

    for (int ans : answers) {
        cout << ans << endl;
    }
}
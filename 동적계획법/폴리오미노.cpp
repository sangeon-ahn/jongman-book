#include <iostream>
#include <vector>
using namespace std;

const int MOD = 10000000;
vector<int> answers;
int cache[101][101];

int polyomino(int prev, int remained, bool start)
{
    int& cached = cache[prev][remained];
    if (cached != -1) return cached;

    // size: // 조각의 크기
    int res = 0;
    for (int size = 1; size <= remained; ++size) {
        if (start) {
            res = (res + polyomino(size, remained - size, false)) % MOD;  
        } else {
            res = (res + (prev + size - 1) * polyomino(size, remained - size, false)) % MOD;
        }
    } 

    return cached = res;
}

void init()
{
    for (int i = 0; i < 101; ++i) {
        for (int j = 0; j < 101; ++j) {
            cache[i][j] = -1;
        }
        cache[i][0] = 1;
    }
}

int main()
{
    int C;
    cin >> C;
    answers = vector<int>();

    while (C--)
    {
        int n;
        cin >> n;
        init();

        answers.push_back(polyomino(1, n, true));
    }

    for (int ans : answers) {
        cout << ans << endl;
    }
}
#include <iostream>
using namespace std;
// O(n^2*k)
int n, k, m;

double dp[51][5]; // dp[i][j]: 노래 i가 j 위치에서 끝날 확률. dp[i][j] = dp[i][j-running_times[i]]*props[i][i] + dp[a][j-running_times[a]]*props[a][i] + dp[b]...
int running_times[51];
double props[51][51];
int favorites[11];

void genius()
{
    for (int time = running_times[0] + 1; time < k + 5; ++time) {
        for (int i = 0; i < n; ++i) {
            double val = 0.0;
            for (int j = 0; j < n; ++j) {
                val += dp[j][(time - running_times[i]) % 5] * props[j][i];
            }
            dp[i][time % 5] = val;
        }
    }
}

void init()
{
    for (int i = 0; i < 51; ++i) {
        for (int j = 0; j < 5; ++j) {
            dp[i][j] = 0;
        }
    }
    dp[0][running_times[0]] = 1;
}

int main()
{
    int C;
    cin >> C;
    while (C--)
    {
        cin >> n >> k >> m;
        
        int running_time;
        for (int i = 0; i < n; ++i) {
            cin >> running_time;
            running_times[i] = running_time;
        }
        double prop;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> prop;
                props[i][j] = prop;
            }
        }
        int fav;
        for (int i = 0; i < n; ++i) {
            cin >> fav;
            favorites[i] = fav;
        }
        
        init();
        genius();
        
        for (int i = 0; i < m; ++i) {
            double res = 0.0;
            for (int j = 1; j <= running_times[favorites[i]]; ++j) {
                res += dp[favorites[i]][(k + j)%5];
            }
            cout << res << " ";
        }
        cout << endl;
    }
}
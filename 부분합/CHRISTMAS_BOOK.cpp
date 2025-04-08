#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

int N, K;
int dolls[100002];
int acc_sum[100002]; // acc_sum[i]: dolls[1] ~ dolls[i] 까지 다 더한걸 K 로 나눈 나머지
int ans1 = 0;
int ans2 = 0;
int last_idxes[100002];
int dp[100002];

unordered_map<int, int> div_map;
void init() {
    dolls[0] = 0;
    acc_sum[0] = 0;
    ans1 = ans2 = 0;
    div_map = unordered_map<int, int>();
}

int main() {
    int C;
    cin >> C;
    while (C--) {
        init();
        cin >> N >> K;
        int D;
        for (int i = 1; i <= N; ++i) {
            cin >> D;
            dolls[i] = D;
        }

        for (int i = 1; i <= N; ++i) {
            acc_sum[i] = (acc_sum[i - 1] + dolls[i]) % K;
            if (div_map.find(acc_sum[i]) == div_map.end()) {
                div_map[acc_sum[i]] = 1;
            } else {
                div_map[acc_sum[i]]++;
            }
        }


        for (auto it = div_map.begin(); it != div_map.end(); ++it) {
            ans1 += it->second * (it->second - 1) / 2;
        }
        if (div_map.find(0) != div_map.end()) {
            ans1 += div_map[0];
        }

        cout << ans1 << endl;

        for (int i = 0; i <= K; ++i) {
            last_idxes[i] = -1;
        }

        // i 번째 상자를 사는 경우, 안 사는 경우로 나눈다.
        // 사는 경우는 이전에 해당 나머지값이 등장했어야 살 수 있다.
        // 안사는 경우는 그 전 상자까지의 범위였을 때 값을 취한다.
        for (int i = 0; i <= N; ++i) {
            if (i == 0) {
               dp[i] = 0; 
            } else {
                dp[i] = dp[i - 1]; // 안 사는 경우
                
                if (acc_sum[i] == 0) {
                    dp[i] = max(dp[i], dp[i - 1] + 1);
                } else if (last_idxes[acc_sum[i]] != -1) {
                    dp[i] = max(dp[i], dp[last_idxes[acc_sum[i]] - 1] + 1);
                }

                last_idxes[acc_sum[i]] = i;
            }
        }

        cout << dp[N] << endl;
    }
}
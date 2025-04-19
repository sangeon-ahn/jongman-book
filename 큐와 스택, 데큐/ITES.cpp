#include <iostream>
using namespace std;

int N, K;
const int WINDOW_SIZE = 5000001;
long long signals[5000001];
int input_signals[5000001];

void gen_signal(int idx) {    
    signals[(WINDOW_SIZE + idx) % WINDOW_SIZE] = (signals[(WINDOW_SIZE + idx - 1) % WINDOW_SIZE] * 214013 + 2531011) % ((long long)1<<32);
    input_signals[(WINDOW_SIZE + idx) % WINDOW_SIZE] = signals[(WINDOW_SIZE + idx - 1) % WINDOW_SIZE] % 10000 + 1;
}

void init() {
    for (int i = 0; i < 5000001; ++i) {
        signals[i] = input_signals[i] = 0;
    }
    signals[0] = 1983;
}

int main() {
    int C;
    cin >> C;
    
    while (C--) {
        cin >> K >> N;
        init();

        int p = 1;
        int q = 1;
        int ans = 0;
        gen_signal(1);
        int ssum = input_signals[1];  
        int cnt = 1;

        while (cnt <= N) {            
            while (ssum > K) { // p == q 가 되는 순간 p + 1 == q 가 되고 ssum = 0 이 되어 루프 탈출
                ssum -= input_signals[p];
                p = (p + 1) % WINDOW_SIZE;
            }
            
            if (ssum == K) ++ans;

            // 추가해도 되는 상태
            ++cnt;
            gen_signal(cnt);
            q = (q + 1) % WINDOW_SIZE;
            ssum += input_signals[q];
        }

        cout << ans << endl;
    }
}
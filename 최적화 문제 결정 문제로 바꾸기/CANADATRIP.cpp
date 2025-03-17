#include <iostream>
using namespace std;

int N, K;

int flagCnt[5001];
int dist[5001];
int gap[5001];
int firstFlag[5001];

int cal(int distance) {
    int cnt = 0;
    int idx = 0;
    while (idx < N) {
        if (dist[idx] <= distance) {
            cnt += flagCnt[idx];
        }

        else if (firstFlag[idx] <= distance) {
            cnt += (distance - firstFlag[idx]) / gap[idx] + 1;
        }
        ++idx;
    }

    return cnt;
}

int solve() {
    int st = 0;
    int en = 10000000;

    for (int i = 0; i < 100; ++i) {
        int mid = (st + en) / 2; // mid 거리까지의 푯말 개수 구해야함

        int flagCnt = cal(mid);
        if (flagCnt >= K) {
            en = mid; // mid도 정답 후보에 둘 수 있다.
        } else {
            st = mid; // flagCnt < K 이기 때문에 mid는 정답 후보에 둘 수 없다. 그래도 mid를 대입하면, 어느순간 st == en == mid 가 되고, 이때 st를 답으로 반환하면 된다.
        }
    }
    return en;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> N >> K;
        int L, M, G;
        for (int i = 0; i < N; ++i) {
            cin >> L >> M >> G;
            // 각 도시당 표지판 몇개인지 구하기
            flagCnt[i] = M / G + 1;
            dist[i] = L;
            gap[i] = G;
            firstFlag[i] = L - M; 
        }

        cout << solve() << endl;
    }
}
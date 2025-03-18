#include <iostream>
using namespace std;
/**
 * 1. 20억 게임 중 남은 게임을 모두 이겼을 때 승률이 현재 승률보다 1% 미만이라면 -1 리턴
 * 2. 현재 승률이 90% 이상이면 -1 리턴
 * 3. 그 외의 경우에는 찾아보기
 * 4. 이분탐색 파라미터는 이긴 횟수이다. 전부 이겨도 상관 없기 때문.
 * 5. 이겼을 때 승률 계산하면 됨.
 * 
 * 피드백: 소수점 사칙연산은 정확하지 않을 수 있다. -> 100을 곱한 후 나눴을 때 일의자리 숫자가 바뀌었는지 본다 -> 바뀌었다면 일의자리 퍼센트가 증가한거다.
 */
const long long MAXGAME = 2000000000;
long long N, M;

int ratio(long long b, long long a) {
    return ((b * 100) / a);
}

int solve() {
    long long st = 0;
    long long en = MAXGAME;

    for (int i = 0; i < 100; ++i) {
        long long mid = (st + en) / 2; // mid 만큼 더 이긴다.
        
        if (ratio(M + mid, N + mid) != ratio(M, N)) {
            en = mid;
        } else {
            st = mid;
        }
    }
    return en;
}

int main() {
    int C;
    cin >> C;
    while (C--) {
        cin >> N >> M;

        int best_win_rate = ratio(M + MAXGAME, N + MAXGAME);

        if (best_win_rate != ratio(M, N)) {
            cout << solve() << endl;
        } else {
            cout << -1 << endl;
        }
    }
}
#include <iostream>
#include <queue> // 왜 queue 를 생각하지 못했나? 왜 배열을 이용한 circular queue 를 생각했나? 일단 처음에 투포인터를 생각했기 때문에 자연스럽게 배열을 이용한 풀이법에 국한되게 되었다. 그런데 풀다보니 end는 항상 앞으로만 이동하고 end에 위치한 숫자가 sum 에서 제외되는 경우는 없었다. 그래서 queue 로 first 에 위치한 숫자만 handling하면 되는 문제여서 queue 를 사용하면 공간낭비없이 문제를 풀 수 있다.
// 난수 생성기도 만들어 사용하자.
// 큐에 넣고, K 보다 크면 줄여주고, 이후에 K 와 같은지 검사
// 큐에 넣을 땐 난수 생성기를 통해 값을 구해주기
// 난수 생성기는 별도의 캐싱 없이 seed 기반 생성

struct RNG { // Random Number Generator
    unsigned int seed; // unsigned int 는 4바이트(32bit)이다. 다음 신호 생성할 때 32bit 이후의 값은 무시되고 mode 32 는 32bit 이전의 값들만 취하게 되므로, 타입 자체를 unsigned int 로 하면 32 bit 만 가질 수 있게된다.
    
    RNG() : seed(1983) {}
    unsigned int next() {
        unsigned int ret = seed;

        // 현재 seed 값을 바탕으로 다음 난수를 구한다.
        // 다음 seed 값 구하기
        seed = seed * 214013 + 2531011;
        return ret % 10000 + 1;
    }
};

using namespace std;

int K, N;

int main() {
    int C;
    cin >> C;
    while (C--) {
        cin >> K >> N;

        queue<int> q;              
        RNG rng; // 이렇게만 해줘도 default constructor 호출되면서 다 세팅된다.
        int ssum = 0;
        int cnt = 0;
        int ans = 0;

        while (cnt < N) {
            // 0. 난수 생성
            int signal = rng.next();

            // 1. 넣기
            q.push(signal);
            ssum += signal;
            ++cnt;

            // 2. 줄이기
            while (ssum > K) {
                ssum -= q.front(); q.pop();
            }

            // 3. ssum == K 면 추가
            if (ssum == K) {
                ++ans;
            }
        }       

        cout << ans << endl;
    }
}
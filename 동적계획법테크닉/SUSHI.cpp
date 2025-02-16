#include <iostream>
using namespace std;

int n;
int m;
int prices[21];
int prefs[21];
/**
 * 초밥 최대 가격이 20000원이기 때문에 예산이 20001 이상부터는 0번째 칸은 사용되지 않게된다. 
 * 그래서 캐시공간을 20001만 사용하고 (balance - price) % 20001 한 값을 인덱스로 사용해서 공간을 절약한다.
 * 그리고, 각 가격은 100의 배수이기 때문에 일의자리, 십의자리는 제외해도 된다.
 * 따라서 최대 가격을 200으로 줄이면 % 201를 하면 된다.
 **/
int cache[201];

int sushi1(int m)
{
    int& ret = cache[m];
    if (ret != -1) return ret;

    for (int i = 0; i < n; ++i) {
        if (m < prices[i]) continue;
        ret = max(ret, sushi1(m - prices[i]) + prefs[i]);
    }

    return ret;
}

int sushi2()
{
    int ret = 0;
    for (int balance = 1; balance <= m; ++balance) {
        cache[balance] = 0;
        for (int i = 0; i < n; ++i) {
            if (balance < prices[i]) continue;
            ret = max(ret, cache[balance - prices[i]] + prefs[i]);
        }
    }

    return ret;
}

int sushi3()
{
    int ret = 0;
    cache[0] = 0;
    for (int balance = 1; balance <= m; ++balance) {
        int cand = 0;
        for (int i = 0; i < n; ++i) {
            if (balance < prices[i]) continue;
            cand = max(cand, cache[(balance - prices[i])%201] + prefs[i]);
        }
        cache[balance % 201] = cand;
        ret = max(ret, cand);
    }

    return ret;
}

void init()
{
    for (int i = 0; i < 201; ++i) {
        cache[i] = -1;
    }
}

int main()
{
    int C;
    cin >> C;
    while (C--)
    {
        // init();

        cin >> n >> m;
        m /= 100;
        int price;
        int pref;
        for (int i = 0; i < n; ++i) {
            cin >> price >> pref;
            prices[i] = price / 100;
            prefs[i] = pref;
        }

        int res = sushi3(); // 이 예산 가지고 얻을 수 있는 최대 선호도
        cout << res << endl;
    }
}
// 
// #include <iostream>
// using namespace std;
// 
// int n, m, price[20], pref[20];
// int c[201];
// 
// int sushi3() {
    // int ret = 0;
    // c[0] = 0;
    // for (int budget = 1; budget <= m; ++budget) {
        // int cand = 0;
        // for (int dish = 0; dish < n; ++dish) {
            // if (budget >= price[dish]) {
                // cand = max(cand, c[(budget - price[dish])%201] + pref[dish]);
            // }
        // }
        // c[budget % 201] = cand;
        // ret = max(ret, cand);
    // }
    // return ret;
// }
// 
// int main()
// {
    // int C;
    // cin >> C;
    // cin >> n >> m;
    // m /= 100;
    // int pr;
    // int pre;
    // for (int i = 0; i < n; ++i) {
        // cin >> pr >> pre;
        // price[i] = pr / 100;
        // pref[i] = pre;
    // }
// 
    // cout << sushi3();
// }
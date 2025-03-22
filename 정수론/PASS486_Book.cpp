#include <iostream>
#include <cmath>
#include <unordered_map>
using namespace std;

int min_factor[10000001];
int min_factor_cnt[10000001];
int factor_cnt[10000001];
int n, lo, hi;

void getMinFactor() {
    for (int i = 0; i <= hi; ++i) {
        min_factor[i] = i;
    }

    int barrier = int(sqrt(hi));
    for (int i = 2; i <= barrier; ++i) {
        if (min_factor[i] == i) {
            for (int j = i * i; j <= hi; j += i) {
                if (min_factor[j] == j) {
                    min_factor[j] = i;
                }
            }
        }
    }
}

void getFactorCnt() {
    min_factor_cnt[1] = min_factor_cnt[2] = 1;
    factor_cnt[1] = 1;
    factor_cnt[2] = 2;

    for (int num = 3; num <= hi; ++num) {
        int val = num / min_factor[num];

        if (val % min_factor[num] == 0) {
            min_factor_cnt[num] = min_factor_cnt[val] + 1;
        } else {
            min_factor_cnt[num] = 1;
        }

        factor_cnt[num] = (factor_cnt[val] * (min_factor_cnt[num] + 1)) / min_factor_cnt[num];
    }
}

int main() {
    int C;
    cin >> C;
    while (C--) {
        cin >> n >> lo >> hi;
     
        getMinFactor();
        getFactorCnt();

        int ret = 0;
        for (int num = lo; num <= hi; ++num) {
            if (factor_cnt[num] == n) ++ret;
        }

        cout << ret << endl;
    }
}
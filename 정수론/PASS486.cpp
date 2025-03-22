#include <iostream>
#include <cmath>
#include <unordered_map>
using namespace std;

int min_divs[10000001];
int n, lo, hi;

void eratos(int hi) {
    for (int i = 0; i <= hi; ++i) {
        min_divs[i] = i;
    }

    int barrier = int(sqrt(hi));
    for (int i = 2; i <= barrier; ++i) {
        if (min_divs[i] == i) {
            for (int j = i * i; j <= hi; j += i) {
                if (min_divs[j] == j) {
                    min_divs[j] = i;
                }
            }
        }
    }
}

bool nMatch(int cnt, int num) {
    unordered_map<int, int> m;
    
    while (num > 1) {
        if (m.find(min_divs[num]) == m.end()) {
            m[min_divs[num]] = 1;
        } else {
            m[min_divs[num]] += 1;
        }
        num /= min_divs[num];
    }

    int ret = 1;
    for (auto& pair : m) {
        ret *= (pair.second + 1);
    }
    
    if (ret == cnt) return true;
    return false;
}

int main() {
    int C;
    cin >> C;
    while (C--) {
        cin >> n >> lo >> hi;
        
        eratos(hi);
        int ret = 0;
        for (int num = lo; num <= hi; ++num) {
            if (nMatch(n, num)) ++ret;
        }
        cout << ret << endl;
    }
}
#include <iostream>
#include <algorithm>
using namespace std;


int n, k;

double rs[1001];
double cs[1001];

bool can(double avg) {
    double arr[1001];
    for (int i = 0; i < n; ++i) {
        arr[i] = avg * cs[i] - rs[i];
    }

    sort(arr, arr + n);

    double sum = 0;
    for (int i = n - k; i < n; ++i) {
        sum += arr[i];
    }

    if (sum >= 0) return true;
    return false;
}

double solve() {
    double st = -1e-9;
    double en = 1;
    
    for (int i = 0; i < 100; ++i) {
        double mid = (st + en) / 2;
        
        if (can(mid)) {
            en = mid;
        } else {
            st = mid;
        }
    }
    return en;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> k;
        int r, c;
        for (int i = 0; i < n; ++i) {
            cin >> r >> c;
            rs[i] = r;
            cs[i] = c;
        }

        cout << solve() << endl;
    }
}
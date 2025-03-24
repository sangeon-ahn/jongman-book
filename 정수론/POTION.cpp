#include <iostream>
#include <vector>
using namespace std;

int n;
int rs[1001];
int ps[1001];

int getGcd(int p, int q) {
    if (p < q) return getGcd(q, p);
    if (q == 0) return p;
    return getGcd(q, p % q);
}

int divConquer(int st, int en) {
    if (st == en) return rs[st];

    int mid = (st + en) / 2;
    int left_min = divConquer(st, mid);
    int right_min = divConquer(mid + 1, en);

    int gcd = getGcd(left_min, right_min);
    return gcd;
}

vector<int> findMinMaterials(int lower) {
    vector<int> rs_piece(n);
    for (int i = 0; i < n; ++i) {
        rs_piece[i] = rs[i] / lower;
    }
    vector<int> ret;

    while (true) {
        bool flag = true;
        for (int i = 0; i < n; ++i) {
            if (ps[i] > rs[i]) {
                flag = false;
                break;
            }
        }

        if (flag) {
            for (int i = 0; i < n; ++i) {
                ret.push_back(rs[i] - ps[i]);
            }        
            return ret;
        }

        for (int i = 0; i < n; ++i) {
            rs[i] += rs_piece[i];
        }
    }
    
}

int main() {
    int C;
    cin >> C;
    while (C--) {
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> rs[i];
        }
        for (int i = 0; i < n; ++i) {
            cin >> ps[i];
        }

        int maxDiv = divConquer(0, n - 1);
        vector<int> ret = findMinMaterials(maxDiv);

        for (auto& mat : ret) {
            cout << mat << " ";
        }
        cout << endl;
    }
}
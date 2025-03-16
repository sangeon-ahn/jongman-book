#include <iostream>
#include <utility>
#include <queue>
#include <cstring>
#include <cmath>
using namespace std;

int n;
bool visited[100];
pair<double, double> origins[100];

double answer = 999999;

bool inRange(int org1, int org2, double d) {
    double x1, x2, y1, y2;
    x1 = origins[org1].first;
    x2 = origins[org2].first;
    y1 = origins[org1].second;
    y2 = origins[org2].second;
    return d * d >= (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

bool check(double d) {
    memset(visited, false, sizeof(visited));
    queue<int> q;
    q.push(0);
    visited[0] = true;
    while (!q.empty()) {
        int org = q.front(); q.pop();
        
        for (int i = 0; i < n; ++i) {
            if (!visited[i] && inRange(org, i, d)) {
                visited[i] = true;
                q.push(i);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) return false;
    }

    return true;
}

void solve() {
    // 반경
    double st = 0.0;
    double en = 2000.0;

    int cnt = 100;
    while (cnt-- > 0) {
        double mid = (st + en) / 2;

        bool canCover = check(mid);
        if (canCover) {
            answer = min(answer, mid);
            en = mid;
        } else {
            st = mid;
        }
    }
}

int main() {
    vector<double> answers;
    int C;
    cin >> C;
    while (C--) {
        answer = 99999;

        cin >> n;
        double x, y;
        for (int i = 0 ; i < n; ++i) {
            cin >> x >> y;
            origins[i] = {x, y};
        }

        solve();

        // 소수점 3자리에서 반올림
        answers.push_back(round(answer * 100) / 100);
    }
    for (double& ans : answers) {
        cout << ans << endl;
    }
}
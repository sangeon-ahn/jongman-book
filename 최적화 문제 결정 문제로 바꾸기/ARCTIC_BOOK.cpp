#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

int n;
double dists[101][101];
pair<double, double> origins[101];

bool decision(double d) {
    vector<bool> visited(n, false);
    visited[0] = true;
    queue<int> q;
    q.push(0);
    int seen = 0;
    while(!q.empty()) {
        int here = q.front();
        q.pop();
        ++seen;
        for(int there = 0; there < n; ++there) {
            if (!visited[there] && dists[here][there] <= d * d) {
                visited[there] = true;
                q.push(there);
            }
        }
    }
    return seen == n;
}

double optimize() {
    double lo = 0, hi = 1416.00;
    for (int it = 0; it < 100; ++it) {
        double mid = (lo + hi) / 2;
        if (decision(mid)) {
            hi = mid;
        } else {
            lo = mid;
        }
    }
    return hi;
}


double getDist(int org1, int org2) {
    double x1, y1, x2, y2;
    x1 = origins[org1].first;
    y1 = origins[org1].second;
    x2 = origins[org2].first;
    y2 = origins[org2].second;
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

int main()
{
    int C;
    cin >> C;
    while (C--) {
        cin >> n;
        double x, y;
        for (int i = 0; i < n; ++i) {
            cin >> x >> y;
            origins[i] = {x, y};
        }

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                double dist = getDist(i, j);
                dists[i][j] = dist;
                dists[j][i] = dist;
            }
        }
        cout.precision(2);
        cout << optimize() << endl;
    }
}
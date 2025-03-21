#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
using namespace std;

struct Point {
    double x, y;
};

int n, m;
vector<Point> hull1;
vector<Point> hull2;
vector<pair<Point, Point>> up_lines; 
vector<pair<Point, Point>> down_lines;

void init() {
    hull1 = vector<Point>();
    hull2 = vector<Point>();
    up_lines = vector<pair<Point, Point>>();
    down_lines = vector<pair<Point, Point>>();
}

void decompose(vector<Point>& hull) {

    int n = hull.size();
    for (int i = 0; i < n; ++i) {
        if (hull[i].x < hull[(i + 1)%n].x) {
            down_lines.push_back({hull[i], hull[(i+1)%n]});
        } else if (hull[i].x > hull[(int)((i + 1)%n)].x) {
            up_lines.push_back({hull[i], hull[(i+1)%n]});
        }
    }
}

double minX(vector<pair<Point, Point>>& lines) {
    double min_x = 987654321;
    for (auto& pair : lines) {
        min_x = min(min_x, min(pair.first.x, pair.second.x));
    }
    return min_x;
}

double maxX(vector<pair<Point, Point>>& lines) {
    double max_x = -987654321;
    for (auto& pair : lines) {
        max_x = max(max_x, max(pair.first.x, pair.second.x));
    }
    return max_x;
}

bool contain(Point& p1, Point& p2, double x) {
    return (p1.x <= x && x <= p2.x) || (p2.x <= x && x <= p1.x);
}

double getDist(Point& p1, Point& p2, double x) {
    double dy = p2.y - p1.y;
    double dx = p2.x - p1.x;
    return (dy/dx) * (x - p1.x) + p1.y;
}

double vertical(double x) {
    // 위 선분과 x좌표축 수직선 그어서 겹치는 것들 중 최소 y값
    double min_y = 987654321;
    bool found_up = false, found_down = false;
    for (auto& pair : up_lines) {
        if (contain(pair.first, pair.second, x)) {
            min_y = min(min_y, getDist(pair.first, pair.second, x));
            found_up = true;
        }
    }
    double max_y = -987654321;
    for (auto& pair : down_lines) {
        if (contain(pair.first, pair.second, x)) {
            max_y = max(max_y, getDist(pair.first, pair.second, x));
            found_down = true;
        }
    }
    if (!found_up || !found_down) return -1e9;
    return min_y - max_y;
}

double solve() {
    double lo = max(minX(up_lines), minX(down_lines)); // x좌표
    double hi = min(maxX(up_lines), maxX(down_lines));

    if (lo > hi) return 0;


    for (int i = 0; i < 100; ++i) {
        if (vertical((2 * lo + hi) / 3) < vertical((lo + 2 * hi) / 3)) {
            lo = (2 * lo + hi) / 3;
        } else {
            hi = (lo + 2 * hi) / 3;
        }
    }

    return max(0.0, vertical(hi));
}

int main() {
    int C;
    cin >> C;
    while (C--) {
        cin >> n >> m;
        double x, y;
        init();
        for (int i = 0; i < n; ++i) {
            cin >> x >> y;
            hull1.push_back({x, y});
        }
        for (int i = 0; i < m; ++i) {
            cin >> x >> y;
            hull2.push_back({x, y});
        }

        for (auto& p : hull2) {
            cout << p.x << " " << p.y << endl;
        }
        decompose(hull1);
        decompose(hull2);
        double ret = solve();
        cout << ret << endl;
    }
}
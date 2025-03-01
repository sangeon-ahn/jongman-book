#include <cmath>
#include <utility>
#include <algorithm>
#include <iostream>
using namespace std;
const double pi = 2 * acos(0);
const int INF = 987654321;
int n;
double y[100], x[100], r[100];
pair<double, double> ranges[100];

void convert_to_range()
{
    for (int i = 0; i < n; ++i) {
        double loc = fmod(2*pi + atan2(y[i], x[i]), 2*pi);
        double range = 2.0 * asin(r[i] / 2.0 / 8.0);
        ranges[i] = make_pair(loc - range, loc + range);
    }

    sort(ranges, ranges + n);
}

int solve_linear(double begin, double end)
{
    int used = 0, idx = 0;
    while (begin < end) {
        double max_cover = -1;
        while (idx < n && ranges[idx].first <= begin) {
            max_cover = max(max_cover, ranges[idx].second);
            ++idx;
        }

        if (max_cover <= begin) return INF;
        begin = max_cover;
        ++used;
    }

    return used;
}
int solve_circular() {
    int ret = INF;

    for (int i = 0; i < n; ++i) {
        if (ranges[i].first <= 0 || ranges[i].second >= 2 * pi) {
            double begin = fmod(ranges[i].second, 2 * pi);
            double end = fmod(ranges[i].first + 2 * pi, 2 * pi);

            ret = min(ret, 1 + solve_linear(begin, end));
        }
    }

    return ret;
}


void init()
{
    for (int i = 0; i < 100; ++i) {
        x[i] = y[i] = r[i] = 0.0;
        ranges[i] = {0,0};
    }
}

int main()
{
    int C;
    cin >> C;
    while (C--)
    {
        cin >> n;
        init();
        double y_v, x_v, r_v; 
        for (int i = 0; i < n; ++i) {
            cin >> y_v >> x_v >> r_v;
            y[i] = y_v;
            x[i] = x_v;
            r[i] = r_v;
        }

        convert_to_range();
        cout << solve_circular() << endl;
    }
}
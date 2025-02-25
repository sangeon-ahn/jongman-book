#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

int n;
vector<pair<int, int>> foods;

void init()
{
    foods = vector<pair<int, int>>();
}

bool compare(pair<int, int> f1, pair<int, int> f2)
{
    if (f1.first < f2.first) return 0;
    return 1;
}

int main()
{
    int C;
    cin >> C;
    while (C--)
    {
        cin >> n;
        int val;

        init();
        vector<int> cooking;
        vector<int> eating;

        for (int i = 0; i < n; ++i) {
            cin >> val;
            cooking.push_back(val);
        }
        for (int i = 0; i < n; ++i) {
            cin >> val;
            eating.push_back(val);
        }

        for (int i = 0; i < n; ++i) {
            foods.push_back({eating[i], cooking[i]});
        }

        sort(foods.begin(), foods.end(), compare);
        

        int last_time = 0;
        int cur_time = 0;
        for (int i = 0; i < foods.size(); ++i) {
            last_time = max(last_time, cur_time + foods[i].first + foods[i].second);
            cur_time += foods[i].second;
        }
        cout << last_time << endl;
    }
}
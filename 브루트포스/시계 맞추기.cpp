#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> switches = {{0, 1, 2}, {3, 7, 9, 11}, {4, 10, 14, 15}, {0, 4, 5, 6, 7},
                        {6, 7, 8, 10, 12}, {0, 2, 14, 15}, {3, 14, 15}, {4, 5, 7, 14, 15},
                        {1, 2, 3, 4, 5}, {3, 4, 5, 9, 13}}; // 10개

int answer = 987654321;


bool is_all_twelve(vector<int>& arr)
{
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] != 3) return false;
    }
    return true;
}

void rotate_clocks(vector<int>& times, int switch_idx, int cnt, int dir)
{
    if (cnt == 0) return;

    for (int i = 0; i < switches[switch_idx].size(); ++i) {
        times[switches[switch_idx][i]] = (4 + times[switches[switch_idx][i]] + cnt * dir) % 4;
    }
}

void print_status(vector<int>& times, int cnt, int cur_switch)
{
    for (int i = 0; i < times.size(); ++i) {
        cout << times[i] << " ";
    }
    cout << endl;
    cout << "count: " << cnt;
    cout << " cur_switch: " << cur_switch;
}

void dfs(vector<int>& times, int cnt, int cur_switch)
{
    // print_status(times, cnt, cur_switch);
    if (is_all_twelve(times)) {
        answer = min(answer, cnt);
        return;
    }

    for (int i = cur_switch; i < switches.size(); ++i) {
        for (int j = 0; j < 4; ++j) { // 0: 0회전, 1: 1회전, 2: 2회전, 3: 3회전
            rotate_clocks(times, i, j, 1);
            dfs(times, cnt + j, i + 1);
            rotate_clocks(times, i, j, -1);
        }
    }
}

int main()
{
    int C;
    cin >> C;

    while (C--)
    {
        vector<int> times; // 0: 3시, 1: 6시, 2: 9시, 3: 12시
        
        int time;
        for (int i = 0; i < 16; ++i) {
            cin >> time;
            times.push_back(int(time / 3) - 1);
        }

        // for (int i = 0; i < 16; ++i) {
        //     cout << times[i];
        // }

        answer = 987654321;
        dfs(times, 0, 0);

        if (answer == 987654321) {
            cout << -1 << endl;
        } else {
            cout << answer;
        }
    }
}
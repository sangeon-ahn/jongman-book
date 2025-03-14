#include <vector>
#include <iostream>
#include <unordered_map>
#include <set>

using namespace std;
const int MAXVAL = 987654321;
int n, m;
unordered_map<string, int> name_map;
vector<vector<int>> foods;
unordered_map<string, int> eat_cnt;
int answer;

void init()
{
    name_map = unordered_map<string, int>();
    foods = vector<vector<int>>();
    answer = MAXVAL;
}

void recur(int idx, unordered_map<int, int>& eat_cnt, int food_cnt)
{
    if (answer <= food_cnt) return;
    if (idx == m) {
        for (int i = 0; i < n; ++i) {
            if (eat_cnt[i] == 0) return;
        }
        answer = min(answer, food_cnt);
        return;
    }

    // 안 만들 때
    recur(idx + 1, eat_cnt, food_cnt);

    // 만들 때
    for (int i = 0; i < foods[idx].size(); ++i) {
        eat_cnt[foods[idx][i]] += 1;
    }
    recur(idx + 1, eat_cnt, food_cnt + 1);
    for (int i = 0; i < foods[idx].size(); ++i) {
        eat_cnt[foods[idx][i]] -= 1;
    }
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        cin >> n >> m;
        init();
        string name;
        for (int i = 0; i < n; ++i) {
            cin >> name;
            name_map[name] = i;
        } 
        int cnt;
        for (int i = 0; i < m; ++i) {
            cin >> cnt;
            vector<int> people;
            for (int j = 0; j < cnt; ++j) {
                cin >> name;
                people.push_back(name_map[name]);
            }
            foods.push_back(people);
        }

        unordered_map<int, int> eat_people;
        for (int i = 0; i < n; ++i) {
            eat_people[i] = 0;
        }

        recur(0, eat_people, 0);
        cout << answer << endl;
    }
}
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map> 
#include <unordered_set>
using namespace std;

const int MAXVAL = 987654321;
int n, m;
bool visited[21];
int answer;
unordered_map<string, int> name_map;
vector<vector<int>> foods;
vector<int> eat_cnts;

void init()
{
    name_map = unordered_map<string, int>();
    foods = vector<vector<int>>();
    eat_cnts = vector<int>(n, 0);
    answer = MAXVAL;
}

void recur(int idx, unordered_set<int>& people, int f_cnt)
{
    if (people.size() == n) {
        answer = min(answer, f_cnt);
        return;
    }

    if (f_cnt >= answer) return;
    if (idx >= m) return;
    
    for (int i = idx; i < m; ++i) {
        int init_size = people.size();
        bool flag = false;
        for (int j = 0; j < foods[i].size(); ++j) {
            if (people.find(foods[i][j]) == people.end()) {
                flag = true;
                break;
            }
        }

        if (flag) {
            for (int j = 0; j < foods[i].size(); ++j) {
                if (people.find(foods[i][j]) == people.end()) {
                    people.insert(foods[i][j]);
                }
                eat_cnts[foods[i][j]] += 1;
            }
            recur(idx + 1, people, f_cnt + 1);
            for (int j = 0; j < foods[i].size(); ++j) {
                eat_cnts[foods[i][j]] -= 1;
                if (eat_cnts[foods[i][j]] == 0) {
                    people.erase(people.find(foods[i][j]));
                }
            }
        }
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
        
        unordered_set<int> people;
        recur(0, people, 0);

        cout << answer << endl;
    }
}
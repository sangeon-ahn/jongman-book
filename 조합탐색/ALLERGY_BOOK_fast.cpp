// 아이디어: 이 사람이 먹을 수 있는 음식을 매 순간 만들기 -> depth <= 음식개수, 음식 개수보다 작을 수 있음.
// 기존의 느린 버전: 이 음식을 만들거나 만들지 않았을 때 결과 보기 -> 무조건 depth = 음식 개수

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

const int MAXVAL = 987654321;

int answer;
int n, m;
unordered_map<string, int> name_map; 
vector<vector<int>> foods; // 음식 별 먹을 수 있는 사람들이 저장됨.
vector<vector<int>> peoples; // 사람 별 먹을 수 있는 음식이 저장됨.
vector<int> eat_cnts;

void recur2(int food_cnt)
{
    if (food_cnt >= answer) return;

    int next = -1;
    for (int i = 0; i < eat_cnts.size(); ++i) {
        if (eat_cnts[i] == 0) {
            next = i;
            break;
        }
    }

    if (next == -1) {
        answer = min(answer, food_cnt);
        return;
    }

    for (int i = 0; i < peoples[next].size(); ++i) {
        for (int j = 0; j < foods[peoples[next][i]].size(); ++j) {
            eat_cnts[foods[peoples[next][i]][j]] += 1;
        }
        recur2(food_cnt + 1);
        for (int j = 0; j < foods[peoples[next][i]].size(); ++j) {
            eat_cnts[foods[peoples[next][i]][j]] -= 1;
        }
    }
}

void recur(int idx, int food_cnt)
{
    if (food_cnt >= answer) return;

    for (int i = 0; i < peoples[idx].size(); ++i) {
        // 먹을 음식 선택
        // 여기서 걸린 음식은 이전에 선택되지 않은 음식이다.
        int food = peoples[idx][i];
        // 먹기
        for (int j = 0; j < foods[food].size(); ++j) {
            eat_cnts[foods[food][j]] += 1;
        }

        // 다음 상대 찾기
        int next = -1;
        for (int j = 0; j < eat_cnts.size(); ++j) {
            if (eat_cnts[j] == 0) {
                next = j;
                break;
            }
        }

        // cout << idx << " " << next << " " << food_cnt + 1 << endl;

        // 다 먹었으면 정답 갱신
        if (next == -1) {
            answer = min(answer, food_cnt + 1);
            for (int j = 0; j < foods[food].size(); ++j) {
                eat_cnts[foods[food][j]] -= 1;
            }
            return; // 리턴해도되나?
        }
        
        // 그 외엔 다음 먹일사람 먹이기
        recur(next, food_cnt + 1);
        for (int j = 0; j < foods[food].size(); ++j) {
            eat_cnts[foods[food][j]] -= 1;
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
        peoples = vector<vector<int>>(n);
        foods = vector<vector<int>>(m);
        answer = MAXVAL;

        string name;
        for (int i = 0; i < n; ++i) {
            cin >> name;
            name_map[name] = i;
        }

        int cnt;
        for (int i = 0; i < m; ++i) {
            cin >> cnt;
            for (int j = 0; j < cnt; ++j) {
                cin >> name;
                foods[i].push_back(name_map[name]);
                peoples[name_map[name]].push_back(i);
            }
        } 
        bool flag = false;
        for (int i = 0; i < peoples.size(); ++i) {
            if (peoples[i].size() == 0) {
                cout << "IMPOSSIBLE" << endl;
                flag = true;
            }
        }
        if (flag) continue;
        
        eat_cnts = vector<int>(n, 0);

        // recur(0, 0); // 0번째 사람부터 먹임.
        recur2(0);
        cout << answer << endl;
    }
}

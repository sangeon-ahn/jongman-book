#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
/*
* 방법1: map<학생, 학생의 친구들>, list<학생>, list 순회하며 map의 value 순회 
* 방법2: 친구집합 유니온 파인드로 만든 후, 각 집단별 경우의수 곱하기
*/


bool visited[11];

void reset_visited(bool* arr, int size)
{
    for (int i = 0; i < size; ++i) {
        *arr = false;
        arr++;
    }
}

int dfs(vector<vector<int>> friends, int cur, int cnt, int size)
{
    if (cnt == size) return 1;

    if (visited[cur]) return dfs(friends, cur + 1, cnt, size);

    int result = 0;
    for (int j = 0; j < friends[cur].size(); ++j) {
        if (visited[friends[cur][j]]) continue;
        visited[cur] = true;
        visited[friends[cur][j]] = true;
        result += dfs(friends, cur + 1, cnt + 2, size);
        visited[cur] = false;
        visited[friends[cur][j]] = false;
    }

    return result;
}

int main()
{
    int C;
    cin >> C;
    
    vector<int> results;

    while (C-- > 0) {
        int n, m;
        cin >> n >> m;

        reset_visited(visited, n);

        vector<vector<int>> friends;
        friends.resize(n);

        while (m-- > 0) {
            int l, r;
            cin >> l >> r;
            
            friends[l].push_back(r);
            friends[r].push_back(l);
        }

        results.push_back(dfs(friends, 0, 0, n));
    }

    for (int res : results) {
        cout << res << endl;
    }
}
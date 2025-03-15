#include <iostream>
#include <cstring>
using namespace std;
/**
 * 각 셀은 두 개의 힌트배열에 속해 있다.
 * 각 힌트 배열에 속하는 숫자의 합은 정해져 있다.
 * 따라서, 각 셀에 적힐 수 있는 후보 숫자는 각 힌트배열에 속할 수 있는 숫자들의 교집합이다.
 * 따라서, 각 힌트배열에 속할 수 있는 후보 숫자들을 모두 구한 후, 셀에 교차되는 힌트배열끼리 후보 숫자들 간에 교집합을 구하면 된다. 
 * 이때, 후보 숫자를 구하는 방식은 비트마스크를 이용한다. 셀에 적힐 수 있는 숫자 범위는 1 이상 9 이하의 자연수이기 때문에, 1<<1 에서 1<<9까지 커버할 수 있는 1<<10=1024를 마스크로 사용하면 된다.
 * generateCandidate(len, sum, known) : (숫자 개수, 총합, 이미 배치돼 있는 숫자들)
 */

int N, Q;
int candidates[10][46][1025];

int color[20][20];
int board[20][20];
int hint[20][20][2];
int sum[400];
int length[400];
int known[400];

int getSize(int n) {
    int ret = 0;
    int mask = (1<<1);

    while (mask < (1<<10)) {
        if ((n & mask) > 0) {
            ++ret;
        }
        mask <<= 1;
    }
    return ret;
}

int getSum(int n) {
    int ret = 0;
    int mask = 1;

    for (int i = 0; i < 10; ++i) {
        if (n & mask > 0) {
            ret += i; 
        }
        mask <<= 1;
    }
    return ret;
}

void generateCandidates() {
    memset(candidates, 0, sizeof(candidates));    

    // 모든 경우에 대해 candidates 만들어두기
    for (int n = 0; n < 1023; n += 2) { // 1022 = 1111111110 라서 1023까지만 해주면 된다. 
        int numCnt = getSize(n);
        int numSum = getSum(n);

        int subSet = n; // known 역할
        while (true) {
            // 여기서 set의 모든 부분집합에 대해 candidates 배열을 채워넣는다. 모든 known 에 대해 채워넣는 과정이다.
            candidates[numCnt][numSum][subSet] = (n & ~subSet);

            if (subSet == 0) break;
            subSet = (subSet - 1) & n;
        }
    }
}


bool inRange(int y, int x) {
    return 0 <= x && x < N && 0 <= y && y < N;
}

void put(int y, int x, int val) {
    board[y][x] = val;
    known[hint[y][x][0]] |= (1<<val);
    known[hint[y][x][1]] |= (1<<val);
}

void remove(int y, int x, int val) {
    board[y][x] = -1;
    known[hint[y][x][0]] &= ~(1<<val);
    known[hint[y][x][1]] &= ~(1<<val);
}

int getCandidates(int y, int x) {
    int hor_idx = hint[y][x][0];
    int ver_idx = hint[y][x][1];

    return candidates[length[hor_idx]][sum[hor_idx]][known[hor_idx]] & candidates[length[ver_idx]][sum[ver_idx]][known[ver_idx]];
}

void printBoard() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool recur() {
    // 가장 후보숫자 개수가 적은 셀 구하기
    int y = -1;
    int x = -1;
    int cand_set = -1;
    int min_cnt = 10000;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (color[i][j] == 1 && board[i][j] == -1) {
                int candies = getCandidates(i, j);
                int num_cnt = getSize(candies);
    
                if (min_cnt > num_cnt) {
                    cand_set = candies;
                    min_cnt = num_cnt;
                    y = i;
                    x = j;
                }
            }
        }
    }

    // 가장 작은걸 찾았는데 넣을 숫자가 없으면 실패
    if (min_cnt == 0) {
        return false;
    }
    
    // 채울 곳을 못 찾았으면 다 채운거라서 성공
    if (y == -1) {
        printBoard();
        return true;
    }

    // 채울 곳 찾았으면 채우기
    // 후보 숫자 돌면서 넣기
    for (int i = 1; i < 10; ++i) {
        if (cand_set & (1<<i)) {
            put(y, x, i);

            bool ret = recur();
            if (ret) return true;

            remove(y, x, i);
        }
    }
    return false;
}
int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> N;
        int cell;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cin >> cell;
                color[i][j] = cell;
                if (cell == 0) {
                    board[i][j] = 0; // 0이면 벽
                } else {
                    board[i][j] = -1; // -1이면 빈공간
                }
            }
        }
        cin >> Q;
        int y, x, dir, summ;
        for (int i = 0; i < Q; ++i) {
            cin >> y >> x >> dir >> summ;
            --y;
            --x;
            int cnt = 0;
            int nx = x, ny = y;
            if (dir == 0) { // 가로
                ++nx;
                while (inRange(ny, nx) && board[ny][nx] == -1) {
                    hint[ny][nx][0] = i;
                    ++nx;
                    ++cnt;
                }
            } else { // 세로
                ++ny;
                while (inRange(ny, nx) && board[ny][nx] == -1) {
                    hint[ny][nx][1] = i;
                    ++ny;
                    ++cnt;
                }
            }
            length[i] = cnt;
            sum[i] = summ;
        }

        // gen
        generateCandidates();
        
        recur();
    }
}
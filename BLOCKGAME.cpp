#include <iostream>
#include <string>
#include <vector>
using namespace std;


int cache[1<<25];

void init()
{
    for (int i = 0; i < 1<<25; ++i) {
        cache[i] = -1;
    }
}

int boardToInt(vector<string>& board)
{
    int res = 0;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            res *= 2;
            if (board[i][j] == '#') {
                res += 1;
            }
        }
    }
    return res;
}

bool inRange(int x, int y)
{
    return 0 <= x && x < 5 && 0 <= y && y < 5;
}

int dx1[4][2] = {{0, 0}, {0, -1}, {0, 0}, {0, 1}};
int dy1[4][2] = {{0, 1}, {0, 0}, {0, -1}, {0, 0}};

int dx2[12][3] = {{0, -1, -1}, {0, 0, -1}, {-1, 0, 0}, {0, -1, -1}, {0, 0, -1}, {-1, 0, 0}, {0, 0, 1}, {0, 1, 1}, {0, 0, 1}, {0, 1, 1}, {0, 0, 1}, {1, 0, 0}};
int dy2[12][3] = {{0, 0, 1}, {0, 1, 1}, {0, 0, 1}, {0, 0, -1}, {0, -1, -1}, {0, 0, -1}, {0, -1, -1}, {0, 0, -1}, {-1, 0, 0}, {0, 0, 1}, {0, 1, 1}, {0, 0, 1}};

int blockGame(vector<string>& board) // 이 상태에서 내가 이길 수 있나 없나.
{
    int& ret = cache[boardToInt(board)];
    if (ret != -1) return ret;
    
    // 내가 놓을 수 있는 공간이 있어서 상대 턴으로 넘겼을 때 리턴값이 false인게 하나라도 있으면 난 이긴다.
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (board[i][j] == '#') continue;
            // 1. --
            for (int k = 0; k < 4; ++k) {
                int x1 = i + dx1[k][0];
                int y1 = j + dy1[k][0];

                int x2 = i + dx1[k][1];
                int y2 = j + dy1[k][1];

                if (!(inRange(x1, y1) && inRange(x2, y2))) continue;
                if (!(board[x1][y1] != '#' && board[x2][y2] != '#')) continue;
                
                board[x1][y1] = '#';
                board[x2][y2] = '#';

                bool opposite_result = blockGame(board); 

                board[x1][y1] = '.';
                board[x2][y2] = '.';

                if (!opposite_result) return ret = 1;
            }
            // 2. :.
            for (int k = 0; k < 12; ++k) {
                int x1 = i + dx2[k][0];
                int x2 = i + dx2[k][1];
                int x3 = i + dx2[k][2];

                int y1 = j + dy2[k][0];
                int y2 = j + dy2[k][1];
                int y3 = j + dy2[k][2];
                
                if (!(inRange(x1, y1) && inRange(x2, y2) && inRange(x3, y3))) continue;
                if (!(board[x1][y1] != '#' && board[x2][y2] != '#' && board[x3][y3] != '#')) continue;

                board[x1][y1] = '#';
                board[x2][y2] = '#';
                board[x3][y3] = '#';

                bool opposite_result = blockGame(board);

                board[x1][y1] = '.';
                board[x2][y2] = '.';
                board[x3][y3] = '.';

                if (!opposite_result) return ret = 1;
            }
        }
    }

    // 여기까지 오면 이길 방법이 없다.
    return ret = 0;
}

int main()
{
    int C;
    cin >> C;
    while (C--)
    {
        init();
        
        vector<string> board;
        string temp;
        for (int i = 0; i < 5; ++i) {
            cin >> temp;
            board.push_back(temp);
        }

        int result = blockGame(board);

        if (result) cout << "WINNING" << endl;
        else cout << "LOSING" << endl;
    }
}
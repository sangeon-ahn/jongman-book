#include <iostream>
#include <vector>
#include <utility>
using namespace std;
// subproblem : board 내에 흰 점 찾으면 해당 점 기준 모양 구한 후, 색칠하고 나머지 영역 대상 subproblem 수행

void print_pieces(vector<vector<pair<int, int>>> ps)
{
    for (auto v : ps) {
        for (auto p : v) {
            cout << p.first << " " << p.second << endl;
        }
        cout << endl;
    }
    cout << "---" << endl;
}

void print_board(char board[21][21], int h, int w)
{
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int dx[12][2] = {{1, 1}, {1, 1}, {0, 1}, {0, 1},
                {0, -1}, {-1, -1}, {-1, -1}, {0, -1},
                {0, -1}, {-1, 0}, {0, 1}, {1, 0}};
int dy[12][2] = {{0, -1}, {0, 1}, {1, 1}, {-1, -1},
                {-1, -1}, {0, -1}, {0, 1}, {1, 1},
                {-1, 0}, {0, 1}, {-1, 0}, {0, 1}};

bool in_range(int nx, int ny, int h, int w)
{
    return (0 <= nx && nx < h) && (0 <= ny && ny < w);
}

vector<vector<pair<int, int>>> get_pieces(char board[21][21], int h, int w)
{
    vector<vector<pair<int, int>>> pieces;

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (board[i][j] == '#') continue; 

            // 맞는모양 찾기
            for (int k = 0; k < 12; ++k) {
                int nx1 = i + dx[k][0];
                int ny1 = j + dy[k][0];
                int nx2 = i + dx[k][1];
                int ny2 = j + dy[k][1];

                // 가능
                if (in_range(nx1, ny1, h, w) && in_range(nx2, ny2, h, w) && board[nx1][ny1] == '.' && board[nx2][ny2] == '.') {
                    // 저장
                    vector<pair<int, int>> temp;
                    temp.push_back(make_pair(i, j));
                    temp.push_back(make_pair(nx1, ny1));
                    temp.push_back(make_pair(nx2, ny2));

                    pieces.push_back(temp);
                }
            }

            return pieces;
        }
    }

    return pieces;
}

int dfs(char board[21][21], int h, int w, int white_cnt)
{
    if (white_cnt == 0) return 1;
    
    vector<vector<pair<int, int>>> pieces = get_pieces(board, h, w);
    // print_board(board, h, w);
    // print_pieces(pieces);

    if (pieces.empty()) return 0;

    int result = 0;
    for (int i = 0; i < pieces.size(); ++i) {
        auto p1 = pieces[i][0];
        auto p2 = pieces[i][1];
        auto p3 = pieces[i][2];

        board[p1.first][p1.second] = '#';
        board[p2.first][p2.second] = '#';
        board[p3.first][p3.second] = '#';    
        result += dfs(board, h, w, white_cnt - 3);
        board[p1.first][p1.second] = '.';
        board[p2.first][p2.second] = '.';
        board[p3.first][p3.second] = '.';
    }

    return result;
}

int main()
{
    int C;
    cin >> C;

    while (C--)
    {
        int H, W;
        cin >> H >> W;

        char board[21][21];

        char temp;
        int white_cnt = 0;
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {
                cin >> temp; 
                board[i][j] = temp;
                
                if (temp == '.') ++white_cnt;
            }
        }

        cout << dfs(board, H, W, white_cnt) << endl;
    }
}
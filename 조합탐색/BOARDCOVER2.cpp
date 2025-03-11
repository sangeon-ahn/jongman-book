#include <iostream>
#include <string>
#include <vector>
using namespace std;

int max_cnt = 0;
int h, w, r, c;
string board[10];
vector<string> piece;
vector<vector<string>> rotated_pieces;
int origin[4][2];

void init()
{
    max_cnt = 0;
    
    for (int i = 0; i < 10; ++i) {
        board[i] = "";
    }
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 2; ++j) {
            origin[i][j] = 0;
        }
    }
    piece = vector<string>();
    rotated_pieces = vector<vector<string>>();
}

void create_rotate_pieces()
{
    vector<string> last_piece = piece;
    for (int i = 0; i < 4; ++i) {
        int lp_r = last_piece.size();
        int lp_c = last_piece[0].size();

        vector<string> temp;
        
        temp.assign(lp_c, string(lp_r, '.'));
        
        int o_x, o_y;
        for (int j = 0; j < lp_r; ++j) {
            for (int k = 0; k < lp_c; ++k) {
                temp[k][lp_r-j-1] = last_piece[j][k];
            }
        }
        
        for (int j = 0; j < lp_c; ++j) {
            bool flag = false;
            for (int k = 0; k < lp_r; ++k) {
                if (temp[j][k] == '#') {
                    o_x = j;
                    o_y = k;
                    flag = true;
                    break;
                }
            }
            if (flag) break;
        }
        origin[i][0] = o_x;
        origin[i][1] = o_y;

        for (int p = 0; p < temp.size(); ++p) {
            for (int q = 0; q < temp[0].size(); ++q) {
                cout << temp[p][q] << " ";
            }
            cout << endl;
        }
        rotated_pieces.push_back(temp);
        last_piece = rotated_pieces.back();
    }
}


bool can_cover(int x, int y, int rot_type)
{
    for (int i = 0; i < rotated_pieces[rot_type].size(); ++i) {
        for (int j = 0; j < rotated_pieces[rot_type][0].size(); ++j) {
            if (rotated_pieces[rot_type][i][j] == '#') {
                if (x + i - origin[rot_type][0] >= h || y + j - origin[rot_type][1] >= w) return false;
                if (board[x + i-origin[rot_type][0]][y + j-origin[rot_type][1]] == '#') return false;
            }
        }
    }
    return true;
}

void cover(int x, int y, int rot_type)
{
    for (int i = 0; i < rotated_pieces[rot_type].size(); ++i) {
        for (int j = 0; j < rotated_pieces[rot_type][0].size(); ++j) {
            if (rotated_pieces[rot_type][i][j] == '#') {
                board[x + i - origin[rot_type][0]][y + j - origin[rot_type][1]] = '#';
            }
        }
    }
}

void uncover(int x, int y, int rot_type)
{
    for (int i = 0; i < rotated_pieces[rot_type].size(); ++i) {
        for (int j = 0; j < rotated_pieces[rot_type][0].size(); ++j) {
            if (rotated_pieces[rot_type][i][j] == '#') {
                board[x + i - origin[rot_type][0]][y + j - origin[rot_type][1]] = '.';
            }
        }
    }
}


void recur(int x, int y, int cnt)
{
    max_cnt = max(max_cnt, cnt);

    if (y == w) {
        ++x;
        y = 0;
    }

    if (x == h) return;

    for (int i = x; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (i == x && j < y) continue;
            if (board[i][j] == '#') continue;

            for (int k = 0; k < 4; ++k) {
                if (can_cover(i, j, k)) {
                    cover(i, j, k);
                    recur(i, j + 1, cnt + 1);
                    uncover(i, j, k);
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
        init();
        cin >> h >> w >> r >> c;

        string row;
        for (int i = 0; i < h; ++i) {
            cin >> row;
            board[i] = row;
        }
    
        for (int i = 0; i < r; ++i) {
            cin >> row;
            piece.push_back(row);
        }
    
        create_rotate_pieces();
    
        recur(0, 0, 0);
        cout << max_cnt << endl;
    }
}

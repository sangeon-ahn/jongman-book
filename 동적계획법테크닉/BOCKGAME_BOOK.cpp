#include <iostream>
#include <vector>
#include <string>
using namespace std;


vector<int> pieces;
string board = "";
int cache[1<<25];

int CellToBin(int x, int y)
{
    return (1 << ((5 * x) + y));
}

int createPieces()
{
    // ㄴ자 모양
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            vector<int> cells;
            int cellSum = 0;
            for (int dx = 0; dx < 2; ++dx) {
                for (int dy = 0; dy < 2; ++dy) {
                    int bitVal = CellToBin(i + dx, j + dy);
                    cellSum += bitVal;
                    cells.push_back(bitVal);
                }
            }
            
            for (int k = 0; k < cells.size(); ++k) {
                pieces.push_back(cellSum - cells[k]);
            }
        }
    }
    // ㅡ자 모양
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 4; ++j) {
            pieces.push_back(CellToBin(i, j) + CellToBin(i, j + 1));
            pieces.push_back(CellToBin(j, i) + CellToBin(j + 1, i));
        }
    }
}

void init()
{
    for (int i = 0; i < 1<<25; ++i) {
        cache[i] = -1;
    }
    board = "";
}

int boardGame(int board)
{
    int& ret = cache[board];
    if (ret != -1) return ret;

    ret = 0;
    for (int i = 0; i < pieces.size(); ++i) {
        if ((board & pieces[i]) == 0) {
            if (!boardGame(board | pieces[i])) {
                ret = 1;
                break;
            }
        }
    }

    return ret;
}

int main()
{
    pieces = vector<int>();
    createPieces();

    int C;
    cin >> C;
    while (C--)
    {
        init();

        string temp;
        for (int i = 0; i < 5; ++i) {
            cin >> temp;
            board += temp;
        }

        int boardToBin = 0;
        for (int i = 0; i < board.size(); ++i) {
            if (board[i] == '#') {
                boardToBin += CellToBin(i / 5, i % 5);
            }
        }

        int result = boardGame(boardToBin);
        if (result) {
            cout << "WINNING" << endl;
        }
        else cout << "LOSING" << endl; 
    }
}
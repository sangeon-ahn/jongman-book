#include <vector>
#include <string>
using namespace std;

int cache[20000];

int convertToKey(vector<string>& board)
{
    int key = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            key = key * 3;
            
            if (board[i][j] == 'x') key += 1;
            else if (board[i][j] == 'o') key += 2;
        }
    }
    return key;
}

bool isLineExists(vector<string>& board, char turn)
{
}

int tictactoe(vector<string>& board, char turn)
{
    int& ret = cache[convertToKey(board)];
    
    if (ret !=-2) return ret;
    
    bool isFinished = isLineExists(board, turn);
    if (isFinished) {
        return ret = 1;
    }

    int minVal = 2;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == '.') {
                board[i][j] = turn;
                minVal = min(minVal, tictactoe(board, 'o'+'x' - turn));
                board[i][j] = '.';
            }
        }
    }

    if (minVal == 2 || minVal == 0) return ret = 0;
    return ret = -minVal;
}

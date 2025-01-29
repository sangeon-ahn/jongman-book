#include <algorithm>
#include <string>
using namespace std;

const int MAX = 1000000000 + 1;
int length[51];
void precal() 
{
    length[0] = 1;
    for (int i = 1; i < 51; ++i) {
        length[i] = min(MAX, 2 * length[i - 1] + 2);
    }
}

const string X = "X+YF";
const string Y = "FX-Y";

char expand(const string& dragonCurve, int generation, int skip) // dragonCurve를 generation번 진화한 드래곤커브의 skip번째 문자 반환
{
    if (generation == 0) {
        return dragonCurve[skip];
    }

    for (int i = 0; i < dragonCurve.size(); ++i) {
        if (dragonCurve[i] == 'X' or dragonCurve[i] == 'Y') {
            if (skip >= length[generation]) {
                skip -= length[generation];
            } else if (dragonCurve[i] == 'X') {
                return expand(X, generation - 1, skip);
            } else {
                return expand(Y, generation - 1, skip);
            }
        } else if (skip > 0) {
            skip--;
        } else {
            return dragonCurve[i];
        }
    }

    return NULL;
}


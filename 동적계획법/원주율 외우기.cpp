#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

vector<int> answers;
string num;

/***
 * 이 함수의 스펙
 * 1. 역할: 숫자를 입력받아, 여러개의 조각으로 분리한 후, 각 조각의 난이도를 전부 더해서 반환한다.
 * 이때, 총합이 가장 낮은 경우일 때의 값을 반환한다.
 * 2. 인자: 시작 인덱스. (끝 인덱스는 num의 길이로 알 수 있음.)
 * 3. 점화식: ANS(0) = min(f(x))*ANS(x), (x=3, 4, 5)
 */
const int MAXVAR = 987654321;

int cache[10001];

bool allSame(int st, int en)
{
    char ch = num[st];

    for (int i = st + 1; i <= en; ++i) {
        if (ch != num[i]) return false;
        ch = num[i];
    }
    return true;
}

bool ascendOrDescendByOne(int st, int en)
{
    char n = num[st + 1];
    int diff = num[st] - num[st + 1];
    
    if (diff != 1 && diff != -1) return false;

    for (int i = st + 2; i <= en; ++i) {
        if (n - num[i] != diff) return false;
        n = num[i];
    }

    return true;
}

bool flip(int st, int en)
{
    char n1 = num[st];
    char n2 = num[st + 1];
    for (int i = st + 2; i <= en; ++i) {
        if (i % 2 == 0 && num[i] != n1) return false;
        if (i % 2 != 0 && num[i] != n2) return false;
    }
    return true;
}

bool equalDiff(int st, int en)
{
    char n = num[st + 1];
    int diff = num[st + 1] - num[st];
    for (int i = st + 2; i <= en; ++i) {
        if (num[i] - n != diff) return false;
        n = num[i];
    }
    return true;
}

int memorizeCircle(int start)
{
    int& res = cache[start];

    if (res != -1) return res;

    res = MAXVAR;    
    for (int i = 2; i <= 4; ++i) {
        if ((start + i < num.size()) && (0 < num.size() - start - i)) {
            // 1+i 크기 조각으로 나눌 때, 위에서부터 하나라도 먼저 걸리면 아래꺼 할 필요 없음. 난이도 낮은 순서대로 있기 때문.
            
            if (allSame(start, start + i)) { // start + i도 포함.
                res = min(res, 1 + memorizeCircle(start + i + 1));
            } else if (ascendOrDescendByOne(start, start + i)) {
                res = min(res, 2 + memorizeCircle(start + i + 1));
            } else if (flip(start, start + i)) {
                res = min(res, 4 + memorizeCircle(start + i + 1));
            } else if (equalDiff(start, start + i)) {
                res = min(res, 5 + memorizeCircle(start + i + 1));
            } else {
                res = min(res, 10 + memorizeCircle(start + i + 1));
            }
        }
    }

    return res; 
}

void initialize()
{
    for (int i = 0; i < 10001; ++i)
    {
        cache[i] = -1;
    }
    cache[num.size()] = 0;
}

int main()
{
    int C;
    cin >> C;
    answers = vector<int>();

    while (C--)
    {
        cin >> num; 
        
        initialize();

        int ans = memorizeCircle(0);


        answers.push_back(ans);
    }

    for (int ans : answers) {
        cout << ans << endl;
    }
}
#include <iostream>
#include <vector>
using namespace std;

const int MINVAL = -987654321;
int n;
int nums[51];
int cached[51][51];
vector<int> answers;

void init()
{
    for (int i = 0; i < 51; ++i) {
        nums[i] = -1001;
    }
    for (int i = 0; i < 51; ++i) {
        for (int j = 0; j < 51; ++j) {
            cached[i][j] = MINVAL;
        }
    }
    answers = vector<int>();
}



int numberGame(int st, int en) // st:en 범위 숫자들 가지고 지금 상대가 diff만큼 더 벌었을 때 내가 차이낼 수 있는 최대 금액.
{
    if (st > en) return 0;
    int& ret = cached[st][en];
    if (ret != MINVAL) return ret;

    // 4가지 각각 수행한 후 numberGame을 넘겼을 때 다음 사람의 최선의 차이를 다 구한 후, 이것들 중에 가장 작은 값의 -를 붙여서 반환

    // 1. 왼쪽 먹기
    ret = max(ret, nums[st] + (-numberGame(st + 1, en)));
    // 2. 오른쪽 먹기
    ret = max(ret, nums[en] + (-numberGame(st, en - 1)));
    
    if (en - st >= 1) {
        // 3. 왼쪽 두개 빼기
        ret = max(ret, -numberGame(st + 2, en));
        // 4. 오른쪽 두개 빼기
        ret = max(ret, -numberGame(st, en - 2));
    }

    return ret;
}

int main()
{
    int C;
    cin >> C;
    while (C--)
    {
        init();

        cin >> n;
        int num;
        for (int i = 0; i < n; ++i) {
            cin >> num;
            nums[i] = num;
        }

        int ret = numberGame(0, n - 1); // state: st, en, turn
        answers.push_back(ret);
    }

    for (int answer : answers) {
        cout << answer << endl;
    }
}
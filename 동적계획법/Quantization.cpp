#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> seq;
vector<int> answers;
int cache[11][101]; // [step][startIndex]: step개 숫자 남았을 때, arr[startIndex:] 범위 오차제곱합 최솟값
const int MAXVAL = 987654321;

int getAvg(int st, int en)
{
    // 1. 합을 구한다.
    int sum = 0;
    for (int i = st; i <= en; ++i) {
        sum += seq[i];
    }

    // 2. 평균의 몫을 구한다.
    int head = sum / (en - st + 1);

    // 3. 몫, 몫 + 1 값에 숫자 개수를 곱한다.
    int num1 = head * (en - st + 1);
    int num2 = (head + 1) * (en - st + 1);

    // 4. 합과의 차이가 작은 쪽을 평균값으로 선택한다.
    if ((num1 - sum) * (num1 - sum) > (num2 - sum) * (num2 - sum)) {
        return head + 1;
    }
    return head;
}

int getDiff(int st, int en)
{
    if (st == en) return 0;

    int avg = getAvg(st, en);

    int res = 0;
    for (int i = st; i <= en; ++i) {
        res += (seq[i] - avg) * (seq[i] - avg);
    }

    return res;
}

int quantize(int remained, int st)
{
    int& res = cache[remained][st];

    if (res != MAXVAL) return res;

    if (remained == 1) {
        return res = getDiff(st, seq.size() - 1);
    }

    for (int i = st; i < seq.size(); ++i) { // st <= x <= i 차지하고 재귀
        // 남은 숫자보다 남은 길이가 같거나 길어야 함.
        if (remained - 1 <= seq.size() - i - 1) {
            res = min(res, getDiff(st, i) + quantize(remained - 1, i + 1));
        }
    }

    return res;
}


void init()
{
    for (int i = 0; i < 11; ++i) {
        for (int j = 0; j < 101; ++j) {
            cache[i][j] = MAXVAL;
        }
    }
}

int main()
{
    int C;
    cin >> C;
    while (C--)
    {
        int n, s;
        cin >> n >> s;

        seq = vector<int>();

        init();

        int num;
        for (int i = 0; i < n; ++i) {
            cin >> num;
            seq.push_back(num);
        }

        sort(seq.begin(), seq.end());

        answers.push_back(quantize(s, 0)); 
    }

    for (int ans : answers) {
        cout << ans << endl;
    }
}
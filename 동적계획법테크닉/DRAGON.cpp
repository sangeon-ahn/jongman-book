#include <iostream>
#include <string>
#include <vector>
using namespace std;

int n, p, l;
vector<string> answers;
vector<string> dragons;
long long mids[51];

void init()
{
    answers = vector<string>();
    dragons.push_back("FX");
    dragons.push_back("FX+YF");
    for (int i = 0; i < 51; ++i) {
        mids[i] = -1;
    }
}

long long toNodeScale(long long val) // return: x, x번째 노드에 위치하는 문자.(1<=x)
{
    return ((val - 1) / 3) + 1;
}

long long toDragonScale(long long val)
{
    return val * 3;
}

string dragon(long long depth, long long st, long long en)
{
    // base condition
    if (depth <= 1) {
        return dragons[depth].substr(st - 1, en - st + 1);
    }

    long long& mid = mids[depth];
    if (mid == -1) mid = ((long long)1 << (depth - 1));

    string left = "";
    string right = "";

    cout << "depth: " << depth << " st: " << st << " en: " << en << " ";
    cout << "mid: " << mid << endl;
    cout << toNodeScale(st) << endl;
    cout << toNodeScale(en) << endl;
    if (toNodeScale(st) <= mid) {
        if (toNodeScale(en) <= mid) {
            if (en == toDragonScale(mid)) {
                cout << 1 << endl;
                left = dragon(depth - 1, st, en - 1) + "+";
            } else {
                cout << 2 << endl;
                left = dragon(depth - 1, st, en);
            }
        } else {
            left = dragon(depth - 1, st, toDragonScale(mid)) + "+";

            if (toDragonScale(mid) * (1.5) <= en) { // en이 3/4 지점 넘어가면 나눠서 구함.         
                cout << 3 << endl;
                right += dragon(depth - 1, 1, toDragonScale(mid) * 0.5);
                char& ch = right.at(right.size() - 1);

                if (ch == '-') ch = '+';
                else ch = '-';
                right += dragon(depth - 1, toDragonScale(mid) * 0.5 + 1, en - toDragonScale(mid));
            } else {
                cout << 4 << endl;
                right = dragon(depth - 1, 1, en - toDragonScale(mid));
            }
        }
    } else {
        if (toDragonScale(mid) * (1.5) <= en && toDragonScale(mid) * 1.5 >= st) { // en이 3/4 지점 넘어가면 나눠서 구함.         
                cout << 5 << endl;
                right += dragon(depth - 1, st - toDragonScale(mid), toDragonScale(mid) * 0.5);
                char& ch = right.at(right.size() - 1);

                if (ch == '-') ch = '+';
                else ch = '-';
                right += dragon(depth - 1, toDragonScale(mid) * 0.5 + 1, en - toDragonScale(mid));      
        } else {
            cout << 6 << endl;
            right = dragon(depth - 1, st - toDragonScale(mid), en - toDragonScale(mid));
        }
    }

    return left + right;
}

int main()
{
    int C;
    cin >> C;

    init();

    while (C--)
    {
        cin >> n >> p >> l;
        answers.push_back(dragon(n, p, p + l - 1));
    }

    for (auto& str : answers) {
        cout << str << endl;
    }
}
#include <iostream>
#include <vector>
using namespace std;


// 반환: st<=x<=en 구간에서 가장 큰 직사각형 넓이
int divide_conquer(vector<int>& ladders, int st, int en) // st<=x<=en , ex) st=0,en=6  |  st=0,en=7
{
    // 기저조건
    if (st == en) return ladders[st];

    // 나누기
    int mid = (st + en) / 2;

    int left_most = divide_conquer(ladders, st, mid); // mid 포함
    int right_most = divide_conquer(ladders, mid + 1, en);

    int max_area = max(left_most, right_most);

    // 사이 넓이 계산(mid, mid + 1)
    int left = mid;
    int right = mid + 1;

    int middle_largest_area = min(ladders[left], ladders[right]) * 2;
    int shortest = min(ladders[left], ladders[right]);

    while (!(left == st && right == en)) { // 둘 중 하나라도 아직 끝에 도달 안했으면 않았으면 진행
        if (left == st) {
            ++right;
            shortest = min(shortest, ladders[right]);
        } else if (right == en) {
            --left;
            shortest = min(shortest, ladders[left]);
        } else if (ladders[left - 1] <= ladders[right + 1]) {
            ++right;
            shortest = min(shortest, ladders[right]);
        } else {
            --left;
            shortest = min(shortest, ladders[left]);
        }

        middle_largest_area = max(middle_largest_area, (right - left + 1) * shortest);
    }

    return max(max_area, middle_largest_area);
}

int main()
{
    int C;
    cin >> C;
    while (C--)
    {
        vector<int> ladders;
        int N;
        cin >> N;

        int ladder;
        for (int i = 0; i < N; ++i) {
            cin >> ladder;
            ladders.push_back(ladder);     
        }

        cout << divide_conquer(ladders, 0, ladders.size() - 1);
    }
}
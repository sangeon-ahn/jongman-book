#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

int n;
priority_queue<int, vector<int>, greater<int>> pq;
void init()
{
    pq = priority_queue<int, vector<int>, greater<int>>();
}

int main()
{
    int C;
    cin >> C;
    while (C--)
    {
        init();
        cin >> n;
        int temp;
        for (int i = 0; i < n; ++i) {
            cin >> temp;
            pq.push(temp);
        }
        if (n == 1) {
            cout << temp << endl;
        } else {
            int ret = 0;
            while (pq.size() > 1) {
                int val1 = pq.top(); pq.pop();
                int val2 = pq.top(); pq.pop();

                ret += (val1 + val2);
                pq.push(val1 + val2);
            }
            cout << ret << endl;
        }
    }
}
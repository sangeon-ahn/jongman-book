#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <utility>
using namespace std;

int n, k;
vector<int> nums;
unordered_map<int, vector<int>> lisInfo; // [num, [nums[numIdx:]의 len(lis), lisCnt]]
vector<pair<int, vector<int>>> lisInfoVec;

int dp[501];

vector<int> answer;
void init()
{
    nums = vector<int>();
    lisInfo = unordered_map<int, vector<int>>();
    answer = vector<int>();
    
    for (int i = 0; i < 501; ++i) {
        dp[i] = -1;
    }
    lisInfoVec = vector<pair<int, vector<int>>>();
}

/**
 * 구해야 하는 것
 * 1. Len(LIS) -> 아는 것
 * 2. k번째 LIS -> 이번에 알아야 하는 것
 * LIS: 가장 긴 부분수열
 * 기존의 LIS 구하는 법: dp + idx 기준 for 재귀 돌려서 최대인 경우로 갱신.
 *
 * 1. lisInfo 채워 넣기
 * 2. lisInfo를 num 기준으로 사전순으로 오름차순 정렬한 벡터A 생성
 * 3. 재귀 수행, 인자: (원하는 lis 길이L, 이전숫자값X), 반환값: void
 *  로직:
 *  - A 돌면서 lis가 L인거 고르고 lisCnt 확인
 *  - step > lisCnt면 step -= lisCnt 후 continue
 *  - step <= lisCnt면 해당 시작숫자를 정답벡터에 추가 후 재귀수행: recur(L-1, curX, step)
 * 4. 정답벡터 반환
 */


pair<int, int> lis(int start)
{
    int& ret = dp[start];
    if (ret != -1) return {lisInfo[nums[start]][0], lisInfo[nums[start]][1]};

    int lisLen = 0;
    int lisCnt = 0;
    for (int i = start + 1; i < n; ++i) {
        if (nums[start] < nums[i]) {
            auto p = lis(i);
            if (lisLen < p.first) {
                lisLen = p.first;
                lisCnt = p.second;
            } else if (lisLen == p.first) {
                lisCnt += p.second;
            }
        }
    }

    lisInfo[nums[start]] = {lisLen + 1, lisCnt == 0 ? 1 : lisCnt};
    ret = lisLen + 1;
    
    return {lisInfo[nums[start]][0], lisInfo[nums[start]][1]};
}

void klis(int lisLen, int num)
{
    if (lisLen == 0) return;

    for (int i = 0; i < lisInfoVec.size(); ++i) {
        if (num < lisInfoVec[i].first) {
            if (lisLen == (lisInfoVec[i].second)[0]) {
                if (k > (lisInfoVec[i].second)[1]) {
                    k -= (lisInfoVec[i].second)[1];
                } else {
                    answer.push_back(lisInfoVec[i].first);
                    klis(lisLen - 1, lisInfoVec[i].first);
                    return;
                }
            }
        }
    }
}

int main()
{
    int C;
    cin >> C;
    while (C--)
    {
        cin >> n >> k;

        init();

        int num;
        for (int i = 0; i < n; ++i) {
            cin >> num;
            nums.push_back(num);
        }


        int maxLisLen = 0;
        for (int i = 0; i < n; ++i) {
            maxLisLen = max(maxLisLen, lis(i).first);
        }

        lisInfoVec = vector<pair<int, vector<int>>>(lisInfo.begin(), lisInfo.end());
        sort(lisInfoVec.begin(), lisInfoVec.end(), [](const auto& a, const auto& b) {
           return to_string(a.first) < to_string(b.first); 
        });

        // for (auto& p : lisInfoVec) {
        //     cout << p.first << " " << p.second[0] << " " << p.second[1] << endl;
        // }
        klis(maxLisLen, -1);

        cout << maxLisLen << endl;
        for (int num : answer) {
            cout << num << " ";
        }
    }
}
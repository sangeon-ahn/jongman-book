#include <iostream>
#include <vector>
#include <string>
using namespace std;
/**
 * 각 물건을 포함하는 경우와 포함하지 않는 경우 두 가지로 나누어 두개의 상태로 구분하여 구현.
 * 선택한 아이템을 구하는 과정은 pack의 결과를 통해 간접적으로 아는 방법임 -> 특정 아이템을 후보군에 포함시켰을 때와 포함시키지 않았을 때 두 결과값을 비교해서 구함.
 */
int n, capacity;

int cache[101][1001];
int volumes[101];
int eagers[1001];
string names[101];

int pack(int item, int capacity) // 최대 간절도 합
{
    int& ret = cache[item][capacity];
    if (ret != -1) return ret;

    // item을 포함하지 않는 경우.
    ret = pack(item + 1, capacity);

    // item을 포함하는 경우
    if (volumes[item] <= capacity) {
        ret = max(ret, eagers[item] + pack(item + 1, capacity - volumes[item]));
    }

    return ret;
}

void reconstruct(int item, int capacity, vector<string>& answer)
{
    if (item == n) return;

    if (pack(item, capacity) == pack(item + 1, capacity)) {
        reconstruct(item + 1, capacity, answer);
    } else {
        answer.push_back(names[item]);
        reconstruct(item + 1, capacity - volumes[item], answer);
    }
}
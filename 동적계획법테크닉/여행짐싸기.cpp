#include <iostream>
#include <string>
#include <vector>
using namespace std;
/**
 * 흠... 일단, 그 뭐냐 그 입력 하나하나씩 받아서 volume 순회돌면서 뒤에서부터 채우는방식은 어떤 물건을 골랐는지 알기 어려움. 왜? 부피별로 배열이나 벡터를 가지고 있어야 어떤 물건들을 담고 있는지 알 수 있음.
 * 이전 문제의 답은 배열의 인덱스가 i면 arr[i] = i-1번째 숫자를 택할 때, LIS를 만들 수 있는 다음 숫자의 인덱스.
 * 이번 문제와 뭐가 다르지? 이전 문제의 조건: 이전 숫자보다 크냐?, 이번 문제의 조건: 더 담을 수 있나?
 * 조건에 맞을 시: 이전 문제 - 선택함. 이번 문제 - 선택함.
 * 반환값: 이전 - 최대LIS길이, 이번 - 최대 간절도합
 * 
 */
class Item
{
    public:
    string name;
    int volume;
    int eager;

    Item(string name, int volume, int eager) : name{name}, volume{volume}, eager{eager} {}
};

int N, W;
vector<Item> items;
int cache[101][1001]; // cache[i][j]: i번째 물건부터 확인하고, 부피를 j만큼 사용했을 때 최대 간절도합.
int best_choices[101][1001];

void init()
{
    items = vector<Item>();
    for (int i = 0; i < 101; ++i) {
        for (int j = 0; j < 1001; ++j) {
            cache[i][j] = -1;
            best_choices[i][j] = -1;
        }
    }
}

int max_eager_sum(int start, int remained_capacity) // start번째 물건부터 확인한다고 할 때, 최대 간절도합
{
    int& ret = cache[start][remained_capacity];
    
    if (ret != -1) return ret;

    if (remained_capacity == 0) return ret = 0;

    int best_choice_idx = -1;

    int subret = -1;
    for (int i = start; i < N; ++i) {
        if (remained_capacity >= items[i].volume) {
            int cand = items[i].eager + max_eager_sum(i + 1, remained_capacity - items[i].volume);

            if (subret < cand) {
                subret = cand;
                // i를 건들어야 한다.
                best_choice_idx = i;
            }
        }
    }

    if (subret == -1) return ret = 0;

    // start, remained_capacity 상태로 물건 골랐을 때 가장 처음에 하는 최고의 선택 = best_choice_idx
    best_choices[start][remained_capacity] = best_choice_idx;
    return ret = subret;
}

int main()
{
    int C;
    cin >> C;


    while (C--)
    {
        cin >> N >> W;
        string item;
        int volume;
        int eager;

        init();

        for (int i = 0; i < N; ++i) {
            cin >> item >> volume >> eager; 
            items.emplace_back(item, volume, eager);
        }

        int ans = max_eager_sum(0, W);
        vector<string> names;

        int next = best_choices[0][W];
        int remained_capacity = W;

        while (next != -1) {
            remained_capacity -= items[next].volume;

            names.push_back(items[next].name); // next가 최고의 선택
            next = best_choices[next+1][remained_capacity]; // 이 값이 valid한게 자명한 이유: next가 최고의 선택이므로, max_eager_sum:52L에서 (next+1, remained_capacity)에 대해 best_choice값이 결정된다(-1 or not)
        }

        cout << ans << " " << names.size() << endl;
        for (string& name : names) cout << name << endl;
    }
}
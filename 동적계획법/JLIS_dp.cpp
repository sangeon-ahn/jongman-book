#include <iostream>
#include <vector>
#include <limits>
using namespace std;

const long long MINVAL = numeric_limits<long long>::min(); 

vector<int> nums1, nums2;

int cache[101][101]; // ([nums1_start:], [nums2_start:]) 범위에서 최대 JLIS 길이 저장 

void initialize()
{
    for (int i = 0; i < 101; ++i) {
        for (int j = 0; j < 101; ++j) {
            cache[i][j] = -1;
        }
    }
}

int jlis(int nums1_idx, int nums2_idx) // nums1_idx와 nums2_idx는 이미 jlis에 포함임. 
{
    int& ret = cache[nums1_idx + 1][nums2_idx + 1];

    if (ret != -1) return ret;

    ret = 2;
    
    long long a = nums1_idx == -1 ? MINVAL : nums1[nums1_idx];
    long long b = nums2_idx == -1 ? MINVAL : nums2[nums2_idx];

    int max_elem = max(a, b);

    for (int i = nums1_idx + 1; i < nums1.size(); ++i) {
        if (max_elem < nums1[i]) {
            ret = max(ret, jlis(i, nums2_idx) + 1);
        }
    }
    for (int i = nums2_idx + 1; i < nums2.size(); ++i) {
        if (max_elem < nums2[i]) {
            ret = max(ret, jlis(nums1_idx, i) + 1);
        }
    }
    return ret;
}

int main()
{
    int C;
    cin >> C;

    vector<int> answers;

    while (C--)
    {
        int n, m;
        cin >> n >> m;

        nums1 = vector<int>(n);
        nums2 = vector<int>(m);

        int temp;
        for (int i = 0; i < n; ++i) {
            cin >> temp;
            nums1[i] = temp; 
        }
        for (int i = 0; i < m; ++i) {
            cin >> temp;
            nums2[i] = temp;
        }

        initialize();

        answers.push_back(jlis(-1, -1) - 2);
    }

    for (int ans : answers) {
        cout << ans << endl;
    }
}
#include <iostream>
#include <vector>
using namespace std;


bool vis1[101];
bool vis2[101];
vector<int> answers;

void init_vis()
{
    for (int i = 0; i < 101; ++i) {
        vis1[i] = false;
        vis2[i] = false;
    }
}

int getJLISLen(vector<int> nums1, vector<int> nums2, vector<int>& seq1, vector<int>& seq2)
{
    int res = 0;
    int p = 0;
    int q = 0;

    while (p < seq1.size() || q < seq2.size())
    {
        if (p == seq1.size()) {
            res += seq2.size() - q;
            break;
        } else if (q == seq2.size()) {
            res += seq1.size() - p;
            break;
        } else {
            int p_num = nums1[seq1[p]];
            int q_num = nums2[seq2[q]];

            if (p_num > q_num) {
                ++res;
                ++q;
            } else if (p_num < q_num) {
                ++res;
                ++p;
            } else {
                ++res;
                ++p;
                ++q;
            }
        }
    }

    return res;
}


vector<int> temp_seq;
void lis(vector<int>& seq, vector<vector<vector<int>>>& subseqs, int start_idx, int cur_idx)
{
    if (start_idx == cur_idx) temp_seq.push_back(start_idx);

    bool flag = false;
    for (int i = cur_idx + 1; i < seq.size(); ++i) {
        if (seq[cur_idx] < seq[i]) {
            flag = true;
            temp_seq.push_back(i);
            lis(seq, subseqs, start_idx, i);
            temp_seq.pop_back();
        }
    }

    // 리프노드일 때,
    if (!flag) {
        subseqs[start_idx].push_back(temp_seq);
    }

    return;
}

int main()
{
    int C;
    cin >> C;
    while (C--)
    {
        int n, m;
        cin >> n >> m;
        int temp;

        init_vis();

        vector<int> nums1;
        vector<int> nums2;

        for (int i = 0; i < n; ++i) {
            cin >> temp;
            nums1.push_back(temp);
        }
        for (int i = 0; i < m; ++i) {
            cin >> temp;
            nums2.push_back(temp);
        }

        vector<vector<vector<int>>> nums1_subseqs; // i번째 시작 부분수열은 여러개다 
        vector<vector<vector<int>>> nums2_subseqs;
        nums1_subseqs.resize(n);
        nums2_subseqs.resize(m);

        for (int i = 0; i < n; ++i) {
            vector<int> vec;
            temp_seq = vec;
            lis(nums1, nums1_subseqs, i, i); // (total_seq, answer, start_idx, cur_idx)
        }        

        for (int i = 0; i < m; ++i) {
            vector<int> vec;
            temp_seq = vec;
            lis(nums2, nums2_subseqs, i, i);
        }

        int answer = -1;
        for (int i = 0; i < nums1_subseqs.size(); ++i) {
            if (vis1[i]) continue;
            
            for (int p = 0; p < nums1_subseqs[i].size(); ++p) {
                for (int q = 0; q < nums1_subseqs[i][p].size(); ++q) {
                    vis1[nums1_subseqs[i][p][q]] = true;
                }

                for (int j = 0; j < nums2_subseqs.size(); ++j) {
                    for (int k = 0; k < nums2_subseqs[j].size(); ++k) {
                        int res = getJLISLen(nums1, nums2, nums1_subseqs[i][p], nums2_subseqs[j][k]);
                        answer = max(answer, res);
                    }
                }
            }
        }

        answers.push_back(answer);
    }

    for (int ans : answers) cout << ans << endl;
}
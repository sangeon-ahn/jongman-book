#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;


/**
 * 어떻게 풀까?
 * 문제가 요구하는 것: 잘못만든 분류기가 인식한 문장 결과를 과거 데이터를 이용해서 원래 문장으로 고쳐라.
 * 과거 데이터들:
 * - 원본 문장에서 i번째 단어가 문장의 첫번째에 올 확률
 * - 원본 문장에서 i번째 옆에 j번째 단어가 올 확률
 * - 분류기가 i번째 단어를 j번째 단어로 인식할 확률
 * 
 * 분류기가 boy라고 인식했다 -> boy가 j번째일 때, 분류기가 0~n-1번째 단어를 j번째 단어로 인식할 확률 -> [0..n][j] 확인
 * 각 경우에 대해서, 원래는 (0..n-1)번째 단어이고, 
 * 분류된 문장의 각 단어 자리에 대해 어떤 단어가 가장 높은 확률인지를 계산해야 한다.
 * 첫번째 자리의 경우는 각 단어들을 순회하면서 그 단어 옆에 오는 단어를 본다. 
 * 
 * boy I
 * 분류기가 맞았다 vs 분류기가 틀렸다로 구분해서 작성
 * ex) 분류된문장의 첫번째 단어가 boy이고, boy가 words에서 2번째(=X, 0부터 시작)일 때
 * 맞았다: classifierPer[2][X]=0.2
 * 틀렸다: classifierPer[0,1, 3, 4, ..., n-1][X] = 0.8
 * 단어 후보들 중 가장 확률 높은걸 고르면 됨.
 * 
 * 그리고, 첫번째 단어로 올 확률
 * [a, b, c, d, e] 이렇게 있을 때, 첫번째 단어가 boy일 확률 = 0.2 * c
 * 첫번째 단어가 원래는 i번째 단어일 확률(A) = classifierPer[i][X] * firstWordPer[i]
 * 
 * 
 * 두번째 단어가 원래는 j번째 단어일 확률 = classifierPer[j][Y] * nextWordPer[i][j]
*/
int m, q;
vector<string> classified;
unordered_map<string, int> words;
vector<string> wordsVec;
vector<vector<string>> answers;

double firstWordPer[501]; // [i]: i번째 단어가 문장의 첫 번째에 올 확률
double nextWordPer[501][501]; // [i][j]: i번째 단어 오른쪽 단어가 j번째 단어일 확률
double classifierPer[501][501]; // [i][j]: 분류기가 i번째 단어를 j번째 단어로 인식할 확률
double dp[501][501]; // [i][j]: 문장상 i번째 위치에 단어상 j번째 단어가 올 확률

double calProb(int linePos, int wordPos) // linePos 위치에 wordPos 단어가 올 확률 = for(lineNo = 0..linePos - 1, wordIdx = 0..n-1) Probability sum
{
    double& ret = dp[linePos][wordPos];
    if (ret != -1) return ret;

    if (linePos == 0) {
        return ret = classifierPer[wordPos][words[classified[linePos]]] * firstWordPer[wordPos];
    }

    double p = 0;
    for (auto it = words.begin(); it != words.end(); ++it) {
        p += calProb(linePos - 1, it->second) * nextWordPer[it->second][wordPos] * classifierPer[wordPos][words[classified[linePos]]];
    }

    return ret = p;
}

void init()
{
    wordsVec = vector<string>();
    words = unordered_map<string, int>();
    answers = vector<vector<string>>();

    for (int i = 0; i < 501; ++i) {
        for (int j = 0; j < 501; ++j) {
            dp[i][j] = -1;
        }
    }
}

void reconstruct(vector<string>& answer)
{
    for (int i = 0; i < classified.size(); ++i) {
        double p = 0;
        int idx = 0;
        for (auto iter = words.begin(); iter != words.end(); ++iter) {
            double cand = calProb(i, iter->second);
            if (p < cand) {
                p = cand;
                idx = iter->second;
            }
        }
        answer.push_back(wordsVec[idx]);
    }
}

int main()
{
    cin >> m >> q;
    string word;

    init();

    for (int i = 0; i < m; ++i)
    {
        cin >> word;
        words[word] = i;
        wordsVec.push_back(word);
    }

    double per;
    for (int i = 0; i < m; ++i)
    {
        cin >> per;
        firstWordPer[i] = per;
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> per;
            nextWordPer[i][j] = per;
        }
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> per;
            classifierPer[i][j] = per;
        }
    }

    int cnt;

    while (q--)
    {
        cin >> cnt;
        classified = vector<string>();
        while (cnt--)
        {
            cin >> word;
            classified.push_back(word);
        }

        vector<string> answer;
        reconstruct(answer);

        answers.push_back(answer);
    }

    for (auto& ans : answers) {
        for (string& word : ans) {
            cout << word << " ";
        }
        cout << endl;
    }
}
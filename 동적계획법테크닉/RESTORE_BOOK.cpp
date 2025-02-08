#include <string>
#include <iostream>
#include <vector>
using namespace std;

const int MINLEN = -1;

int k;
int cached[15][1<<15];
int overlap[15][15];
vector<string> words;

void init()
{
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < (1<<15); ++j) {
            cached[i][j] = -1;
        }
    }
}

void delUselessWords()
{
    int idx = 0;
    while (true) {
        bool del = false;
        for (int i = idx + 1; i < words.size(); ++i) {
            if (words[idx].size() <= words[i].size()) {
                for (int jump = 0; i <= words[i].size() - words[idx].size(); ++jump) {
                    if (words[idx] == words[i].substr(jump, words[idx].size())) {
                        del = true;
                        break;
                    }
                }

                if (del) {
                    break;
                }
            }
        }

        if (del) {
            words.erase(words.begin() + idx);
        } else {
            ++idx;
        }
    }
}


void calOverlap()
{
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            
            int saved = 0;
            for (int jump = 1; jump < max(words[i].size(), words[j].size()); ++jump) {
                bool flag = true;
                for (int k = 0; k < jump; ++k) {
                    if (words[i][words[i].size() - jump + k] != words[j][k]) {
                        flag = false;
                        break;
                    }
                }

                if (flag) {
                    saved = jump;
                }
            }

            overlap[i][j] = saved;
        }
    } 
}

int restore(int last, int used) // 최대 overlap 합 구하는 함수
{
    int& ret = cached[last][used];
    if (ret != -1) return ret;

    ret = MINLEN;
    for (int i = 0; i < k; ++i) {
        if ((used & (1<<i)) == 0) {
            ret = max(ret, overlap[last][i] + restore(i, (used | (1<<i))));
        }
    }

    return ret;
}

string reconstruct(int last, int used)
{
    if (used == (1<<(k-1))) return "";

    for (int i = 0; i < k; ++i) {
        if ((used & (1<<i)) == 1) continue;
        int cand = overlap[last][i] + restore(i, (used | (1<<i)));
        if (cand == restore(last, used)) {
            return words[i].substr(overlap[last][i]) + reconstruct(i, (used | (1<<i)));
        }
    }
    return NULL;
}

int main()
{
    int C;
    cin >> C;
    while (C--)
    {
        cin >> k;
        init();

        string temp;
        for (int i = 0; i < k; ++i) {
            cin >> temp;
            words.push_back(temp);
        }
        
        delUselessWords();       
        calOverlap();

        int maxOverlapSize = 0;
        int tempVal = 0;
        int idx = 0;
        for (int i = 0; i < k; ++i) {
            tempVal = restore(i, (1<<i));
            if (maxOverlapSize < tempVal) {
                idx = i;
            }
        }

        cout << words[idx] + reconstruct(idx, 1<<idx);
    }
}
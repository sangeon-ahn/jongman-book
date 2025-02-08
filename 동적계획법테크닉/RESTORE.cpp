#include <iostream>
#include <string>
#include <vector>
using namespace std;

int k;
vector<string> words;
vector<string> answers;
bool visited[16];

/**
 * ab + bc = abc
 * abc + bc = abc
 * abc + cef = abcef
 * abcef + ah = abcefah
 * abcefah + efahgg = abcefahgg
 * = ab + bc + bc + cef + ah + efahgg
 * 
 */

vector<int> idxes;

void init()
{
    words = vector<string>();
    idxes = vector<int>();
    for (int i = 0; i < 16; ++i) visited[i] = false;
}

string compressed(string str1, string str2) // str1 <- str2 방향으로 겹쳐지도록.
{
    if (str1.size() == 0) return str2;
    if (str2.size() == 0) return str1;
    
    int saved = 0;
    int jump = 1;
    
    int maxSize = max(str1.size(), str2.size());
    while (jump <= maxSize) {
        bool flag = true;
        for (int i = 0; i < jump; ++i) {
            if (i >= str2.size()) break;
            if (str1[str1.size() - jump + i] != str2[i]) {
                flag = false;
                break;
            }
        }

        if (flag) {
            saved = jump;
        }
        ++jump;
    }

    string result = str1;

    if (saved >= str2.size()) return result;
    
    result += str2.substr(saved);

    return result;
}

string restore(string prev, int cnt)
{
    if (cnt == words.size()) {
        // cout << prev << endl;
        return prev;
    }

    string ret = "";
    int minLen = 987654321;

    for (int i = 0; i < words.size(); ++i) {
        if (visited[i]) continue;
        visited[i] = true;
        string cand = restore(compressed(prev, words[i]), cnt + 1);
        if (minLen > cand.length()) {
            ret = cand;
            minLen = cand.length();
        }
        visited[i] = false;
    }

    return ret;
}

int main()
{
    answers = vector<string>();

    int C;
    cin >> C;
    while (C--)
    {
        init();
        cin >> k;
        string temp;
        for (int i = 0; i < k; ++i) {
            cin >> temp;
            words.push_back(temp);
        }

        answers.push_back(restore("", 0));
    }

    for (string& str : answers) {
        cout << str << endl;
    }
}
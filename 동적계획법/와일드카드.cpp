#include <iostream>
#include <string>
#include <vector>
using namespace std;


// 한 문자씩 대조하며 valid하면 넘어가다가, * 나오면 *이 커버할 name 영역을 후보군 하나씩 체크하며 하나라도 true면 끝
bool canMatch(const string& card, const string& name)
{
    int pos = 0;
    while (pos < card.size() && pos < name.size() && (card[pos] == '?' || card[pos] == name[pos])) {
        ++pos;
    }

    // 왜 빠져나왔는지 체크
    
    // 1. wildcard끝까지 갔을 경우 -> * 없어서 남은 길이가지고 판단 가능
    if (pos == card.size()) {
        return card.size() == name.size();
    } 

    // 2. * 만나서 중단된 경우
    if (card[pos] == '*') {
        // pos가 커버할 name 영역 순회하면서 판단
        for (int jump = 0; pos + jump <= name.size(); ++jump) {
            if (canMatch(card.substr(pos + 1), name.substr(pos + jump))) {
                return true;
            }
        }
    }
    return false;
}

int main()
{
    vector<string> answer;

    int C;
    cin >> C;
    while (C--)
    {
        string wildCard;
        int n;
        cin >> wildCard >> n;
        
        string name;
        for (int i = 0; i < n; ++i) {
            cin >> name;
            
            if (canMatch(wildCard, name)) {
                answer.push_back(name);
            }
        }

    }
    for (string s : answer) {
        cout << s << endl;
    }
}
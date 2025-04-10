#include <iostream>
#include <stack>
#include <string>
using namespace std;

string s;
int main() {
    int C;
    cin >> C;
    while (C--) {
        cin >> s;

        stack<char> st;
        bool flag = true; 
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
                st.push(s[i]);
                continue;
            }

            if (st.empty())
                flag = false;

            else if (s[i] == ')' && st.top() != '(')
                flag = false; 

            else if (s[i] == '}' && st.top() != '{')
                flag = false;

            else if (s[i] == ']' && st.top() != '[')
                flag = false;
            
            if (!flag) {
                cout << "NO" << endl;
                break;
            }
            st.pop();
        }

        if (flag) {
            if (st.empty())
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
        }
}
}

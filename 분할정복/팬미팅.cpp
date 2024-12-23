#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    int C;
    while (C--)
    {
        string idols;
        string fans;
        cin >> idols >> fans;

        vector<int> idols_bit;
        idols_bit.resize(idols.length());
        vector<int> fans_bit;
        fans_bit.resize(fans.length());

        for (int i = 0; i < idols.length(); ++i) {
            idols_bit[i] = idols[i] == 'w' ? 0 : 1;
        } 
        for (int i = fans.length() - 1; i >= 0; ++i) {
            fans_bit[i] = fans[i] == 'w' ? 0 : 1;
        }

        vector<int> mul_result = karatsuba(idols_bit, fans_bit); // 큰 수의 곱 알고리즘, N^log3

        int answer = 0;
        for (int i = idols_bit.size() - 1; i < fans_bit.size(); ++i) {
            if(mul_result[i] == 0) {
                ++answer;
            }
        }

        return answer;
    }
}
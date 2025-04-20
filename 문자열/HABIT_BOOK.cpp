/**
 * 문자열 A에서 부분 문자열 B가 K번 출현한다는 말은 A의 모든 접미사 중에 B 를 접두사로 가지는 접미사가 K개 있다는거다.
 * 그리고 이 K개 접미사들은 suffix array에서 서로 연속되게 인접해 있다.
 * 따라서, 이 K개 접미사들의 시작 접미사와 맨 마지막 접미사 간에 공통 접두사가 존재한다면 그 사이 접미사들 또한 공통 접두사가 존재하므로 K개의 부분문자열이 있음을 알 수 있다.
*/
#include <string>
#include <vector>
using namespace std;
int habit(const string& s, int k) {
    vector<int> suffix_array = getSuffixArray(s);
    // i 와 (i + k - 1) 번째 suffix 를 검사해야 함.
    int max_val = 0;
    for (int i = 0; i <= suffix_array.size() - k; ++i) {
        int cp = getCommonPrefixSize(s, suffix_array[i], suffix_array[i + k - 1]);
        if (max_val < cp) {
            max_val = cp;
        }
    }
    return max_val;
}
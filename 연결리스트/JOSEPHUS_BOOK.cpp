#include <list>
#include <iostream>
using namespace std;

void josephus(int n, int k) {
    list<int> survivors;
    for (int i = 1; i <= n; ++i) survivors.push_back(i);

    list<int>::iterator it = survivors.begin();
    while (n > 2) {
        it = survivors.erase(it);
        --n;
        if (it == survivors.end()) it = survivors.begin();

        for (int i = 0; i < k - 1; ++i) {
            ++it;
            if (it == survivors.end()) it = survivors.begin();
        }
    }

    cout << survivors.front() << " " << survivors.back() << endl;
}

int main() {
    josephus(6, 3);
}
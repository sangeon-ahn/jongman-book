#include <iostream>
#include <deque>
#include <vector>
#include <unordered_map>
using namespace std;

struct doublyll {
    doublyll* prev;
    doublyll* next;
    int val;
};

int N, K;

doublyll* connect(doublyll* elem1, doublyll* elem2) {
    elem1->next = elem2;
    elem2->prev = elem1;
    return elem2;
}


void detach(doublyll* elem) {
    elem->prev->next = elem->next;
    elem->next->prev = elem->prev;
}

int main() {
    int C;
    cin >> C;
    while (C--) {
        cin >> N >> K;
    
        doublyll* head = new doublyll();
        head->val = 1;
        head->prev = NULL;
        doublyll* tail = new doublyll();
        tail->val = N;
        tail->next = NULL;
        
        connect(head, tail);

        doublyll* prev = head;
        doublyll* temp;
        for (int i = 1; i < N - 1; ++i) {
            temp = new doublyll();
            temp->val = i + 1;
            connect(prev, temp);
            prev = temp;
        }
        connect(prev, tail);
        connect(tail, head);

        int cnt = 0;
        doublyll* target = head;
        while (cnt < N - 2) {
            detach(target);
            temp = target->next;
            delete target;

            int k_cnt = 1;
            while (k_cnt < K) {
                temp = temp->next;
                ++k_cnt;
            }
            target = temp;
            ++cnt;
        }
        
        cout << target->val << " " << target->next->val << endl;
        delete target->next;
        delete target;
    }
}
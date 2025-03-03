#include <iostream>

using namespace std;

struct Node {
    int d;
    Node* next;
};

struct St {
    Node* top = nullptr;
};

bool empty(St& s) {
    return s.top == nullptr;
};

void push(St& s, int value) {
    Node* nn = new Node;
    nn->d = value;
    nn->next = s.top;
    s.top = nn;
}

int pop(St& s) {
    if (empty(s)) {
        return -1;
    }
    int value = s.top->d;
    Node* temp = s.top;
    s.top = s.top->next;
    delete temp;
    return value;
}

int peek(St& s) {
    if (empty(s)) {
        return -1;
    }
    return s.top->d;
}


void init_s1(St& s1, int n) {
    for (int i = n; i >= 1; --i) {
        push(s1, i);
    }
}

void drag(St& s1, St& s2, int k) {
    for (int i = 0; i < k - 1; ++i) {
        if (empty(s1)) {
            while (!empty(s2)) {
                push(s1, pop(s2));
            }
        }
        push(s2, pop(s1));
    }
}


void refill(St& s1, St& s2) {
    while (!empty(s2)) {
        push(s1, pop(s2));
    }
}

void p_iter(St& s1, St& s2, int k, int& n) {
    drag(s1, s2, k);

    if (empty(s1)) {
        refill(s1, s2);
    }
    pop(s1);
    n--;

    refill(s1, s2);
}


int f(int n, int k) {
    St s1;
    St s2;

    init_s1(s1, n);

    while (n > 1) {
        p_iter(s1, s2, k, n);
    }

    return pop(s1);
}

int main() {
    int n, k;
    cin >> n;
    cin >> k;

    int last = f(n, k);
    cout << last << endl;

    return 0;
}

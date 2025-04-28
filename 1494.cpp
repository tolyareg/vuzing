#include <iostream>

using namespace std;

struct St {
    int* items;
    int capacity;
    int top_index;

    St(int size) : capacity(size), top_index(-1) {
        items = new int[capacity];
    }

    ~St() {
        delete[] items;
    }
};

bool isEmpty(St* a) {
    return a->top_index == -1;
}

void push(St* a, int value) {
    if (a->top_index >= a->capacity - 1) {
        return;
    }
    a->items[++a->top_index] = value;
}

int pop(St* a) {
    if (isEmpty(a)) {
        return -1;
    }
    return a->items[a->top_index--];
}


int peek(St* a) {
    if (isEmpty(a)) {
        return -1;
    }
    return a->items[a->top_index];
}

int main() {
    int n;
    cin >> n;

    int* arr = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    St queueu(n);
    int arr_idx = 0;

    for (int current_ball = 1; current_ball <= n; ++current_ball) {
        push(&queueu, current_ball);

        while (!isEmpty(&queueu) && arr_idx < n && peek(&queueu) == arr[arr_idx]) {
            pop(&queueu);
            arr_idx++;
        }
    }

    if (arr_idx == n) {
        cout << "Not a proof" << endl;
    } else {
        cout << "Cheater" << endl;
    }

    delete[] arr;

    return 0;
}

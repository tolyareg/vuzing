#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct IntNode {
    int data;
    IntNode* prev;
    IntNode* next;

    IntNode(int val) : data(val), prev(nullptr), next(nullptr) {}
};

struct IntList {
    IntNode* head;
    IntNode* tail;

    IntList() : head(nullptr), tail(nullptr) {}

    ~IntList() {
        IntNode* current = head;
        while (current) {
            IntNode* next = current->next;
            delete current;
            current = next;
        }
    }

    void append(int val) {
        IntNode* newNode = new IntNode(val);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
};

struct ListListNode {
    IntList* data;
    ListListNode* prev;
    ListListNode* next;

    ListListNode(IntList* list) : data(list), prev(nullptr), next(nullptr) {}

    ~ListListNode() {
        delete data;
    }
};

struct ListOfLists {
    ListListNode* head;
    ListListNode* tail;

    ListOfLists() : head(nullptr), tail(nullptr) {}

    ~ListOfLists() {
        ListListNode* current = head;
        while (current) {
            ListListNode* next = current->next;
            delete current;
            current = next;
        }
    }

    void appendList(IntList* list) {
        ListListNode* newNode = new ListListNode(list);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void printIntList(IntList* list) {
        IntNode* current = list->head;
        cout << "[";
        while (current) {
            cout << current->data;
            if (current->next) {
                cout << ", ";
            }
            current = current->next;
        }
        cout << "]";
    }

    void printListOfLists() {
        ListListNode* currentOuter = head;
        cout << "List of Lists:" << endl;
        while (currentOuter) {
            printIntList(currentOuter->data);
            if (currentOuter->next) {
                cout << ", ";
            }
            currentOuter = currentOuter->next;
        }
        cout << endl;
    }

    void sortListOfLists() {
        if (!head || !head->next) {
            return;
        }

        bool swapped;
        do {
            swapped = false;
            ListListNode* currentOuter = head;
            ListListNode* nextOuter = head->next;
            ListListNode* prevOuter = nullptr;

            while (nextOuter) {
                int val1 = (currentOuter->data->head) ? (currentOuter->data->head->data) : -999999;
                int val2 = (nextOuter->data->head) ? (nextOuter->data->head->data) : -999999;

                if (val1 > val2) {
                    swapped = true;

                    if (prevOuter) {
                        prevOuter->next = nextOuter;
                    } else {
                        head = nextOuter;
                    }

                    currentOuter->next = nextOuter->next;
                    nextOuter->prev = prevOuter;

                    currentOuter->prev = nextOuter;
                    nextOuter->next = currentOuter;

                    if (currentOuter->next) {
                        currentOuter->next->prev = currentOuter;
                    } else {
                        tail = currentOuter;
                    }

                    prevOuter = nextOuter;
                    nextOuter = currentOuter->next;
                } else {
                    prevOuter = currentOuter;
                    currentOuter = nextOuter;
                    nextOuter = nextOuter->next;
                }
            }
        } while (swapped);
    }
};


int main() {
    ListOfLists listOfLists;
    ifstream inputFile("data.txt");

    if (!inputFile.is_open()) {
        cerr << "Error opening file data.txt" << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line)) {
        IntList* intList = new IntList();
        stringstream ss(line);
        int number;
        while (ss >> number) {
            intList->append(number);
        }
        listOfLists.appendList(intList);
    }

    inputFile.close();

    cout << "Original List of Lists:" << endl;
    listOfLists.printListOfLists();

    listOfLists.sortListOfLists();

    cout << "\nSorted List of Lists:" << endl;
    listOfLists.printListOfLists();

    return 0;
}

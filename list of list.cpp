#include <iostream>
using namespace std;

struct Subnode {
    int num;
    Subnode* next;
};

struct Node {
    int num;
    Node* next; 
    Subnode* sublist;
};

Node* Node(int k) {
    Node* node = new Node();
    node->num = k;
    node->next = nullptr;
    node->sublist = nullptr;
    return node;
}

// Node* node = new Node(); - выделяем память под новый узел типа Node в динамической памяти (в куче) с помощью оператора 'new'.
//                         Оператор 'new Node()' возвращает указатель на выделенную память.
//                         Результат присваивается указателю 'node' типа Node*.
// node->num = k; - устанавливаем значение 'num' для созданного узла равным переданному аргументу 'k'.
//             '->' - оператор доступа к члену структуры через указатель.
// node->next = nullptr; - инициализируем указатель 'next' нового узла значением nullptr (нулевой указатель).
//                     nullptr означает, что узел пока не указывает ни на какой следующий узел.
//                     Это важно для инициализации, чтобы избежать случайных ссылок.
// node->sublist = nullptr; - инициализируем указатель 'sublist' нового узла значением nullptr.
//                        nullptr означает, что узел пока не связан ни с каким подсписком.
// return node; - возвращаем указатель 'node' на созданный и инициализированный узел.




Subnode* Subnode(int k) {
    Subnode* sub = new Subnode();
    sub->num = k;
    sub->next = nullptr; // Initialize next pointer
    return sub;
}

// Subnode* sub = new Subnode(); - выделяем память под новый узел подсписка типа Subnode в динамической памяти (в куче) с помощью оператора 'new'.
//                            Оператор 'new Subnode()' возвращает указатель на выделенную память.
//                            Результат присваивается указателю 'sub' типа Subnode*.
// sub->num = k; - устанавливаем значение 'num' для созданного узла подсписка равным переданному аргументу 'k'.
// sub->next = nullptr; - инициализируем указатель 'next' нового узла подсписка значением nullptr.
//                    nullptr означает, что узел пока не указывает ни на какой следующий узел подсписка.
// return sub; - возвращаем указатель 'sub' на созданный и инициализированный узел подсписка.




Node* appendNode(Node* head, Node* newNode) {
    if (head == nullptr) {
        return newNode; 
    }
    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = newNode;
    return head;
}

// if (head == nullptr) { - проверяем, является ли список пустым (голова списка равна nullptr).
//     return newNode; // If list is empty, new node becomes head - если список пуст, то новый узел становится головой списка, и функция возвращает указатель на него.
// }
// Node* current = head; - создаем указатель 'current' и устанавливаем его на голову списка. 'current' будет использоваться для прохода по списку.
// while (current->next != nullptr) { - начинаем цикл while, который будет выполняться, пока указатель 'next' текущего узла 'current' не равен nullptr.
//                                  Это означает, что мы не достигли конца списка (последний узел в односвязном списке имеет 'next' = nullptr).
//     current = current->next; // Traverse to the end of the list - перемещаем 'current' на следующий узел в списке, присваивая ему значение 'current->next'.
//                                 Таким образом, 'current' "движется" вдоль списка к концу.
// } // цикл завершится, когда 'current' будет указывать на последний узел списка.
// current->next = newNode; // Append the new node at the end - после цикла 'current' указывает на последний узел. Устанавливаем 'next' указатель последнего узла на 'newNode', тем самым добавляя 'newNode' в конец списка.
// return head; // Return the head of the list (head might not change, but good practice to return) - возвращаем указатель на голову списка.
//              В данном случае, если список изначально не был пустым, голова списка не изменится, но функция все равно возвращает 'head' для единообразия.




Subnode* appendSubnode(Subnode* head, Subnode* newSub) {
    if (head == nullptr) {
        return newSub;
    }
    Subnode* current = head;
    while (current->next != nullptr) {
        current = current->next; 
    }
    current->next = newSub;
    return head;
}
// Функция appendSubnode добавляет новый узел подсписка (newSub) в конец подсписка.
// Subnode* appendSubnode(Subnode* head, Subnode* newSub) - объявление функции. Возвращает указатель на Subnode (Subnode*), который является головой подсписка.
//                                        Принимает два аргумента: 'head' - указатель на голову текущего подсписка, и 'newSub' - указатель на новый узел подсписка для добавления.
// Логика функции полностью аналогична appendNode, но работает с узлами типа Subnode и подсписком.




void print(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        cout << current->num << ": ";
        Subnode* sub = current->sublist;
        while (sub != nullptr) {
            cout << sub->num << " ";
            sub = sub->next;
        }
        cout << endl;
        current = current->next;
    }
}
// Node* current = head; - создаем указатель 'current' на узел основного списка и устанавливаем его на голову основного списка.
// while (current != nullptr) { - начинаем внешний цикл while, который выполняется, пока 'current' не равен nullptr.
//                              Это означает, что мы не достигли конца основного списка.
//     cout << current->num << ": "; - выводим значение 'num' текущего узла основного списка, за которым следует двоеточие и пробел.
//     Subnode* sub = current->sublist; - создаем указатель 'sub' на узел подсписка и устанавливаем его на подсписок текущего узла основного списка ('current->sublist').
//     while (sub != nullptr) { - начинаем внутренний цикл while, который выполняется, пока 'sub' не равен nullptr.
//                               Это означает, что мы не достигли конца текущего подсписка.
//         cout << sub->num << " "; - выводим значение 'num' текущего узла подсписка, за которым следует пробел.
//         sub = sub->next; // Changed from prev to next for forward iteration - перемещаем 'sub' на следующий узел подсписка, присваивая ему значение 'sub->next'.
//     } // внутренний цикл завершится, когда все узлы подсписка будут выведены.
//     cout << endl; - выводим символ новой строки, чтобы перейти на следующую строку для следующего узла основного списка.
//     current = current->next; // Changed from prev to next for forward iteration - перемещаем 'current' на следующий узел основного списка, присваивая ему значение 'current->next'.
// }




void freeSublist(Subnode* head) {
    Subnode* current = head;
    while (current != nullptr) {
        Subnode* next = current->next;
        delete current;
        current = next;
    }
}

// Subnode* current = head; - создаем указатель 'current' на узел подсписка и устанавливаем его на голову подсписка.
// while (current != nullptr) { - начинаем цикл while, который выполняется, пока 'current' не равен nullptr.
//                              Это означает, что мы не достигли конца подсписка.
//     Subnode* next = current->next; - создаем временный указатель 'next' и сохраняем в нем указатель на следующий узел ('current->next').
//                                  Это необходимо, потому что после удаления текущего узла ('current'), мы потеряем доступ к следующему узлу, если не сохраним его указатель.
//     delete current; - освобождаем память, на которую указывает 'current' (удаляем текущий узел). Оператор 'delete' освобождает память, выделенную с помощью 'new'.
//     current = next; - перемещаем 'current' на следующий узел, который мы сохранили в 'next' перед удалением текущего узла.
// }




void freeListofLists(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        freeSublist(current->sublist);
        Node* next = current->next;
        delete current;
        current = next;
    }
}

// { ... } - тело функции.
// Node* current = head; - создаем указатель 'current' на узел основного списка и устанавливаем его на голову основного списка.
// while (current != nullptr) { - начинаем цикл while, который выполняется, пока 'current' не равен nullptr.
//                              Это означает, что мы не достигли конца основного списка.
//     freeSublist(current->sublist); // Free sublist for current node - вызываем функцию freeSublist для подсписка текущего узла основного списка ('current->sublist').
//                                   Это освобождает память, выделенную для всех узлов подсписка, связанных с текущим узлом основного списка.
//     Node* next = current->next; - создаем временный указатель 'next' и сохраняем в нем указатель на следующий узел основного списка ('current->next').
//                                 Это необходимо, потому что после удаления текущего узла ('current'), мы потеряем доступ к следующему узлу, если не сохраним его указатель.
//     delete current; - освобождаем память, на которую указывает 'current' (удаляем текущий узел основного списка).
//     current = next; - перемещаем 'current' на следующий узел основного списка, который мы сохранили в 'next' перед удалением текущего узла.
// } // цикл завершится, когда все узлы основного списка и их подсписки будут пройдены и удалены.





int main() {
    int n;
    cin >> n;
    
    Node* head = nullptr;

    for (int i = 0; i < n; i++) {
        Node* newNode = Node(i + 1);
        Subnode* subHead = nullptr; 

        for (int j = 0; j < n; j++) {
            int a;
            cin >> a;

            if (a != 0) {
                Subnode* newSub = Subnode(j + 1);
                subHead = appendSubnode(subHead, newSub);
            }
        } 

        newNode->sublist = subHead;
        head = appendNode(head, newNode);
    }

    print(head);

    freeListofLists(head);
    return 0;
}

#include <iostream>
#include <string>

using namespace std;

// Struct for Node (not actually used for stack in array-based approach, but kept if needed for potential linked list stack later)
// struct Node {
//     string data;
//     Node* next;
// };

// Struct for Stack (Array-based implementation)
struct St {
    string* items; // Array to store stack items (strings)
    int capacity;
    int top_index;

    St(int size) : capacity(size), top_index(-1) {
        items = new string[capacity];
    }

    ~St() {
        delete[] items;
    }
};

bool isEmpty(St* s) {
    return s->top_index == -1;
}

bool isFull(St* s) {
    return s->top_index >= s->capacity - 1;
}

void push(St* s, string value) {
    if (isFull(s)) {
        cerr << "Stack overflow!" << endl;
        return; // Or handle overflow as needed
    }
    s->items[++s->top_index] = value;
}

string pop(St* s) {
    if (isEmpty(s)) {
        return ""; // Or handle underflow as needed, returning empty string for now
    }
    return s->items[s->top_index--];
}

string peek(St* s) {
    if (isEmpty(s)) {
        return ""; // Or handle empty peek as needed, returning empty string for now
    }
    return s->items[s->top_index];
}

// Function to get precedence of operators (same as before)
int precedence(string op) {
    if (op == "OR") return 1;
    if (op == "+") return 2;
    if (op == "*") return 4;
    if (op == "AND") return 3;
    if (op == "NOT" || op == "!") return 5;
    return 0; // For '(' and other cases
}

// Function to check if a token is an operator (same as before)
bool isOperator(string token) {
    return (token == "OR" || token == "AND" || token == "NOT" || token == "!" || token == "+" || token == "*");
}

// Function to check if a token is an operand (letter A-Z or TRUE/FALSE) (same as before)
bool isOperand(string token) {
    if (token == "TRUE" || token == "FALSE") return true;
    if (token.length() == 1 && token[0] >= 'A' && token[0] <= 'Z') return true;
    return false;
}

int main() {
    string infix_expression = "NOT((A OR NOT B) AND (A OR B)) OR NOT (A AND NOT B OR TRUE)";
    string rpn_expression = "";
    St operator_stack(50); // Initialize our struct-based stack with a capacity (adjust as needed)
    string current_token;

    for (int i = 0; i < infix_expression.length(); ++i) {
        char currentChar = infix_expression[i];
        current_token = "";
        current_token += currentChar;

        if (currentChar == ' ') {
            continue; // Skip whitespace
        } else if (isalpha(currentChar)) {
            rpn_expression += current_token;
            rpn_expression += " ";
        } else if (isdigit(currentChar)) { // If you want to handle numbers
            rpn_expression += current_token;
            rpn_expression += " ";
        } else if (currentChar == '(') {
            push(&operator_stack, current_token); // Use our push function
        } else if (currentChar == ')') {
            while (!isEmpty(&operator_stack) && peek(&operator_stack) != "(") { // Use our isEmpty and peek
                rpn_expression += pop(&operator_stack); // Use our pop
                rpn_expression += " ";
            }
            if (!isEmpty(&operator_stack) && peek(&operator_stack) == "(") { // Use our isEmpty and peek
                pop(&operator_stack); // Pop '('
            } else {
                cerr << "Mismatched parentheses" << endl;
                return 1;
            }
        } else if (currentChar == 'N' && infix_expression.substr(i, 3) == "NOT") {
            current_token = "NOT";
            i += 2;
            while (!isEmpty(&operator_stack) && precedence(peek(&operator_stack)) >= precedence(current_token)) { // Use our isEmpty and peek
                rpn_expression += pop(&operator_stack); // Use our pop
                rpn_expression += " ";
                pop(&operator_stack); // Pop twice in original code - corrected to pop once in while loop
            }
            push(&operator_stack, current_token); // Use our push
        }
         else if (currentChar == 'O' && infix_expression.substr(i, 2) == "OR") {
            current_token = "OR";
            i += 1;
            while (!isEmpty(&operator_stack) && precedence(peek(&operator_stack)) >= precedence(current_token)) { // Use our isEmpty and peek
                rpn_expression += pop(&operator_stack); // Use our pop
                rpn_expression += " ";
            }
            push(&operator_stack, current_token); // Use our push
        } else if (currentChar == 'A' && infix_expression.substr(i, 3) == "AND") {
            current_token = "AND";
            i += 2;
             while (!isEmpty(&operator_stack) && precedence(peek(&operator_stack)) >= precedence(current_token)) { // Use our isEmpty and peek
                rpn_expression += pop(&operator_stack); // Use our pop
                rpn_expression += " ";
            }
            push(&operator_stack, current_token); // Use our push
        } else if (currentChar == 'T' && infix_expression.substr(i, 4) == "TRUE") {
            current_token = "TRUE";
            i += 3;
            rpn_expression += current_token;
            rpn_expression += " ";
        } else if (currentChar == 'F' && infix_expression.substr(i, 5) == "FALSE") {
            current_token = "FALSE";
            i += 4;
            rpn_expression += current_token;
            rpn_expression += " ";
        }
        else if (isOperator(current_token)) {
             while (!isEmpty(&operator_stack) && precedence(peek(&operator_stack)) >= precedence(current_token)) { // Use our isEmpty and peek
                rpn_expression += pop(&operator_stack); // Use our pop
                rpn_expression += " ";
            }
            push(&operator_stack, current_token); // Use our push
        }
    }

    while (!isEmpty(&operator_stack)) { // Use our isEmpty
        rpn_expression += pop(&operator_stack); // Use our pop
        rpn_expression += " ";
    }

    cout << "Infix Expression: " << infix_expression << endl;
    cout << "Reverse Polish Notation: " << rpn_expression << endl;

    return 0;
}

#include<iostream>
using namespace std;


class Node {
public:
    char command;
    int movement;
    Node* next;

    Node(char c, int m) {
        command = c;
        movement = m;
        next = NULL;
    }
};


class Stack {
public:
    Node* top;

    Stack() {
        top = NULL;
    }

    void push(char command, int movement) {

        Node* newNode = new Node(command, movement);
        newNode->next = top;
        top = newNode;
    }

    bool isEmpty() {
        return top == NULL;
    }

    Node* pop() {

        if(top == NULL) return NULL;

        Node* temp = top;
        top = top->next;
        temp->next = NULL;
        return temp;
    }

    void display() {

        if(top == NULL) {
            cout << "Stack is empty." << endl;
            return;
        }

        Node* temp = top;

        cout << "Remaining stack: ";

        while(temp != NULL) {
            cout << temp->command;
            if(temp->next != NULL) cout << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {

    int n;
    cout << "Enter number of commands: ";
    cin >> n;

    Stack s;

    int position = 0;
    int successfulMovements = 0;
    int successfulUndos = 0;

    cout << "Enter commands: ";

    for(int i = 0; i < n; i++) {

        char command;
        cin >> command;

        if(command == 'R') {

            int newPosition = position + 1;
            if(newPosition >= 0) {
                position = newPosition;
                s.push('R', 1);
                successfulMovements++;
            }
        }

        else if(command == 'L') {

            int newPosition = position - 1;

            if(newPosition >= 0) {
                position = newPosition;
                s.push('L', -1);
                successfulMovements++;
            }
        }

        else if(command == 'J') {

            int newPosition = position + 2;
            if(newPosition >= 0) {
                position = newPosition;
                s.push('J', 2);
                successfulMovements++;
            }
        }

        else if(command == 'B') {

            if(!s.isEmpty()) {
                Node* temp = s.pop();
                position = position - temp->movement;
                delete temp;
                successfulUndos++;
            }
        }
    }

    cout << "\n========== RESULT ==========\n";
    cout << "Final Position: " << position << endl;
    cout << "Successful Movements: " << successfulMovements << endl;
    cout << "Successful Undo Operations: " << successfulUndos << endl;

    s.display();
    return 0;
}
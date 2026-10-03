#include <iostream>
#include <string>
using namespace std;

class Node
{
public:
    string data;
    Node* next;
    Node* prev;

    Node(string d)
    {
        data = d;
        next = NULL;
        prev = NULL;
    }
};


class LinkedList
{
public:
    Node* head;
    Node* tail;

    LinkedList()
    {
        head = NULL;
        tail = NULL;
    }

    void insert(string value)
    {
        Node* newNode = new Node(value);

        if (head == NULL)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Evaluate expression inside brackets / whole expression
    int calculate(Node*& current)
    {
        int result = 0;
        char operation = '+';

        while (current != NULL)
        {
            // Closing bracket means this part is finished
            if (current->data == ")")
            {
                current = current->next;
                break;
            }

            int number;

            // Opening bracket
            if (current->data == "(")
            {
                current = current->next;

                // Recursively calculate inside brackets
                number = calculate(current);
            }
            else
            {
                // Convert string number to integer
                number = stoi(current->data);
                current = current->next;
            }

            // Perform previous operation
            if (operation == '+')
            {
                result += number;
            }
            else if (operation == '-')
            {
                result -= number;
            }
            else if (operation == '*')
            {
                result *= number;
            }
            else if (operation == '/')
            {
                result /= number;
            }

            // Get next operator
            if (current != NULL && current->data != ")")
            {
                operation = current->data[0];
                current = current->next;
            }
        }

        return result;
    }

    int solve()
    {
        Node* current = head;
        return calculate(current);
    }

    void display()
    {
        Node* temp = head;

        while (temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }

        cout << endl;
    }
};


int main()
{
    LinkedList expression;

    // 10 + (12 * (2) - 2)
    expression.insert("10");
    expression.insert("+");
    expression.insert("(");
    expression.insert("12");
    expression.insert("*");
    expression.insert("(");
    expression.insert("2");
    expression.insert(")");
    expression.insert("-");
    expression.insert("2");
    expression.insert(")");

    cout << "Expression: ";
    expression.display();

    cout << "Answer: " << expression.solve() << endl;

    return 0;
}
#include<iostream>
using namespace std;

class Node {
    public: 
        int data;
        Node* next;

        Node(int val) {
            data = val;
            next = NULL;
        }
};

class List {
    Node* head;
    Node* tail;

    public:
        List() {
            head = tail = NULL;
        }

        void push_front(int val) {
            Node* newNode = new Node(val);
            if (head==NULL) {
                head = tail = newNode;
                return;
            }
            else {
                newNode->next = head;
                head = newNode; 
            }
            // Node newNode(val) // static
        }

        void print() {
            Node* temp = head;
            while(temp!=NULL) {
                cout << temp->data << " ";
                temp = temp->next;
            }
            cout << endl;
        }

        void push_back(int val) {
            Node* newNode = new Node(val);
            if (head==NULL) {
                head = tail = newNode;
                return;
            }
            else { 
                tail->next = newNode; 
                tail=newNode; 
            }
            // Node newNode(val) // static
        }

        void pop_front() {
            if (head==NULL) cout << "LL is empty\n";
            else {
                Node* temp = head;
                head = head->next;
                temp->next=NULL;
                delete temp;
            }
        }

};

int main () {
    List ll;

    ll.push_front(1);
    ll.push_front(4);
    ll.push_front(6);

    ll.push_back(8);

    ll.pop_front();

    ll.print();
}
#include<iostream>
using namespace std;

class Node {
    public:
        int code;
        string name;
        int duration;
        Node* prev;
        Node* next;

        Node(int c, string n, int d) {
            code=c;
            name=n;
            duration=d;
            prev=NULL;
            next=NULL;
        }
};

class LinkedList {
    public:
        Node* head;
        Node* tail;

        LinkedList() {
            head=NULL;
            tail=NULL;
        }

        void showOutbound(Node* head) {
            Node* temp=head;

            do {
                cout << temp->code << ":  " << temp->name << " (" << temp->duration << ")" << "\n";
                temp=temp->next; 
            } while(temp!=head);
        }

        void insert(Node* temp) {
            if (head==NULL) {
                head=temp;
                tail=temp;
                tail->next=head;
            }
            else {
                temp->prev=tail;
                temp->next=head;
                tail->next=temp;
                tail=temp;
            }
        }



};
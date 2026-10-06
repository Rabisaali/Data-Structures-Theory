#include<iostream>
using namespace std;

class Request {
    public:
        string rollNO;
        string courseCode;
        char action;
};

class Queue {
    public:
        Request arr[50];
        int MAX=50;
        int front;
        int rear;

        Queue() {
            front=-1;
            rear=-1;
        }

        bool isFull() {
            if ((rear+1)%MAX==front) return true;
            else return false;
        }

        bool isEmpty() {
            if (front==-1 && rear==-1) return true;
            else return false;
        }

        void enqueue(Request r) {
            if (isFull()) return;
            else if (isEmpty()) {
                front=0;
                rear=0;
                arr[0] = r;
            }
            else {
                rear=(rear+1)%MAX;
                arr[rear] = r;
            }
        }

        Request dequeue() {
            if (isEmpty()) return Request();
            else if (front==rear) {
                Request t=arr[front];
                front=-1;
                rear=-1;
                return t;
            }
            else {
                Request t=arr[front];
                front=(front+1)%MAX;
                return t;
            }
        }

        void Front() {
            if (isEmpty()) return;
            cout << "Roll number: " << arr[front].rollNO << " | Course Code: " << arr[front].courseCode << " | action: " << arr[front].action << endl; 
        }
};
class Node {
    public:
        Request r;
        Node* next;

        Node(Request t) {
            r=t;
            next=NULL;
        }
};

class Stack {
    public:
        Node* top;

        Stack() {
            top=NULL;
        }

        bool isEmpty() {
            if (top==NULL) return true;
            else return false;
        }

        void push(Request r) {
            Node* temp = new Node(r);

            temp->next=top;
            top=temp;
        }

        Request pop() {
            if (isEmpty()) return Request();
            else {
                Node* temp = top;
                Request r = temp->r;
                top = top->next;
                delete temp;
                return r;
            }
        }

        Request peek() {
            if (isEmpty()) return Request();
            else {
                Node* temp = top;
                Request r = temp->r;
                return r;
            }
        }
};

void process(Queue& q, Stack& h, int& seatsLeft) {
    do {
        if (q.isEmpty()) return;
        Request t = q.dequeue();
        if (t.action=='A') {
            if (seatsLeft>0) {
                seatsLeft--;
                h.push(t);
            }
        }
        else if (t.action=='D') {
            seatsLeft++;
            h.push(t);
        }
    } while (!q.isEmpty());
}

void undoLast(Stack& h, int& seatsLeft, int k) {
    while(k>0 && !h.isEmpty()) {
        Request temp=h.pop();
        if (temp.action == 'A') seatsLeft++;
        else if (temp.action == 'D') seatsLeft--;
        k--;
    }
} 

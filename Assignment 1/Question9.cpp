#include<iostream>
using namespace std;

const int MAX = 100;

class Queue {
public:
    int arr[MAX];
    int front;
    int rear;
    int count;

    Queue() {
        front = 0;
        rear = -1;
        count = 0;
    }

    bool isEmpty() {
        return count == 0;
    }

    bool isFull() {
        return count == MAX;
    }

    void enqueue(int patientID) {
        if(isFull()) {
            cout << "Queue is full.\n";
            return;
        }
        rear = (rear + 1) % MAX;
        arr[rear] = patientID;
        count++;
    }

    int dequeue() {
        if(isEmpty()) return -1;
        int patientID = arr[front];
        front = (front + 1) % MAX;
        count--;
        return patientID;
    }

    int size() {
        return count;
    }
};

int main() {

    Queue criticalQueue;
    Queue seriousQueue;
    Queue normalQueue;

    int n;
    cout << "Enter number of operations: ";
    cin >> n;

    int treatmentOrder[MAX];
    int treatedCount = 0;

    for(int i = 0; i < n; i++) {
        string operation;
        cin >> operation;

        if(operation == "ARRIVE") {
            int id;
            int severity;
            cin >> id >> severity;

            if(severity == 1) {
                criticalQueue.enqueue(id);
            }
            else if(severity == 2) {
                seriousQueue.enqueue(id);
            }
            else if(severity == 3) {
                normalQueue.enqueue(id);
            }
            else {
                cout << "Invalid severity.\n";
            }
        }

        else if(operation == "TREAT") {
            int patientID = -1;
            if(!criticalQueue.isEmpty()) {
                patientID = criticalQueue.dequeue();
            }
            else if(!seriousQueue.isEmpty()) {
                patientID = seriousQueue.dequeue();
            }
            else if(!normalQueue.isEmpty()) {
                patientID = normalQueue.dequeue();
            }

            if(patientID != -1) {
                treatmentOrder[treatedCount] = patientID;
                treatedCount++;
            }
        }
        else {
            cout << "Invalid operation.\n";
        }
    }
    cout << "\n========== RESULT ==========\n";
    cout << "Treatment Order: ";
    if(treatedCount == 0) {
        cout << "None";
    }
    else {
        for(int i = 0; i < treatedCount; i++) {
            cout << treatmentOrder[i];
            if(i < treatedCount - 1) cout << " ";
        }
    }
    cout << endl;

    int remaining = criticalQueue.size() + seriousQueue.size() + normalQueue.size();
    cout << "Total Patients Treated: " << treatedCount << endl;
    cout << "Total Patients Remaining: " << remaining << endl;
    cout << "Critical Patients Remaining: " << criticalQueue.size() << endl;
    cout << "Serious Patients Remaining: " << seriousQueue.size() << endl;
    cout << "Normal Patients Remaining: " << normalQueue.size() << endl;
    return 0;
}
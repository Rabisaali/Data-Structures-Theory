#include<iostream>
#include<string>
using namespace std;

class Job {
    public:
        string name;
        int priority;
        int arrival;
};

class PriorityQueue {
    public:
        Job* arr;
        int size;
        int capacity;
        int arrivalCount;

        PriorityQueue(int cap) {
            capacity = cap;
            size = 0;
            arrivalCount = 0;
            arr = new Job[capacity];
        }

        bool isHigher(Job a, Job b) {
            if(a.priority == b.priority) {
                return a.arrival < b.arrival;
            }

            return a.priority < b.priority;
        }

        void push(string name, int priority) {
            if(size == capacity) {
                cout << "Queue is full!" << endl;
                return;
            }

            Job temp;
            temp.name = name;
            temp.priority = priority;
            temp.arrival = arrivalCount++;

            arr[size] = temp;

            int i = size;
            size++;

            // Heapify Up
            while(i > 0) {
                int parent = (i - 1) / 2;

                if(isHigher(arr[i], arr[parent])) {
                    Job t = arr[i];
                    arr[i] = arr[parent];
                    arr[parent] = t;

                    i = parent;
                }
                else {
                    break;
                }
            }
        }

        void pop() {
            if(size == 0) {
                cout << "Queue is empty!" << endl;
                return;
            }

            cout << arr[0].name << endl;

            arr[0] = arr[size - 1];
            size--;

            // Heapify Down
            int i = 0;

            while(true) {
                int left = 2 * i + 1;
                int right = 2 * i + 2;
                int smallest = i;

                if(left < size && isHigher(arr[left], arr[smallest])) {
                    smallest = left;
                }

                if(right < size && isHigher(arr[right], arr[smallest])) {
                    smallest = right;
                }

                if(smallest != i) {
                    Job t = arr[i];
                    arr[i] = arr[smallest];
                    arr[smallest] = t;

                    i = smallest;
                }
                else {
                    break;
                }
            }
        }

        void peek() {
            if(size == 0) {
                cout << "Queue is empty!" << endl;
                return;
            }

            cout << arr[0].name << endl;
        }

        ~PriorityQueue() {
            delete[] arr;
        }
};

int main() {
    PriorityQueue pq(10);

    pq.push("J1", 3);
    pq.push("J2", 1);
    pq.push("J3", 2);

    cout << "POP: ";
    pq.pop();

    pq.push("J4", 1);
    pq.push("J5", 3);

    cout << "POP: ";
    pq.pop();

    cout << "POP: ";
    pq.pop();

    pq.push("J6", 2);

    for(int i = 0; i < 3; i++) {
        cout << "POP: ";
        pq.pop();
    }

    return 0;
}
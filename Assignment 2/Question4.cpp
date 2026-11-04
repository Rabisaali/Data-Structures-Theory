#include<iostream>
using namespace std;

class MinHeap {
    private:
        int* arr;
        int size;
        int capacity;

        void printArray() {
            cout << "[ ";
            for(int i=0; i<size; i++) {
                cout << arr[i] << " ";
            }
            cout << "]\n";
        }

        void swapNodes(int i, int j) {
            int temp=arr[i];
            arr[i]=arr[j];
            arr[j]=temp;

            cout << "After swap: ";
            printArray();
        }

        void siftUp(int i) {
            while(i>0) {
                int parent=(i-1)/2;

                if(arr[i]<arr[parent]) {
                    swapNodes(i, parent);
                    i=parent;
                }
                else break;
            }
        }

        void siftDown(int i) {
            while(true) {
                int smallest=i;
                int left=2*i+1;
                int right=2*i+2;

                if(left<size && arr[left]<arr[smallest]) {
                    smallest=left;
                }

                if(right<size && arr[right]<arr[smallest]) {
                    smallest=right;
                }

                if(smallest!=i) {
                    swapNodes(i, smallest);
                    i=smallest;
                }
                else break;
            }
        }

    public:

        MinHeap(int values[], int n, int cap) {
            capacity=cap;
            size=n;

            arr=new int[capacity];

            for(int i=0; i<n; i++) {
                arr[i]=values[i];
            }
        }

        ~MinHeap() {
            delete[] arr;
        }

        void insert(int key) {
            if(size==capacity) {
                cout << "Heap is full\n";
                return;
            }

            arr[size]=key;
            size++;

            cout << "After insertion of " << key << ": ";
            printArray();

            siftUp(size-1);
        }

        bool search(int key) {
            for(int i=0; i<size; i++) {
                if(arr[i]==key) return true;
            }
            return false;
        }

        int extractMin() {
            if(size==0) {
                cout << "Heap is empty\n";
                return -1;
            }

            int minValue=arr[0];

            arr[0]=arr[size-1];
            size--;

            cout << "After moving last element to root: ";
            printArray();

            if(size>0) {
                siftDown(0);
            }

            return minValue;
        }

        void decreaseKey(int index, int newValue) {
            if(index<0 || index>=size) {
                cout << "Invalid index\n";
                return;
            }

            if(newValue>arr[index]) {
                cout << "New value is greater than current value\n";
                return;
            }

            arr[index]=newValue;

            cout << "After decreasing key: ";
            printArray();

            siftUp(index);
        }

        void display() {
            printArray();
        }
};

int main() {

    int H[]={5, 11, 8, 14, 17, 9, 12, 20, 16, 19};

    MinHeap heap(H, 10, 20);

    cout << "--- Initial Heap ---\n";
    heap.display();

    cout << "\n--- Part B: Insertions ---\n";

    heap.insert(6);
    heap.insert(4);

    cout << "\nHeap after insertions: ";
    heap.display();

    cout << "\n--- Part C: Extract Min ---\n";

    cout << "Extracted: " << heap.extractMin() << endl;
    cout << "Heap: ";
    heap.display();

    cout << "\nSecond Extract Min:\n";
    cout << "Extracted: " << heap.extractMin() << endl;
    cout << "Heap: ";
    heap.display();

    cout << "\n--- Part D: Decrease Key ---\n";

    heap.decreaseKey(7, 3);

    cout << "Final Heap: ";
    heap.display();

    return 0;
}

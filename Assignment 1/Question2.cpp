#include<iostream>
using namespace std;

void insertionSort(int arr[], int n) {
    for(int i=1; i<n; i++) {
        int key=arr[i];
        int j=i-1;

        while(j>=0 && arr[j]>key) {
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=key;
    }
}

void printingArray(int arr[], int n) {
    for(int i=0; i<n; i++) cout << arr[i] << " ";
    cout << endl;
}
int main () {
    int n;
    cout << "Enter number of shelves: ";
    cin >> n;
    int* arr = new int[n];
    cout << "Enter book capacity of each shelf:" << endl;
    for(int i=0; i<n; i++) cin >> arr[i];

    cout << "Original shelf capacities: ";
    printingArray(arr, n);

    int pos;

    cout << "Enter position to add the new shelf (0 to " << n << "): ";
    cin >> pos;

    int* arr2 = new int[n+1];

    for(int i=0; i<pos; i++) arr2[i]=arr[i];
    cout << "Enter capacity of the new shelf: ";
    cin >> arr2[pos];
    for(int i=pos+1; i<n+1; i++) arr2[i]=arr[i-1];

    delete[] arr;

    cout << "Shelves after adding new shelf: ";
    printingArray(arr2, n+1);

    cout << "Shelves after sorting: ";
    insertionSort(arr2, n+1);

    printingArray(arr2, n+1);

    delete[] arr2;
}
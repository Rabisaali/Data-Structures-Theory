#include<iostream>
using namespace std;

void printingArray(int arr[], int n);

void insertionSort(int arr[], int n) {
    for(int i=1; i<n; i++) {
        int key = arr[i];
        int j=i-1;
        while(j>=0 && arr[j]>key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1]=key;
        cout << "Iteration " << i << ": ";
        printingArray(arr, n);
    }
}

void printingArray(int arr[], int n) {
    for(int i=0; i<n; i++) {
        cout << arr[i] << " ";
    }
    cout << '\n';
}

int main () {
    int arr1[] = {85, 42, 120, 35, 67, 50};
    cout << "Passing the array provided in the question:\n";
    cout << "Original Array: ";
    printingArray(arr1, size(arr1));
    insertionSort(arr1, size(arr1));
    cout << "Final Sorted Array: ";
    printingArray(arr1, size(arr1));

    int n;
    cout << "Taking user input:\n";
    cout << "Enter the size of array: ";
    cin >> n;
    int arr2[n];
    cout << "Enter " << n << " elements: "; 
    for(int i=0; i<n; i++) cin >> arr2[i];
    cout << "Original Array: ";
    printingArray(arr2, n);
    insertionSort(arr2, n);
    cout << "Final Sorted Array: ";
    printingArray(arr2, n);
}
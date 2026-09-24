#include<iostream>
using namespace std;

void printingArray(int arr[], int n) {
    for(int i=0; i<n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void combSort(int arr[], int n) {
    int gap=n;
    bool swapped=true;
    int i=1;
    while(gap!=1 || !swapped) {
        if (gap>1) {
            gap/=1.3;

            if(gap<1) gap=1;
        }
        swapped=false;
        cout << "Gap value in iteration " << i << ": " << gap <<endl;
        for(int j=0; j<n-gap; j++) {
            if (arr[j]>arr[j+gap]) {
                int temp=arr[j];
                arr[j]=arr[j+gap];
                arr[j+gap]=temp;
                swapped=true;
            }
        }
        cout << "Array after " << i++ << " iteration: ";
        printingArray(arr, n);
    }
}

int main() {
    int array1[] = {120, 35, 90, 15, 75, 10, 60, 25};

    cout << "The given array in question: ";
    printingArray(array1, size(array1));
    combSort(array1, size(array1));

    cout << "Sorted array: ";
    printingArray(array1, size(array1));
    cout << endl;

    cout << "Taking user input: " << endl << endl;
    int n;
    cout << "Enter number of values: ";
    cin >> n;

    int* array2 = new int[n];

    cout << "Enter " << n << " values: ";
    for(int i=0; i<n; i++) cin >> array2[i];

    cout << "Original user inputted array: ";
    printingArray(array2, n);
    combSort(array2, n);

    cout << "Sorted array: ";
    printingArray(array2, n);

    delete[] array2;
}
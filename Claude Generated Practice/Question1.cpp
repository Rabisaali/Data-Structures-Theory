#include<iostream>
using namespace std;
void printingArray(int arr[], int n);
void insertionSort(int arr[], int n) {
    int count=0;
    for(int i=1; i<n; i++) {
        int j=i-1;
        int key=arr[i];
        while(j>=0 && arr[j]>key) {
            arr[j+1]=arr[j];
            j--;
            count++;
        }
        arr[j+1]=key;

        cout << "After pass: " << i << " ";
        printingArray(arr, n);
    }
    cout << "Number of counts: " << count << "\n";
}

void selectionSort(int arr[], int n) {
    int count=0;
    for (int i=0; i<n-1; i++) {
        int min_ind=i;
        for (int j=i+1; j<n; j++) {
            if (arr[j]<arr[min_ind]) {
                min_ind=j;
            }
        }
        swap(arr[i], arr[min_ind]);
        count++;
        cout << "After pass: " << i+1 << " ";
        printingArray(arr, n);
    }
    cout << "Number of counts: " << count << "\n";
}

void shellShort(int arr[], int n) {
    for(int gap=n/2; gap>0; gap/=2) {
        for(int j=gap; j<n; j++) {
            int temp=arr[j];
            int res=j;
            while(res>=gap && arr[res-gap]>temp) {
                arr[res]=arr[res-gap];
                res-=gap;
            }
            arr[res]=temp;
        }
        
    }
}

int binarySearch(int arr[], int n, int key) {
    int low=0, high=n-1;
    while(low<=high) {
        if (arr[high]==arr[low]) {
            if (arr[high]==key) return high;
            else return -1;
        }
        int mid = low + (high-low)/2;

        if (arr[mid]==key) return mid;
        else if (arr[mid]<key) low = mid+1;
        else high=mid-1; 
    }
    return -1;
}

int interpolationSearch(int arr[], int n, int key) {
    int high=n-1, low=0;
    while(high>=low && arr[high]>=key && arr[low]<=key) {
        if (arr[high]==arr[low]) {
            if (arr[high]==key) return high;
            else return -1;
        }

        int pos = low + (key-arr[low])*(high-low)/(arr[high]-arr[low]);

        if (arr[pos]==key) return pos;
        else if (arr[pos]>key) high = pos-1;
        else low = pos+1;
    }
    return -1;
}

void printingArray(int arr[], int n) {
    for (int i=0; i<n; i++) cout << arr[i] << " ";
    cout << endl;
}


int main () {
    int arr[] = {67, 45, 89, 23, 78, 56, 91, 34, 62, 80};
    insertionSort(arr, 10);
    selectionSort(arr, 10);
    shellShort(arr, 10);

    cout << binarySearch(arr, 10, 78) << "\n";
    cout << interpolationSearch(arr, 10, 78);

}
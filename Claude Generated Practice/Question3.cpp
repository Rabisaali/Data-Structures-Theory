#include<iostream>
using namespace std;

class Student {
    public:
        int rollNo;
        string name;
        float cgpa;
};

void printingArray(Student arr[], int n) {
    for(int i=0; i<n; i++) {
        cout << arr[i].rollNo << ": " << arr[i].name << " | (" << arr[i].cgpa << ")\n";
    }
}

void insertionSort(Student arr[], int n) {
    int comp=0, shift=0;
    for (int i=1; i<n; i++) {
        Student s=arr[i];
        int key=arr[i].rollNo;
        int j=i-1;
        while(j>=0 && arr[j].rollNo>key) {
            arr[j+1]=arr[j];
            j--;
            shift++;
            comp++;
        }
        arr[j+1]=s;
        comp++;
    }
    cout << "Comparisions: " << comp << " | Shifts: " << shift << "\n"; 
}

void shellShort(Student arr[], int n) {
    for(int gap=n/2; gap>0; gap/=2) {
        for(int j=gap; j<n; j++) {
            Student s=arr[j];
            int temp=arr[j].rollNo;
            int res=j;

            while(res>=gap && arr[res-gap].rollNo>arr[res].rollNo) {
                arr[res]=arr[res-gap];
                res-=gap;
            }
            arr[res]=s;
        }
        printingArray(arr, n);
    }
}

void selectionSort(Student arr[], int n, int k) {
    for(int i=0; i<n-1 && k>0; i++) {
        int max_ind=i;
        for(int j=i+1; j<n; j++) {
            if (arr[j].cgpa>arr[max_ind].cgpa) max_ind=j;
        }
        swap(arr[i], arr[max_ind]);
        k--;
    }
}

int binarySearch(Student arr[], int n, int key) {
    int high=n-1, low=0;

    while(high>=low) {
        int mid = low+(high-low)/2;
        if (arr[mid].rollNo==key) return mid;
        else if (arr[mid].rollNo>arr[low].rollNo) low=mid+1;
        else high=mid-1; 
    }
    return -1;
}

int interpolationSearch(Student arr[], int n, int key) {
    int high=n-1, low=0;

    while(high>=low && key>=arr[low].rollNo && key<=arr[high].rollNo) {
        if (arr[low].rollNo == arr[high].rollNo)
            return (arr[low].rollNo == key) ? low : -1;

        int mid = low+(key-arr[low].rollNo)*(high-low)/(arr[high].rollNo-arr[low].rollNo);
        
        if (arr[mid].rollNo==key) return mid;
        else if (arr[mid].rollNo>arr[low].rollNo) low=mid+1;
        else high=mid-1; 
    }
    return -1;
}
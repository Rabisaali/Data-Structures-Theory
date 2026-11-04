#include<iostream>
#include<iomanip>
using namespace std;

class Student {
    public:
        string ID, name, department;
        float CGPA;
        string award;

        Student() {}

        Student(string i, string n, string d, float c) {
            ID=i;
            name=n;
            department=d;
            CGPA=c;
            award="No Award";
        }
};

void merge(Student arr[], int left, int mid, int right) {

    int n1=mid-left+1;
    int n2=right-mid;

    Student* L=new Student[n1];
    Student* R=new Student[n2];

    for(int i=0; i<n1; i++) {
        L[i]=arr[left+i];
    }

    for(int j=0; j<n2; j++) {
        R[j]=arr[mid+1+j];
    }

    int i=0, j=0;
    int k=left;

    while(i<n1 && j<n2) {

        // Descending order
        if(L[i].CGPA>=R[j].CGPA) {
            arr[k]=L[i];
            i++;
        }
        else {
            arr[k]=R[j];
            j++;
        }
        k++;
    }

    while(i<n1) {
        arr[k]=L[i];
        i++;
        k++;
    }

    while(j<n2) {
        arr[k]=R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(Student arr[], int left, int right) {

    if(left>=right) return;

    int mid=left+(right-left)/2;

    mergeSort(arr, left, mid);
    mergeSort(arr, mid+1, right);

    merge(arr, left, mid, right);
}

void assignAwards(Student arr[], int n) {

    for(int i=0; i<n; i++) {

        if(arr[i].CGPA==4.00) {
            arr[i].award="Rector's List";
        }
        else if(arr[i].CGPA>=3.50) {
            arr[i].award="Dean's List";
        }
        else {
            arr[i].award="No Award";
        }
    }
}

void display(Student arr[], int n) {

    cout << "\n---------------- FINAL MERIT LIST ----------------\n\n";
    cout << left << setw(8) << "Rank" << setw(12) << "ID" << setw(18) << "Name" << setw(15) << "Department" << setw(10) << "CGPA" << "Award\n";
    cout << "---------------------------------------------------------------\n";

    for(int i=0; i<n; i++) {

        cout << left << setw(8) << i+1 << setw(12) << arr[i].ID << setw(18) << arr[i].name << setw(15) << arr[i].department << setw(10) << fixed << setprecision(2) << arr[i].CGPA << arr[i].award << endl;
    }
    cout << "---------------------------------------------------------------\n";
}

int main() {

    Student students[] = {

        Student("BCS001", "Ali", "CS", 3.95),
        Student("BCS002", "Ahmed", "CS", 3.45),
        Student("BCS003", "Sara", "SE", 3.80),
        Student("BCS004", "Ayesha", "AI", 3.90),
        Student("BCS005", "Hamza", "CS", 3.20),

        Student("BCS006", "Zara", "SE", 3.75),
        Student("BCS007", "Usman", "AI", 3.95),
        Student("BCS008", "Hira", "CS", 3.50),
        Student("BCS009", "Bilal", "SE", 2.90),
        Student("BCS010", "Noor", "AI", 3.85),

        Student("BCS011", "Daniyal", "CS", 3.60),
        Student("BCS012", "Maham", "SE", 3.90),
        Student("BCS013", "Saad", "AI", 3.30),
        Student("BCS014", "Fatima", "CS", 4.00),
        Student("BCS015", "Hassan", "SE", 3.70),

        Student("BCS016", "Maryam", "AI", 3.50),
        Student("BCS017", "Taha", "CS", 3.95),
        Student("BCS018", "Laiba", "SE", 3.10),
        Student("BCS019", "Zain", "AI", 3.80),
        Student("BCS020", "Areeba", "CS", 3.65),

        Student("BCS021", "Saima", "SE", 3.40),
        Student("BCS022", "Arham", "AI", 3.90),
        Student("BCS023", "Muneeb", "CS", 3.55),
        Student("BCS024", "Eman", "SE", 3.95),
        Student("BCS025", "Rayan", "AI", 2.75),

        Student("BCS026", "Anaya", "CS", 3.70),
        Student("BCS027", "Fahad", "SE", 3.30),
        Student("BCS028", "Iqra", "AI", 3.85),
        Student("BCS029", "Sameer", "CS", 3.50),
        Student("BCS030", "Dua", "SE", 3.95)

    };

    int n=sizeof(students)/sizeof(students[0]);

    cout << "Total Students: " << n << endl;

    cout << "\nSorting students according to CGPA...\n";

    mergeSort(students, 0, n-1);

    assignAwards(students, n);

    display(students, n);

    return 0;
}

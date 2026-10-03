#include<iostream>
using namespace std;
int getNum(string m) {
    if (m=="January")return 12;
    else if (m=="February") return 11;
    else if (m=="March") return 10;
    else if (m=="April") return 9;
    else if (m=="May") return 8;
    else if (m=="June") return 7;
    else if (m=="July") return 6;
    else if (m=="August") return 5;
    else if (m=="September") return 4;
    else if (m=="October") return 3;
    else if (m=="November") return 2;
    else return 1;
}

class Customer {
    public:
        string name;
        int number;
        int date;
        string month;
        Customer(string n, int d, string m) {
            name=n;
            date=d;
            month=m;
        }
};

void sort(Customer arr[]) {
    int n=5;
    for(int i=0; i<n-1; i++) {
        int min_ind=i;

        for(int j=i+1; j<n; j++) {
            if ((getNum(arr[min_ind].month)>getNum(arr[j].month)) || (getNum(arr[min_ind].month)==getNum(arr[j].month) && arr[min_ind].date>arr[j].date) || (getNum(arr[min_ind].month)==getNum(arr[j].month) && arr[min_ind].date==arr[j].date && arr[min_ind].name.length()>arr[j].name.length())) {
                min_ind=j;
            }
        }

        swap(arr[i], arr[min_ind]);
    }
}

void assignHangers(Customer c[]) {
    int hanger=1;
    for(int i=0; i<5; i++) c[i].number=hanger++;
}

void display(Customer c[]) {
    for(int i=0; i<5; i++) {
        cout << c[i].name << " " << "Hanger " << c[i].number << "\t";
    }
}

int binarySearch(Customer c[], string n) {
    int left=0, right=5-1;

    while(left<=right) {
        int mid = left + (right-left)/2;

        if (c[mid].name==n) return c[mid].number;
        else if (c[mid].name<n) left=mid+1;
        else right=mid-1; 
    }
    return -1;
}

void sortByName(Customer arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;

        for (int j = i + 1; j < n; j++)
        {
            if (arr[j].name < arr[minIndex].name)
            {
                minIndex = j;
            }
        }

        Customer temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

int main () {
    Customer c[] = {Customer("Mubeen", 9, "September"), Customer("Ali", 1, "September"), Customer("Shaheer", 15, "September"), Customer("Sadiq", 8, "September"), Customer("Romaan", 20, "September")};
    sort(c);
    assignHangers(c);
    display(c);

    sortByName(c, 5);
    cout << binarySearch(c, "Romaan") << "\n";

}
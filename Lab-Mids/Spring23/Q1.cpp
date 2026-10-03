#include<iostream>
using namespace std;

class Title {
    public:
        string* arr;
        int N;

        Title(int n) {
            N=n;
            arr = new string[N];
        }

        void input() {
            for(int i=0; i<N; i++) {
                cin >> arr[i];
            }
        }

        Title(const Title& other) {
            N=other.N;
            for(int i=0; i<N; i++) arr[i]=other.arr[i];
        }

        Title& operator= (const Title& other) {
            if (&other==this) return *this;
            
            delete[] arr;

            N=other.N;
            arr = new string[N];
            for(int i=0; i<N; i++) {
                arr[i]=other.arr[i];
            }
        }

        ~Title() {
            delete[] arr;
        }

        void sort() {
            for(int gap=N; gap>0; gap/=2) {
                for (int j=gap; j<N; j++) {
                    int res=j;
                    string temp=arr[j];

                    while(res>=gap && arr[res-gap]>temp) {
                        arr[res]=arr[res-gap];
                        res-=gap;
                    }
                    arr[res]=temp;
                }
            }
        }

        void display() {
            cout << "Printing array: ";
            for (int i=0; i<N; i++) {
                cout << arr[i] << " ";
            }
        }
};

int main () {
    Title t(3);
    t.input();

    t.sort();
    t.display();
}
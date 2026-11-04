#include <iostream>
using namespace std;

int result[100];
int total = 0;
int N, S, M;

void display() {
    total++;
    for (int i = 0; i < N; i++) {
        cout << result[i] << " ";
    }
    cout << endl;
}

void generate(int allowed[], int index, int start, int sum) {

    if (index == N) {
        if (sum == S) {
            display();
        }
        return;
    }

    for (int i = start; i < M; i++) {
        result[index] = allowed[i];
        generate(allowed, index + 1, i + 1, sum + allowed[i]);
        result[index] = 0;
    }
}

int main() {
    cout << "Enter the number of allowed digits: ";
    cin >> M;

    int* allowed = new int[M];

    cout << "Enter the allowed digits: ";
    for (int i = 0; i < M; i++) {
        cin >> allowed[i];
    }

    cout << "Enter the number of digits in the access code: ";
    cin >> N;

    cout << "Enter the target sum: ";
    cin >> S;
    if (N <= 0 || N > M || N > 100) {
        cout << "Invalid value of N." << endl;
        delete[] allowed;
        return 0;
    }
    for (int i = 0; i < M - 1; i++) {
        for (int j = 0; j < M - i - 1; j++) {
            if (allowed[j] > allowed[j + 1]) {
                int temp = allowed[j];
                allowed[j] = allowed[j + 1];
                allowed[j + 1] = temp;
            }
        }
    }

    generate(allowed, 0, 0, 0);
    if (total == 0) {
        cout << "No valid combinations found." << endl;
    }
    else {
        cout << "Total valid combinations: " << total << endl;
    }
    delete[] allowed;
    return 0;
}

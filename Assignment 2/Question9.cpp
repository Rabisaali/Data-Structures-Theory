#include <iostream>
#include <string>
using namespace std;

string courses[4] = {
    "Programming",
    "Database Systems",
    "Operating Systems",
    "Computer Networks"
};

int seatRow[4], seatCol[4];

bool rowUsed[7] = {false};
bool colUsed[9] = {false};

int total = 0;

bool isSafe(int r, int c, int course) {

    if (r == 3 && c == 3)
        return false;

    if (rowUsed[r] || colUsed[c])
        return false;

    for (int i = 0; i < course; i++) {
        if (abs(seatRow[i] - r) == abs(seatCol[i] - c)) return false;
    }

    return true;
}

void display() {
    total++;
    cout << "\nArrangement " << total << ":\n";
    for (int i = 0; i < 4; i++) {
        cout << courses[i] << " -> (" << seatRow[i] << ", " << seatCol[i] << ")\n";
    }
}

void assignSeats(int course) {
    if (course == 4) {
        display();
        return;
    }

    int startRow, endRow;

    if (course == 0) {
        startRow = 1;
        endRow = 1;
    }
    else {
        startRow = 1;
        endRow = 6;
    }

    for (int r = startRow; r <= endRow; r++) {
        for (int c = 1; c <= 8; c++) {
            if (isSafe(r, c, course)) {
                seatRow[course] = r;
                seatCol[course] = c;
                rowUsed[r] = true;
                colUsed[c] = true;
                assignSeats(course + 1);
                rowUsed[r] = false;
                colUsed[c] = false;
            }
        }
    }
}

int main() {

    assignSeats(0);
    cout << "\nTotal valid arrangements: " << total << endl;
    return 0;
}

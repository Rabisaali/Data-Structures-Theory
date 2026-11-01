#include<iostream>
using namespace std;

void fun(char** board, int r, int c, int n, string paths, int& count, bool** visited) {

    if (r<0 || c<0 || r>=n || c>=n || board[r][c]=='X' || visited[r][c]) return;

    visited[r][c]=true;

    if (r==n-1 && c==n-1) {
        count++;
        cout << "Path " << count << ": " << paths << "\n";
        visited[r][c]=false;
        return; 
    }
    
    fun(board, r+1, c, n, paths+'D', count, visited);
    fun(board, r-1, c, n, paths+'U', count, visited);
    fun(board, r, c+1, n, paths+'R', count, visited);
    fun(board, r, c-1, n, paths+'L', count, visited);

    visited[r][c] = false;
}

int main () {
    int n;
    cout << "Enter the value of N: ";
    cin >> n;

    char** board = new char* [n];
    for(int i=0; i<n; i++) board[i] = new char [n];

    cout << "Enter the contents of " << n << "x" << n << " grid: (0 represents open way and X represents blocked way): \n";

    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) cin >> board[i][j];
    }

    bool** visited = new bool* [n];
    for(int i=0; i<n; i++) visited[i] = new bool[n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            visited[i][j] = false;
        }
    }

    int count=0;
    fun(board, 0, 0, n, "", count, visited);
    if (count==0) {
        cout << "No valid path exists\n";
    }
    
    for(int i=0; i<n; i++) {
        delete[] board[i];
        delete[] visited[i];
    }

    delete[] board;
    delete[] visited;
}
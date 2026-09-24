#include <iostream>
using namespace std;

const int MAX_PLAYERS = 100;
const int MAX_ACTIONS = 1000;

class Player {
public:
    int id;
    int energy;

    Player() {
        id = 0;
        energy = 100;
    }

    Player(int i) {
        id = i;
        energy = 100;
    }
};

class ActionStack {
public:
    char actions[MAX_ACTIONS];
    int top;

    ActionStack() {
        top = -1;
    }

    bool isEmpty() {
        return top == -1;
    }

    void push(char action) {
        if (top < MAX_ACTIONS - 1) {
            top++;
            actions[top] = action;
        }
    }

    char pop() {
        if (isEmpty()) {
            return '\0';
        }
        char action = actions[top];
        top--;
        return action;
    }

    int size() {
        return top + 1;
    }
};

class WaitingQueue {
public:
    Player players[MAX_PLAYERS];

    int front;
    int rear;
    int count;

    WaitingQueue() {
        front = 0;
        rear = -1;
        count = 0;
    }

    bool isEmpty() {
        return count == 0;
    }

    void enqueue(Player p) {
        if (count == MAX_PLAYERS) {
            return;
        }
        rear = (rear + 1) % MAX_PLAYERS;
        players[rear] = p;
        count++;
    }

    Player dequeue() {
        Player p;
        if (isEmpty()) {
            return p;
        }

        p = players[front];
        front = (front + 1) % MAX_PLAYERS;
        count--;
        return p;
    }

    int size() {
        return count;
    }
};

int main() {

    WaitingQueue waitingQueue;
    ActionStack history[MAX_PLAYERS];
    Player allPlayers[MAX_PLAYERS];

    int n;
    cout << "Enter number of players: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        int id;
        cin >> id;

        allPlayers[id] = Player(id);
        waitingQueue.enqueue(allPlayers[id]);
    }

    int commands;
    cout << "Enter number of commands: ";
    cin >> commands;

    int eliminated[MAX_PLAYERS];
    int eliminatedCount = 0;

    for (int i = 0; i < commands; i++) {

        char command;
        cin >> command;

        if (waitingQueue.isEmpty()) {
            continue;
        }
        Player current = waitingQueue.dequeue();

        int id = current.id;

        if (command == 'F') {
            current.energy -= 10;
            history[id].push('F');
        }
        else if (command == 'B') {
            history[id].push('B');
        }
        else if (command == 'T') {
            current.energy += 20;
            history[id].push('T');
        }
        else if (command == 'U') {

            if (!history[id].isEmpty()) {
                char previousAction = history[id].pop();
                if (previousAction == 'F') {
                    current.energy += 10;
                }
                else if (previousAction == 'B') {
                    // B had no energy effect.
                }
                else if (previousAction == 'T') {
                    current.energy -= 20;
                }
            }
        }

        allPlayers[id] = current;

        if (current.energy <= 0) {
            eliminated[eliminatedCount] = id;
            eliminatedCount++;
        }
        else {
            waitingQueue.enqueue(current);
        }
    }

    cout << "\nElimination Order: ";
    if (eliminatedCount == 0) {
        cout << "None";
    }
    else {
        for (int i = 0; i < eliminatedCount; i++) {
            cout << eliminated[i];
            if (i < eliminatedCount - 1) {
                cout << " ";
            }
        }
    }
    cout << endl;
    cout << "\nRemaining Players:\n";

    if (waitingQueue.isEmpty()) {
        cout << "None" << endl;
    }
    else {
        int numberOfPlayers = waitingQueue.size();

        for (int i = 0; i < numberOfPlayers; i++) {
            Player current = waitingQueue.dequeue();
            cout << "Player ID: " << current.id << ", Energy: " << current.energy << ", Undoable Actions: " << history[current.id].size() << endl;
            waitingQueue.enqueue(current);
        }
    }
    return 0;
}
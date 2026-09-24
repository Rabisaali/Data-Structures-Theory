#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Combatant {
public:
    string name;
    int health;
    int attackPower;

    Combatant(string n, int h, int a) {
        name = n;
        health = h;
        attackPower = a;
    }
};

class Node {
public:
    Combatant combatant;
    Node* prev;
    Node* next;

    Node(Combatant c) : combatant(c) {
        prev = NULL;
        next = NULL;
    }
};


class DoublyLinkedList {
public:
    Node* head;
    Node* tail;

    DoublyLinkedList() {
        head = NULL;
        tail = NULL;
    }

    void insertAtEnd(Combatant c) {
        Node* newNode = new Node(c);

        if(head == NULL) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    Node* search(string name) {
        Node* temp = head;

        while(temp != NULL) {
            if(temp->combatant.name == name) return temp;
            temp = temp->next;
        }

        return NULL;
    }

    Node* getAtPosition(int position) {
        if(position < 0) return NULL;

        Node* temp = head;
        int count = 0;

        while(temp != NULL) {
            if(count == position) return temp;
            count++;
            temp = temp->next;
        }

        return NULL;
    }

    void deleteNode(Node* temp) {
        if(temp == NULL) return;

        if(head == temp && tail == temp) {
            head = NULL;
            tail = NULL;
        }

        else if(temp == head) {
            head = head->next;
            head->prev = NULL;
        }

        else if(temp == tail) {
            tail = tail->prev;
            tail->next = NULL;
        }

        else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }
        delete temp;
    }

    bool isEmpty() {
        return head == NULL;
    }

    void displayNames() {
        Node* temp = head;

        if(temp == NULL) {
            cout << "None";
            return;
        }
        while(temp != NULL) {
            cout << temp->combatant.name;
            if(temp->next != NULL) cout << " -> ";
            temp = temp->next;
        }
    }

    int totalHealth() {
        int total = 0;
        Node* temp = head;
        while(temp != NULL) {
            total += temp->combatant.health;
            temp = temp->next;
        }
        return total;
    }

    void displayDetails() {
        Node* temp = head;
        while(temp != NULL) {
            cout << "Name: " << temp->combatant.name << endl;
            cout << "Health: " << temp->combatant.health << endl;
            cout << "Attack Power: " << temp->combatant.attackPower << endl;
            cout << endl;
            temp = temp->next;
        }
    }
};

Node* chooseCombatant(DoublyLinkedList& team, string type) {
    int choice;

    cout << "\nChoose " << type << " by:\n";
    cout << "1. Name\n";
    cout << "2. Position\n";
    cout << "Enter choice: ";
    cin >> choice;

    if(choice == 1) {
        string name;
        cout << "Enter name: ";
        cin >> name;
        return team.search(name);
    }

    if(choice == 2) {
        int position;
        cout << "Enter position: ";
        cin >> position;
        return team.getAtPosition(position);
    }
    return NULL;
}

void performAttack(Node* attacker, Node* target, DoublyLinkedList& targetTeam) {
    int randomValue = rand() % 3 + 1;
    int damage = attacker->combatant.attackPower * randomValue;
    cout << attacker->combatant.name << " attacks " << target->combatant.name << endl;
    target->combatant.health -= damage;
    cout << "Damage dealt: " << damage << endl;

    if(target->combatant.health <= 0) {
        cout << target->combatant.name << " has been defeated!\n";
        targetTeam.deleteNode(target);
    }
}


int main() {

    srand(time(0));


    DoublyLinkedList heroes;
    DoublyLinkedList enemies;

    heroes.insertAtEnd(Combatant("Michael", 70, 5));
    heroes.insertAtEnd(Combatant("Dean", 60, 4));
    heroes.insertAtEnd(Combatant("Sloane", 65, 5));
    heroes.insertAtEnd(Combatant("Lia", 55, 3));
    heroes.insertAtEnd(Combatant("Cassie", 50, 4));

    enemies.insertAtEnd(Combatant("Jameson", 60, 4));
    enemies.insertAtEnd(Combatant("Grayson", 40, 3));
    enemies.insertAtEnd(Combatant("Avery", 70, 5));
    enemies.insertAtEnd(Combatant("Nash", 55, 4));
    enemies.insertAtEnd(Combatant("Xander", 45, 3));

    int round = 1;
    const int maxRounds = 10;

    cout << endl;
    cout << "       TURN BASED BATTLE\n";
    cout << "====================================\n";

    while(round <= maxRounds && !heroes.isEmpty() && !enemies.isEmpty()) {
        cout << "\n========== ROUND " << round << " ==========\n";

        cout << "\n--- HERO TURN ---\n";

        cout << "Heroes: ";
        heroes.displayNames();
        cout << endl;

        cout << "Enemies: ";
        enemies.displayNames();
        cout << endl;

        Node* heroAttacker = NULL;
        Node* enemyTarget = NULL;

        while(heroAttacker == NULL) {
            heroAttacker = chooseCombatant(heroes, "hero attacker");
            if(heroAttacker == NULL) cout << "Invalid hero. Try again.\n";
        }

        while(enemyTarget == NULL) {
            enemyTarget = chooseCombatant(enemies, "enemy target");

            if(enemyTarget == NULL) cout << "Invalid enemy. Try again.\n";
        }

        performAttack(heroAttacker, enemyTarget, enemies);

        if(enemies.isEmpty()) {
            cout << "\nAll enemies have been defeated!\n";
            cout << "HEROES WIN!\n";
            break;
        }

        cout << "\nRemaining Heroes: ";
        heroes.displayNames();

        cout << "\nRemaining Enemies: ";
        enemies.displayNames();

        cout << endl;

        cout << "\n--- ENEMY COUNTERATTACK ---\n";

        Node* enemyAttacker = NULL;
        Node* heroTarget = NULL;
        while(enemyAttacker == NULL) {

            enemyAttacker = chooseCombatant(enemies, "enemy attacker");

            if(enemyAttacker == NULL) cout << "Invalid enemy. Try again.\n";
        }

        while(heroTarget == NULL) {
            heroTarget = chooseCombatant(heroes, "hero target");
            if(heroTarget == NULL) cout << "Invalid hero. Try again.\n";
        }

        performAttack(enemyAttacker, heroTarget, heroes);

        if(heroes.isEmpty()) {
            cout << "\nAll heroes have been defeated!\n";
            cout << "ENEMIES WIN!\n";
            break;
        }

        cout << "\nRemaining Heroes: ";
        heroes.displayNames();

        cout << "\nRemaining Enemies: ";
        enemies.displayNames();
        cout << endl;
        round++;
    }

    cout << "\n====================================\n";
    cout << "          FINAL RESULT\n";
    cout << "====================================\n";

    if(heroes.isEmpty()) {
        cout << "\nWinner: ENEMY TEAM\n\n";
        cout << "Surviving Enemies:\n";
        enemies.displayDetails();
    }

    else if(enemies.isEmpty()) {
        cout << "\nWinner: HERO TEAM\n\n";
        cout << "Surviving Heroes:\n";
        heroes.displayDetails();
    }

    else {

        int heroHealth = heroes.totalHealth();
        int enemyHealth = enemies.totalHealth();

        cout << "\n10 rounds completed.\n";

        cout << "Total Hero Health: " << heroHealth << endl;
        cout << "Total Enemy Health: " << enemyHealth << endl;

        if(heroHealth > enemyHealth) {
            cout << "\nWinner: HERO TEAM\n\n";

            cout << "Surviving Heroes:\n";
            heroes.displayDetails();
        }

        else if(enemyHealth > heroHealth) {
            cout << "\nWinner: ENEMY TEAM\n\n";
            cout << "Surviving Enemies:\n";
            enemies.displayDetails();
        }

        else {

            cout << "\nRESULT: DRAW\n\n";
            cout << "Remaining Heroes:\n";
            heroes.displayDetails();
            cout << "Remaining Enemies:\n";
            enemies.displayDetails();
        }
    }

    return 0;
}
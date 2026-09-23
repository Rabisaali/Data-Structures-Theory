#include<iostream>
using namespace std;

class Node {
    public:
        int productID;
        string productName;
        string category;
        int price;
        Node* next;

        Node(int id, string name, string cat, int p) {
            productID = id;
            productName = name;
            category = cat;
            price = p;
            next = NULL;
        }
};

class List {
    public:
        Node* head;
        Node* tail;

        List() {
            head = NULL;
            tail = NULL;
        }

        void arrangeAscending(Node* t) {

            if (head == NULL) {
                head = tail = t;
                t->next = NULL;
                return;
            }

            if (t->productID < head->productID) {
                t->next = head;
                head = t;
                return;
            }

            Node* temp = head;

            while (temp->next != NULL &&
                   temp->next->productID < t->productID) {
                temp = temp->next;
            }

            t->next = temp->next;
            temp->next = t;

            if (t->next == NULL) {
                tail = t;
            }
        }

        void add(int id, string name, string cat, int p) {

            Node* newNode = new Node(id, name, cat, p);

            arrangeAscending(newNode);
        }

        void display() {

            Node* temp = head;

            while (temp != NULL) {
                cout << "Product ID: " << temp->productID << " | Product Name: " << temp->productName << " | Category: " << temp->category << " | Price: " << temp->price << endl;
                temp = temp->next;
            }
        }
};

List merge(List& l1, List& l2) {

    List l3;

    Node* temp1 = l1.head;
    Node* temp2 = l2.head;

    Node* last = NULL;

    while (temp1 != NULL && temp2 != NULL) {
        Node* selected;

        if (temp1->productID < temp2->productID) {

            selected = temp1;
            temp1 = temp1->next;
        }

        else if (temp2->productID < temp1->productID) {

            selected = temp2;
            temp2 = temp2->next;
        }

        else {

            if (temp1->price <= temp2->price) {

                selected = temp1;

                temp1 = temp1->next;
                temp2 = temp2->next;
            }
            else {

                selected = temp2;

                temp1 = temp1->next;
                temp2 = temp2->next;
            }
        }

        selected->next = NULL;

        if (l3.head == NULL) {
            l3.head = selected;
            l3.tail = selected;
            last = selected;
        }
        else {
            last->next = selected;
            last = selected;
            l3.tail = selected;
        }
    }

    while (temp1 != NULL) {

        Node* selected = temp1;
        temp1 = temp1->next;

        selected->next = NULL;

        if (l3.head == NULL) {
            l3.head = selected;
            l3.tail = selected;
        }
        else {
            l3.tail->next = selected;
            l3.tail = selected;
        }
    }

    while (temp2 != NULL) {

        Node* selected = temp2;
        temp2 = temp2->next;

        selected->next = NULL;

        if (l3.head == NULL) {
            l3.head = selected;
            l3.tail = selected;
        }
        else {
            l3.tail->next = selected;
            l3.tail = selected;
        }
    }

    return l3;
}


int main() {

    List GlowCare;
    List BeautyHub;
    int choice;

    cout << "Enter products for GlowCare\n";

    do {

        int id, price;
        string name, category;

        cout << "\nEnter Product ID: ";
        cin >> id;

        cout << "Enter Product Name: ";
        cin >> name;

        cout << "Enter Category: ";
        cin >> category;

        cout << "Enter Price: ";
        cin >> price;

        GlowCare.add(id, name, category, price);

        cout << "Add another product? (1 = Yes, 0 = No): ";
        cin >> choice;

    } while (choice == 1);


    cout << "\nEnter products for BeautyHub\n";

    do {

        int id, price;
        string name, category;

        cout << "\nEnter Product ID: ";
        cin >> id;

        cout << "Enter Product Name: ";
        cin >> name;

        cout << "Enter Category: ";
        cin >> category;

        cout << "Enter Price: ";
        cin >> price;

        BeautyHub.add(id, name, category, price);

        cout << "Add another product? (1 = Yes, 0 = No): ";
        cin >> choice;

    } while (choice == 1);


    cout << "\n========== GLOWCARE ==========\n";
    GlowCare.display();

    cout << "\n========== BEAUTYHUB ==========\n";
    BeautyHub.display();

    List Master = merge(GlowCare, BeautyHub);

    cout << "\n========== MASTER LIST ==========\n";
    Master.display();

    int count = 0;
    int totalValue = 0;

    Node* temp = Master.head;

    while (temp != NULL) {

        count++;
        totalValue += temp->price;

        temp = temp->next;
    }

    cout << "\nTotal Number of Products: " << count << endl;
    cout << "Total Inventory Value: " << totalValue << endl;

    return 0;
}
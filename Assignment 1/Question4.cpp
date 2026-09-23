#include<iostream>
using namespace std;

class Rider {
    public:
        int RiderID;
        string RiderName;
        int AssignedOrders;

        Rider() {}
        Rider (int id, string name, int order) {
            RiderID=id;
            RiderName=name;
            AssignedOrders=order;
        }
};

class Node {
    public:
        Rider rider;
        Node* next;

        Node(Rider r) {
            rider=r;
            next=NULL;
        }
};

class LinkedList {
    public:
        Node* head;
        Node* tail;

        LinkedList() {
            head=tail=NULL;
        }

        int countTotal() {
            if (head == NULL) {
                return 0;
            }
            Node* temp=head;
            int count=0;
            do {
                count++;
                temp=temp->next;
            } while(temp!=head);
            return count;
        }

        void insertAtBeginning(Rider r) {
            Node* newNode = new Node(r);
            if (head==NULL) {
                head=newNode;
                tail=newNode;
                tail->next=head;
            }
            else {
                newNode->next=head;
                head=newNode;
                tail->next=head;
            }
        }

        void insertionAtTheEnd(Rider r) {
            Node* newNode = new Node(r);
            if(head==NULL) {
                head=newNode;
                tail=newNode;
                tail->next=head;
            }
            else {
                tail->next=newNode;
                tail=newNode;
                tail->next=head;
            }
        }

        void insertionAtAPosition(int pos, Rider r) {
            if (pos==0) {
                insertAtBeginning(r);
            }
            else if (pos==countTotal()) {
                insertionAtTheEnd(r);
            }
            else if (pos>countTotal() || pos<0) {
                cout << "Invalid Position\n";
                return;
            } 
            else {
                Node* prev=NULL;
                Node* curr=head;
                while(pos--) {
                    prev=curr;
                    curr=curr->next;
                }
                Node* newNode = new Node(r);
                newNode->next=curr;
                prev->next=newNode;
            }
        }
        
        void deletionFromBeginning() {
            if (head==NULL) {
                cout << "Invalid index\n";
                return;
            }
            else if (head == tail) {
                delete head;
                head=NULL;
                tail=NULL;
            }
            else {
                Node* temp;
                temp=head->next;
                delete head;
                head=temp;
                tail->next=head;
            }
        }

        void deletionFromEnd() {
            if(head==NULL) {
                cout << "Linked list is empty\n";
                return;
            }
            else if (head == tail) {
                delete head;
                head=NULL;
                tail=NULL;
            }
            else {
                Node* temp=head;
                while(temp->next->next!=head) {
                    temp=temp->next;
                }
                delete temp->next;
                tail=temp;
                tail->next=head;
            }
        }

        void deletionFromSpecificPosition(int pos) {
            if (pos==0) {
                deletionFromBeginning();
            }
            else if (pos==countTotal()-1) {
                deletionFromEnd();
            }
            else if (pos>=countTotal() || pos<0) {
                cout << "Invalid Position\n";
                return;
            } 
            else {
                pos-=1;
                Node* prev=NULL;
                Node* curr=head;
                while(pos--) {
                    prev=curr;
                    curr=curr->next;
                }
                prev->next=curr->next;
                delete curr;
            }
        }

        bool searchingByName(string name) {
            if (head==NULL) return false;

            Node* temp=head;
            do {
                if (temp->rider.RiderName==name) return true;
                temp=temp->next;
            } while(temp!=head);
            return false;
            
        }

        bool searchingByID(int id) {
            if (head==NULL) return false;
            Node* temp=head;
            do {
                if (temp->rider.RiderID==id) return true;
                temp=temp->next;
            } while(temp!=head);
            return false;
        }

        void updateRiderInfo(int id) {
            if (searchingByID(id)) {
                string name;
                int orders;
                cout << "Enter the updated name of the rider: ";
                cin >> name;
                cout << "Enter the updated number of orders: ";
                cin >> orders;
                Node* temp = head;
                while(temp->rider.RiderID!=id) {
                    temp=temp->next;
                }
                temp->rider.RiderName=name;
                temp->rider.AssignedOrders=orders;
            }
            else {
                cout << "Rider not found\n";
            }
        }

        void display() {
            if(head==NULL) {
                cout << "The list is empty\n";
                return;
            }
            else {
                Node* temp=head;

                do {
                    cout << "ID: " << temp->rider.RiderID << " | Name: " << temp->rider.RiderName << " | Orders: " << temp->rider.AssignedOrders << endl;
                    temp=temp->next; 
                } while(temp!=head);
            }
        }

        void traversingFromAPosition(int pos) {
            if (head == NULL) {
                cout << "The list is empty\n";
                return;
            }

            if (pos < 0 || pos >= countTotal()) {
                cout << "Invalid Position\n";
                return;
            }

            if (pos==0) display();
            else {
                pos-=1;
                Node* temp=head;
                while(pos--) {
                    temp=temp->next;
                }
                Node* save = temp->next;
                Node* curr = save;
                do {
                    cout << "ID: " << curr->rider.RiderID << " | Name: " << curr->rider.RiderName << " | Orders: " << curr->rider.AssignedOrders << endl;
                    curr=curr->next;
                } while(curr!=save);
            }
        }
};

int main() {

    LinkedList riders;

    int choice;

    do {
        cout << "\n========== KFC RIDER MANAGEMENT SYSTEM ==========\n";
        cout << "1. Insert Rider at Beginning\n";
        cout << "2. Insert Rider at End\n";
        cout << "3. Insert Rider at Specific Position\n";
        cout << "4. Delete Rider from Beginning\n";
        cout << "5. Delete Rider from End\n";
        cout << "6. Delete Rider from Specific Position\n";
        cout << "7. Search Rider by Name\n";
        cout << "8. Search Rider by ID\n";
        cout << "9. Update Rider Information\n";
        cout << "10. Display All Riders\n";
        cout << "11. Count Total Riders\n";
        cout << "12. Traverse from Selected Position\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1 || choice == 2 || choice == 3) {

            int id, orders, pos;
            string name;

            cout << "Enter Rider ID: ";
            cin >> id;

            cout << "Enter Rider Name: ";
            cin >> name;

            cout << "Enter Number of Assigned Orders: ";
            cin >> orders;

            Rider r(id, name, orders);

            if (choice == 1) {
                riders.insertAtBeginning(r);
                cout << "Rider inserted at beginning.\n";
            }
            else if (choice == 2) {
                riders.insertionAtTheEnd(r);
                cout << "Rider inserted at end.\n";
            }
            else {
                cout << "Enter position: ";
                cin >> pos;

                riders.insertionAtAPosition(pos, r);
            }
        }

        else if (choice == 4) {
            riders.deletionFromBeginning();
        }

        else if (choice == 5) {
            riders.deletionFromEnd();
        }

        else if (choice == 6) {
            int pos;

            cout << "Enter position to delete: ";
            cin >> pos;

            riders.deletionFromSpecificPosition(pos);
        }

        else if (choice == 7) {
            string name;

            cout << "Enter Rider Name to search: ";
            cin >> name;

            if (riders.searchingByName(name)) {
                cout << "Rider found.\n";
            }
            else {
                cout << "Rider not found.\n";
            }
        }

        else if (choice == 8) {
            int id;

            cout << "Enter Rider ID to search: ";
            cin >> id;

            if (riders.searchingByID(id)) {
                cout << "Rider found.\n";
            }
            else {
                cout << "Rider not found.\n";
            }
        }

        else if (choice == 9) {
            int id;

            cout << "Enter Rider ID to update: ";
            cin >> id;

            riders.updateRiderInfo(id);
        }

        else if (choice == 10) {
            riders.display();
        }

        else if (choice == 11) {
            cout << "Total Riders: " << riders.countTotal() << endl;
        }

        else if (choice == 12) {
            int pos;

            cout << "Enter starting position: ";
            cin >> pos;

            riders.traversingFromAPosition(pos);
        }

        else if (choice == 0) {
            cout << "Exiting program...\n";
        }

        else {
            cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}
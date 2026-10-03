#include <iostream>
using namespace std;
struct Node { 
    string song; 
    Node *prev,*next; 
};
class Playlist {
private:
    Node *head;
    Node *tail;
    int count;
public: 

    Playlist() { // Constructor
        head = NULL;
        tail = NULL;
        count = 0; 
    }

    ~Playlist() { // Destructor
        Node *temp = head;
        while (temp != NULL) {
            Node *current = temp;
            temp = temp->next;
            delete current; 
        }
        head = NULL;
        tail = NULL;
        count = 0; 
    }
    // Function to remove a song from the playlist at a
    void removeSong(int position)
    { 
        if (head == NULL) return;

        if (position<1) {
            return;
        } 
        count=0;
        Node* temp=head;
        do {
            count++;
            temp=temp->next;
        } while(temp!=head);

        if (position>count) return;
        
        if (count==1) {
            delete head;
            head=NULL;
            tail=NULL;
        }
        else if (position==1) {
            
            Node* temp2=head;
            head=head->next;
            head->prev=tail;
            tail->next=head;
            delete temp2;
        } 
        else if (position==count) {
            Node* curr=tail->prev;
            delete tail;
            tail=curr;
            curr->next=head;
            head->prev=tail;
        }
        else {
            Node* temp=head;
            for(int i=1; i<position; i++) {
                temp=temp->next;
            }
            temp->prev->next=temp->next;
            temp->next->prev=temp->prev;
            delete temp;
        }
        count--;
    }
    // Function to display the playlist
    void display() {
        if (head == NULL) {
            cout << "List is empty." << endl;
            return; 
        }
        Node* temp = head;
        do {
            cout << temp->song << " ";
            temp = temp->next;
        } while (temp != head);
        cout << endl; 
    } 
};
int main() {
    Playlist myList;
    myList.display();
    myList.removeSong(3);
    myList.display();
    return 0;
}

#include<iostream>
using namespace std;

class Song {
public:
    string title;
    string genre;
    int duration;
    bool explicitContent;

    Song(string t, string g, int d, bool e) {
        title = t;
        genre = g;
        duration = d;
        explicitContent = e;
    }
};

class Node {
public:
    Song song;
    Node* next;

    Node(Song s) : song(s) {
        next = NULL;
    }
};

class Playlist {
public:
    Node* head;
    int operationCount;

    Playlist() {
        head = NULL;
        operationCount = 0;
    }

    int size() {
        int count = 0;
        Node* temp = head;

        while(temp != NULL) {
            count++;
            temp = temp->next;
        }

        return count;
    }

    bool isValidPosition(Song s, int pos) {

        int n = size();

        if(pos < 0 || pos > n) return false;

        if(head == NULL) return true;

        Node* prev = NULL;
        Node* curr = head;

        for(int i = 0; i < pos; i++) {
            prev = curr;
            curr = curr->next;
        }

        if(prev != NULL && prev->song.genre == s.genre) return false;

        if(curr != NULL && curr->song.genre == s.genre) return false;

        if(prev != NULL && curr != NULL) {
            if(prev->song.duration +
               s.duration +
               curr->song.duration > 600) {
                return false;
            }
        }

        if(prev != NULL && prev != head) {

            Node* beforePrev = head;

            while(beforePrev->next != prev)
                beforePrev = beforePrev->next;

            if(beforePrev->song.duration +
               prev->song.duration +
               s.duration > 600) {
                return false;
            }
        }

        if(curr != NULL && curr->next != NULL) {

            if(s.duration + curr->song.duration + curr->next->song.duration > 600) {
                return false;
            }
        }

        return true;
    }

    int findValidPosition(Song s, int desiredPos) {

        int n = size();

        if(desiredPos < 0) desiredPos = 0;

        if(desiredPos > n) desiredPos = n;

        for(int pos = desiredPos; pos <= n; pos++) {
            if(isValidPosition(s, pos)) return pos;
        }

        return -1;
    }

    void insert(Song s, int desiredPos) {

        int validPos = findValidPosition(s, desiredPos);

        if(validPos == -1) {
            cout << "No valid position found for this song.\n";
            return;
        }

        Node* newNode = new Node(s);

        if(validPos == 0) {
            newNode->next = head;
            head = newNode;
        }
        else {

            Node* temp = head;

            for(int i = 0; i < validPos - 1; i++) {
                temp = temp->next;
            }

            newNode->next = temp->next;
            temp->next = newNode;
        }

        operationCount++;

        cout << "Song inserted at position " << validPos << ".\n";

        checkAfterThreeOperations();
    }

    Node* search(string title) {

        Node* temp = head;

        while(temp != NULL) {
            if(temp->song.title == title) return temp;
            temp = temp->next;
        }

        return NULL;
    }

    bool removeExplicitFlag(string title) {

        Node* temp = search(title);
        if(temp == NULL) {
            cout << "Song not found.\n";
            return false;
        }

        if(temp->song.explicitContent == false) {
            cout << "Song is already non-explicit.\n";
            return false;
        }

        temp->song.explicitContent = false;

        cout << "Explicit flag removed from the song.\n";

        return true;
    }

    void deleteAt(int pos) {

        if(head == NULL) {
            cout << "Playlist is empty.\n";
            return;
        }

        if(pos < 0 || pos >= size()) {
            cout << "Invalid position.\n";
            return;
        }

        Node* toDelete;
        if(pos == 0) {

            toDelete = head;

            if(toDelete->song.explicitContent) {
                cout << "Cannot delete explicit song.\n";
                cout << "Remove its explicit flag first.\n";
                return;
            }

            head = head->next;
            delete toDelete;
        }

        else {

            Node* temp = head;
            for(int i = 0; i < pos - 1; i++) {
                temp = temp->next;
            }

            toDelete = temp->next;

            if(toDelete->song.explicitContent) {
                cout << "Cannot delete explicit song.\n";
                cout << "Remove its explicit flag first.\n";
                return;
            }

            temp->next = toDelete->next;
            delete toDelete;
        }

        operationCount++;

        cout << "Song deleted successfully.\n";

        checkAfterThreeOperations();
    }

    void display() {

        if(head == NULL) {
            cout << "Playlist is empty.\n";
            return;
        }

        Node* temp = head;
        int pos = 0;

        while(temp != NULL) {

            cout << "\nPosition: " << pos << endl;
            cout << "Title: " << temp->song.title << endl;
            cout << "Genre: " << temp->song.genre << endl;
            cout << "Duration: " << temp->song.duration << " seconds" << endl;

            cout << "Explicit: ";

            if(temp->song.explicitContent) cout << "Yes";
            else cout << "No";
            cout << endl;
            temp = temp->next;
            pos++;
        }
    }

    bool validatePlaylist() {

        Node* prev = NULL;
        Node* curr = head;

        while(curr != NULL) {

            if(prev != NULL) {
                if(prev->song.genre == curr->song.genre) {
                    return false;
                }
            }

            if(prev != NULL && curr->next != NULL) {
                if(prev->song.duration +
                   curr->song.duration +
                   curr->next->song.duration > 600) {
                    return false;
                }
            }

            prev = curr;
            curr = curr->next;
        }

        return true;
    }

    void checkAfterThreeOperations() {
        if(operationCount % 3 == 0) {
            cout << "\n--- 3 Operations Completed ---\n";

            if(validatePlaylist()) cout << "Playlist constraints satisfied.\n";
            else cout << "WARNING: Playlist constraints violated.\n";
        }
    }
};


int main() {

    Playlist playlist;
    int choice;
    do {

        cout << "\n========== MUSIC PLAYLIST ==========\n";
        cout << "1. Insert Song\n";
        cout << "2. Delete Song\n";
        cout << "3. Search Song\n";
        cout << "4. Remove Explicit Flag\n";
        cout << "5. Display Playlist\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if(choice == 1) {

            string title, genre;
            int duration;
            bool explicitContent;
            int position;

            cout << "Enter title: ";
            cin >> title;

            cout << "Enter genre: ";
            cin >> genre;

            cout << "Enter duration in seconds: ";
            cin >> duration;

            cout << "Explicit? (1 = Yes, 0 = No): ";
            cin >> explicitContent;

            cout << "Enter desired position: ";
            cin >> position;

            Song s(title, genre, duration, explicitContent);

            playlist.insert(s, position);
        }

        else if(choice == 2) {

            int position;

            cout << "Enter position to delete: ";
            cin >> position;

            playlist.deleteAt(position);
        }

        else if(choice == 3) {

            string title;

            cout << "Enter song title to search: ";
            cin >> title;

            Node* result = playlist.search(title);

            if(result != NULL) {
                cout << "Song found!\n";
                cout << "Title: " << result->song.title << endl;
                cout << "Genre: " << result->song.genre << endl;
                cout << "Duration: " << result->song.duration << endl;
            }
            else {
                cout << "Song not found.\n";
            }

            playlist.operationCount++;
            playlist.checkAfterThreeOperations();
        }

        else if(choice == 4) {
            string title;

            cout << "Enter song title: ";
            cin >> title;

            if(playlist.removeExplicitFlag(title)) {
                playlist.operationCount++;
                playlist.checkAfterThreeOperations();
            }
        }

        else if(choice == 5) {
            playlist.display();
        }

        else if(choice == 6) {
            cout << "Exiting...\n";
        }

        else {
            cout << "Invalid choice.\n";
        }

    } while(choice != 6);

    return 0;
}
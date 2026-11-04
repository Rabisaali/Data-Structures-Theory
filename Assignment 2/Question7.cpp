
#include<iostream>
using namespace std;

class Parcel {
    public:
        long long tracking;
        string sender;
        string city;
        int region;

        Parcel() {}

        Parcel(long long t, string s, string c, int r) {
            tracking=t;
            sender=s;
            city=c;
            region=r;
        }
};

class Node {
    public:
        Parcel data;
        Node* next;

        Node(Parcel p) {
            data=p;
            next=NULL;
        }
};

void insertEnd(Node*& head, Parcel p) {
    Node* newNode=new Node(p);

    if(head==NULL) {
        head=newNode;
        return;
    }

    Node* temp=head;

    while(temp->next!=NULL) {
        temp=temp->next;
    }

    temp->next=newNode;
}

Node* copyList(Node* head) {
    Node* newHead=NULL;
    Node* tail=NULL;

    while(head!=NULL) {
        Node* newNode=new Node(head->data);

        if(newHead==NULL) {
            newHead=newNode;
            tail=newNode;
        }
        else {
            tail->next=newNode;
            tail=newNode;
        }

        head=head->next;
    }

    return newHead;
}

void display(Node* head) {
    while(head!=NULL) {
        cout << head->data.tracking << " | "
             << head->data.sender << " | "
             << head->data.city << " | "
             << head->data.region << endl;

        head=head->next;
    }
}

void deleteList(Node*& head) {
    while(head!=NULL) {
        Node* temp=head;
        head=head->next;
        delete temp;
    }
}

void radixSort(Node*& head) {
    long long exp=1;

    for(int pass=0; pass<9; pass++) {

        Node* bucketHead[10]={NULL};
        Node* bucketTail[10]={NULL};
        Node* curr=head;

        while(curr!=NULL) {

            Node* nextNode=curr->next;
            curr->next=NULL;

            int digit=(curr->data.tracking/exp)%10;

            if(bucketHead[digit]==NULL) {
                bucketHead[digit]=curr;
                bucketTail[digit]=curr;
            }
            else {
                bucketTail[digit]->next=curr;
                bucketTail[digit]=curr;
            }

            curr=nextNode;
        }

        head=NULL;
        Node* tail=NULL;

        for(int i=0; i<10; i++) {

            if(bucketHead[i]!=NULL) {

                if(head==NULL) {
                    head=bucketHead[i];
                    tail=bucketTail[i];
                }
                else {
                    tail->next=bucketHead[i];
                    tail=bucketTail[i];
                }
            }
        }

        exp=exp*10;
    }
}

Node* merge(Node* left, Node* right) {

    Node* head=NULL;
    Node* tail=NULL;

    while(left!=NULL && right!=NULL) {
        Node* selected;

        if(left->data.region<=right->data.region) {
            selected=left;
            left=left->next;
        }
        else {
            selected=right;
            right=right->next;
        }

        if(head==NULL) {
            head=selected;
            tail=selected;
        }
        else {
            tail->next=selected;
            tail=selected;
        }
    }

    if(left!=NULL) {
        if(head==NULL) head=left;
        else tail->next=left;
    }

    if(right!=NULL) {
        if(head==NULL) head=right;
        else tail->next=right;
    }

    return head;
}

void split(Node* head, Node*& left, Node*& right) {

    Node* slow=head;
    Node* fast=head->next;

    while(fast!=NULL && fast->next!=NULL) {
        slow=slow->next;
        fast=fast->next->next;
    }

    left=head;
    right=slow->next;

    slow->next=NULL;
}

Node* mergeSort(Node* head) {

    if(head==NULL || head->next==NULL) {
        return head;
    }

    Node* left;
    Node* right;

    split(head, left, right);

    left=mergeSort(left);
    right=mergeSort(right);

    return merge(left, right);
}

int main() {

    Parcel parcels[] = {

        Parcel(987654321, "Ali", "Lahore", 3),
        Parcel(123, "Sara", "Karachi", 1),
        Parcel(56789, "Ahmed", "Islamabad", 2),
        Parcel(45, "Zara", "Lahore", 1),
        Parcel(999999999, "Hamza", "Karachi", 3),
        Parcel(123456, "Ayesha", "Peshawar", 2),
        Parcel(789, "Usman", "Islamabad", 1),
        Parcel(456789123, "Hira", "Lahore", 2),
        Parcel(123456789, "Bilal", "Karachi", 3),
        Parcel(100, "Noor", "Peshawar", 2)

    };

    int n=sizeof(parcels)/sizeof(parcels[0]);

    Node* trackingHead=NULL;
    Node* regionHead=NULL;

    // Create two copies of the original records
    for(int i=0; i<n; i++) {
        insertEnd(trackingHead, parcels[i]);
        insertEnd(regionHead, parcels[i]);
    }

    cout << "--- PART 1: RADIX SORT ---\n";

    radixSort(trackingHead);

    cout << "\nParcels sorted by tracking number:\n";
    display(trackingHead);

    cout << "\n--- PART 2: MERGE SORT ---\n";

    regionHead=mergeSort(regionHead);

    cout << "\nParcels sorted by region code:\n";
    display(regionHead);

    deleteList(trackingHead);
    deleteList(regionHead);

    return 0;
}

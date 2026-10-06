#include<iostream>
using namespace std;

class Stop {
    public:
        int stopId;
        string name;
        Stop* next;
        Stop* prev;

        Stop(int is, string n) {
            stopId=is;
            name=n;
            next=NULL;
            prev=NULL;
        }
};

class ShuttleRoute {
    public:
        Stop* head;
        Stop* tail;

        ShuttleRoute() {
            head=NULL;
            tail=NULL;
        }

        void addStop(int id, string name) {
            Stop* s = new Stop(id, name);
            if (head==NULL) {
                head=s;
                s->next=head;
                s->prev=head;
                tail=s;
            }
            else {
                tail->next=s;
                s->prev=tail;
                s->next=head;
                head->prev=s;
                tail=s;
            }
        }

        void travelClockwise(int startID, int numStops) {
            Stop* temp=head;
            while(temp->stopId!=startID) temp=temp->next;

            for(int i=numStops; i>0; i--) {
                cout << "Stop ID: " << temp->stopId << " | Name: " << temp->name << endl;
                temp=temp->next;
            }
        }

        void travelAntiClockwise(int startID, int numStops) {
            Stop* temp=head;
            while(temp->stopId!=startID) temp=temp->prev;

            for(int i=numStops; i>0; i--) {
                cout << "Stop ID: " << temp->stopId << " | Name: " << temp->name << endl;
                temp=temp->prev;
            }
        }

        bool removeStop(int id) {
            Stop* temp=head;
            while(temp->stopId!=id) temp=temp->next;

            if (temp==head) {
                if (head->next!=head && head->prev!=head) {
                    tail->next=head->next;
                    head->next->prev=tail;
                    delete head;
                    head=tail->next;
                }
                else {
                    delete head;
                    head=NULL;
                    tail=NULL;
                }
            }
            else if (temp==tail) {
                if (tail->prev!=tail && tail->next!=tail) {
                    tail->prev->next=head;
                    head->prev=tail->prev;
                    delete tail;
                    tail=head->prev;
                }
                else {
                    delete head;
                    head=NULL;
                    tail=NULL;
                }
            }
            else {
                temp->prev->next=temp->next;
                temp->next->prev=temp->prev;
                delete temp;
            }
            return true;
        }

        int shortestDirection(int fromID, int toID) {
            Stop* temp=head;
            while(temp->stopId!=fromID) temp=temp->next;
            Stop* copy=temp;
            int count=0;
            while(temp->stopId!=toID) {
                count++;
                temp=temp->next;
            }
            int count1=0;
            while(copy->stopId!=toID) {
                count1++;
                copy=copy->prev;
            }
            if (count>count1) return -1;
            else if (count<count1) return 1;
            else return 0;
        }
};
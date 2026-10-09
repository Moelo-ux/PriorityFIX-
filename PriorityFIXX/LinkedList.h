#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Complaint.h"

struct Node {
    Complaint* data;
    Node* next;

    Node(Complaint* c) {
        data = c;
        next = NULL;
    }
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() {
        head = NULL;
    }

    ~LinkedList() {
        Node* current = head;
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            delete temp->data;
            delete temp;
        }
    }

    Node* getHead() {
        return head;
    }

    void addComplaint(Complaint* c) {
        Node* newNode = new Node(c);
        if (head == NULL) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    Complaint* findByID(int id) {
        Node* current = head;
        while (current != NULL) {
            if (current->data->ticketID == id) {
                return current->data;
            }
            current = current->next;
        }
        return NULL;
    }

    void displayAll() {
        if (head == NULL) {
            cout << "No complaints recorded.\n";
            return;
        }
        Node* current = head;
        while (current != NULL) {
            current->data->display();
            current = current->next;
        }
    }

    int countTotal() {
        int count = 0;
        Node* current = head;
        while (current != NULL) {
            count++;
            current = current->next;
        }
        return count;
    }

    int filterByStatus(Status s) {
        int found = 0;
        Node* current = head;
        while (current != NULL) {
            if (current->data->status == s) {
                current->data->display();
                found++;
            }
            current = current->next;
        }
        return found;
    }
};

#endif

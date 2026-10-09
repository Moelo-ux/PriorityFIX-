#ifndef TICKETINGSYSTEM_H
#define TICKETINGSYSTEM_H

#include "helpers.h"
#include "severity.h"
#include "Complaint.h"
#include "LinkedList.h"
#include "MinHeap.h"

class TicketingSystem {
private:
    LinkedList list;
    MinHeap heap;
    int nextID;

    Complaint* findDuplicate(string category, string location) {
        Node* current = list.getHead();
        while (current != NULL) {
            Complaint* c = current->data;
            if (c->status != RESOLVED &&
                toLower(c->category) == toLower(category) &&
                toLower(c->location) == toLower(location)) {
                return c;
            }
            current = current->next;
        }
        return NULL;
    }

public:
    TicketingSystem() {
        nextID = 1001;
    }

    void registerComplaint() {
        cout << "\n--- Register Complaint ---\n";

        if (heap.isFull()) {
            cout << "The waiting queue is full. Cannot add more complaints.\n";
            return;
        }

        cout << "1. Pothole\n2. Pipeline Burst\n3. Exposed Wiring\n4. Other\n";
        int choice = readInt("Choose category (1-4): ");

        string category;
        if (choice == 1) {
            category = "Pothole";
        } else if (choice == 2) {
            category = "Pipeline Burst";
        } else if (choice == 3) {
            category = "Exposed Wiring";
        } else if (choice == 4) {
            category = readText("Enter category name: ");
        } else {
            cout << "Invalid category.\n";
            return;
        }

        string location = readText("Location: ");
        string description = readText("Description: ");
        string timestamp = readText("Timestamp (YYYY-MM-DD HH:MM): ");

        Complaint* duplicate = findDuplicate(category, location);
        if (duplicate != NULL) {
            cout << "\nWARNING: a similar complaint already exists:\n";
            duplicate->display();
            string answer = readText("\nCreate a new ticket anyway? (y/n): ");
            if (answer != "y" && answer != "Y") {
                cout << "Cancelled. No ticket created.\n";
                return;
            }
        }

        int severity = getSeverity(category);
        Complaint* c = new Complaint(nextID, category, location, description, timestamp, severity);
        nextID++;

        list.addComplaint(c);
        heap.insert(c);

        cout << "\nComplaint registered successfully!";
        c->display();
    }

    void showAll() {
        list.displayAll();
    }

    void filterByStatus() {
        int s = readInt("Status (1 = OPEN, 2 = IN_PROGRESS, 3 = RESOLVED): ");
        int found = 0;

        if (s == 1) {
            found = list.filterByStatus(OPEN);
        } else if (s == 2) {
            found = list.filterByStatus(IN_PROGRESS);
        } else if (s == 3) {
            found = list.filterByStatus(RESOLVED);
        } else {
            cout << "Invalid status.\n";
            return;
        }

        cout << "\n" << found << " complaint(s) found.\n";
    }

    void dispatchNext() {
        Complaint* c = heap.extractMin();
        if (c == NULL) {
            cout << "No open complaints waiting.\n";
            return;
        }
        c->status = IN_PROGRESS;
        cout << "\nDispatched the most urgent complaint (now IN_PROGRESS):";
        c->display();
    }

    void advanceStatus() {
        int id = readInt("Enter Ticket ID: ");
        Complaint* c = list.findByID(id);
        if (c == NULL) {
            cout << "Ticket not found.\n";
            return;
        }

        if (c->status == OPEN) {
            heap.removeComplaint(c);
            c->status = IN_PROGRESS;
        } else if (c->status == IN_PROGRESS) {
            c->status = RESOLVED;
        } else {
            cout << "This ticket is already RESOLVED.\n";
            return;
        }
        cout << "Ticket #" << id << " is now " << statusToString(c->status) << ".\n";
    }

    void changeSeverity() {
        int id = readInt("Enter Ticket ID: ");
        Complaint* c = list.findByID(id);
        if (c == NULL) {
            cout << "Ticket not found.\n";
            return;
        }

        int newScore = readInt("New severity score (1 = most urgent, 4 = least urgent): ");
        if (newScore < 1 || newScore > 4) {
            cout << "Invalid score.\n";
            return;
        }

        c->severityScore = newScore;
        heap.reHeapify();
        cout << "Severity updated and the queue was re-ranked.\n";
    }

    void showDashboard() {
        int open = 0, inProgress = 0, resolved = 0;

        Node* current = list.getHead();
        while (current != NULL) {
            if (current->data->status == OPEN) {
                open++;
            } else if (current->data->status == IN_PROGRESS) {
                inProgress++;
            } else {
                resolved++;
            }
            current = current->next;
        }

        cout << "\n========== AUTHORITY DASHBOARD ==========\n";
        cout << "Total complaints: " << list.countTotal() << endl;
        cout << "OPEN: " << open << " | IN_PROGRESS: " << inProgress
             << " | RESOLVED: " << resolved << endl;

        cout << "\nTop-priority open complaint:";
        Complaint* top = heap.peek();
        if (top == NULL) {
            cout << " none\n";
        } else {
            top->display();
        }

        cout << "\nRanked queue (most urgent first):\n";
        heap.displayRanked();
        cout << "=========================================\n";
    }

    void showReports() {
        int open = 0, inProgress = 0, resolved = 0;
        int pothole = 0, pipeline = 0, wiring = 0, other = 0;
        int sev1 = 0, sev2 = 0, sev3 = 0, sev4 = 0;

        Node* current = list.getHead();
        while (current != NULL) {
            Complaint* c = current->data;

            if (c->status == OPEN) {
                open++;
            } else if (c->status == IN_PROGRESS) {
                inProgress++;
            } else {
                resolved++;
            }

            string cat = toLower(c->category);
            if (cat == "pothole") {
                pothole++;
            } else if (cat == "pipeline burst") {
                pipeline++;
            } else if (cat == "exposed wiring") {
                wiring++;
            } else {
                other++;
            }

            if (c->severityScore == 1) {
                sev1++;
            } else if (c->severityScore == 2) {
                sev2++;
            } else if (c->severityScore == 3) {
                sev3++;
            } else {
                sev4++;
            }

            current = current->next;
        }

        cout << "\n============== REPORTS ==============\n";
        cout << "Total complaints: " << list.countTotal() << endl;

        cout << "\nBy category:\n";
        cout << "  Pothole: " << pothole << endl;
        cout << "  Pipeline Burst: " << pipeline << endl;
        cout << "  Exposed Wiring: " << wiring << endl;
        cout << "  Other: " << other << endl;

        cout << "\nBy status:\n";
        cout << "  OPEN: " << open << endl;
        cout << "  IN_PROGRESS: " << inProgress << endl;
        cout << "  RESOLVED: " << resolved << endl;

        cout << "\nSeverity distribution:\n";
        cout << "  Severity 1: " << sev1 << endl;
        cout << "  Severity 2: " << sev2 << endl;
        cout << "  Severity 3: " << sev3 << endl;
        cout << "  Severity 4: " << sev4 << endl;
        cout << "=====================================\n";
    }
};

#endif

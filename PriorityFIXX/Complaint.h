#ifndef COMPLAINT_H
#define COMPLAINT_H

#include "helpers.h"

struct Complaint {
    int ticketID;
    string category;
    string location;
    string description;
    string timestamp;
    int severityScore;
    Status status;

    Complaint(int id, string cat, string loc, string desc, string time, int severity) {
        ticketID = id;
        category = cat;
        location = loc;
        description = desc;
        timestamp = time;
        severityScore = severity;
        status = OPEN;
    }

    void display() {
        cout << "\n\tComplaint Details\n";
        cout << "Ticket ID: " << ticketID << endl;
        cout << "Category: " << category << endl;
        cout << "Location: " << location << endl;
        cout << "Description: " << description << endl;
        cout << "Timestamp: " << timestamp << endl;
        cout << "Severity Score: " << severityScore << endl;
        cout << "Status: " << statusToString(status) << endl;
    }
};

#endif

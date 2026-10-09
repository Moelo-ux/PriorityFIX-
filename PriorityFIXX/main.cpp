#include <iostream>
#include "TicketingSystem.h"
using namespace std;

int main() {
    TicketingSystem system;
    int choice;

    do {
        cout << "\n===== PriorityFIX: Civic Hazard Tracker =====\n";
        cout << "1. Register new complaint\n";
        cout << "2. View dashboard\n";
        cout << "3. Show all complaints\n";
        cout << "4. Show complaints by status\n";
        cout << "5. Dispatch next most urgent complaint\n";
        cout << "6. Advance complaint status\n";
        cout << "7. Change severity score\n";
        cout << "8. Reports\n";
        cout << "0. Exit\n";
        choice = readInt("Enter choice: ");

        if (choice == 1) {
            system.registerComplaint();
        } else if (choice == 2) {
            system.showDashboard();
        } else if (choice == 3) {
            system.showAll();
        } else if (choice == 4) {
            system.filterByStatus();
        } else if (choice == 5) {
            system.dispatchNext();
        } else if (choice == 6) {
            system.advanceStatus();
        } else if (choice == 7) {
            system.changeSeverity();
        } else if (choice == 8) {
            system.showReports();
        } else if (choice == 0) {
            cout << "Goodbye!\n";
        } else {
            cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}

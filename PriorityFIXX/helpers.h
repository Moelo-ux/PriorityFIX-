#ifndef HELPERS_H
#define HELPERS_H

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

enum Status { OPEN, IN_PROGRESS, RESOLVED };

inline string statusToString(Status s) {
    if (s == OPEN) {
        return "OPEN";
    } else if (s == IN_PROGRESS) {
        return "IN_PROGRESS";
    } else {
        return "RESOLVED";
    }
}

inline string toLower(string text) {
    for (int i = 0; i < (int)text.length(); i++) {
        text[i] = tolower(text[i]);
    }
    return text;
}

inline int readInt(string message) {
    int number;
    cout << message;
    cin >> number;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid. Please enter a number: ";
        cin >> number;
    }
    cin.ignore(1000, '\n');
    return number;
}

inline string readText(string message) {
    string line;
    cout << message;
    getline(cin, line);
    return line;
}

#endif

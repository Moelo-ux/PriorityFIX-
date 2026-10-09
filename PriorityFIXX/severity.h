#ifndef SEVERITY_H
#define SEVERITY_H

#include "helpers.h"

inline int getSeverity(string category) {
    string c = toLower(category);
    if (c == "exposed wiring") {
        return 1;
    } else if (c == "pipeline burst") {
        return 2;
    } else if (c == "pothole") {
        return 3;
    } else {
        return 4;
    }
}

#endif

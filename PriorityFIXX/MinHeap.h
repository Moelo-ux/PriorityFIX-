#ifndef MINHEAP_H
#define MINHEAP_H

#include "Complaint.h"

const int MAX_HEAP = 100;

class MinHeap {
private:
    Complaint* items[MAX_HEAP];
    int count;

    bool isHigher(Complaint* a, Complaint* b) {
        if (a->severityScore != b->severityScore) {
            return a->severityScore < b->severityScore;
        }
        if (a->timestamp != b->timestamp) {
            return a->timestamp < b->timestamp;
        }
        return a->ticketID < b->ticketID;
    }

    void swapItems(int i, int j) {
        Complaint* temp = items[i];
        items[i] = items[j];
        items[j] = temp;
    }

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (isHigher(items[index], items[parent])) {
                swapItems(index, parent);
                index = parent;
            } else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int best = index;

            if (left < count && isHigher(items[left], items[best])) {
                best = left;
            }
            if (right < count && isHigher(items[right], items[best])) {
                best = right;
            }

            if (best == index) {
                break;
            }
            swapItems(index, best);
            index = best;
        }
    }

public:
    MinHeap() {
        count = 0;
    }

    bool isEmpty() {
        return count == 0;
    }

    bool isFull() {
        return count == MAX_HEAP;
    }

    void insert(Complaint* c) {
        if (isFull()) {
            return;
        }
        items[count] = c;
        heapifyUp(count);
        count++;
    }

    Complaint* peek() {
        if (isEmpty()) {
            return NULL;
        }
        return items[0];
    }

    Complaint* extractMin() {
        if (isEmpty()) {
            return NULL;
        }
        Complaint* top = items[0];
        items[0] = items[count - 1];
        count--;
        if (count > 0) {
            heapifyDown(0);
        }
        return top;
    }

    void removeComplaint(Complaint* c) {
        int position = -1;
        for (int i = 0; i < count; i++) {
            if (items[i] == c) {
                position = i;
                break;
            }
        }
        if (position == -1) {
            return;
        }

        items[position] = items[count - 1];
        count--;
        if (position < count) {
            heapifyUp(position);
            heapifyDown(position);
        }
    }

    void reHeapify() {
        for (int i = count / 2 - 1; i >= 0; i--) {
            heapifyDown(i);
        }
    }

    void displayRanked() {
        if (isEmpty()) {
            cout << "No open complaints waiting.\n";
            return;
        }

        Complaint* temp[MAX_HEAP];
        for (int i = 0; i < count; i++) {
            temp[i] = items[i];
        }

        for (int i = 0; i < count - 1; i++) {
            int best = i;
            for (int j = i + 1; j < count; j++) {
                if (isHigher(temp[j], temp[best])) {
                    best = j;
                }
            }
            Complaint* swap = temp[i];
            temp[i] = temp[best];
            temp[best] = swap;
        }

        for (int i = 0; i < count; i++) {
            cout << (i + 1) << ". [Severity " << temp[i]->severityScore << "] Ticket #"
                 << temp[i]->ticketID << " | " << temp[i]->category
                 << " | " << temp[i]->location << " | " << temp[i]->timestamp << endl;
        }
    }
};

#endif

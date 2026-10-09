# PriorityFIX (Phase 2, clean version)

| File | Holds |
|------|-------|
| helpers.h | Status enum, toLower, readInt, readText |
| severity.h | getSeverity() |
| Complaint.h | struct Complaint |
| LinkedList.h | Node + LinkedList |
| MinHeap.h | MinHeap |
| TicketingSystem.h | TicketingSystem |
| main.cpp | the menu |

Build and run (terminal, inside this folder):

    g++ main.cpp -o priorityfix
    ./priorityfix          (Windows PowerShell: .\priorityfix)

Or press Ctrl+Shift+B. Only main.cpp is compiled; it pulls in the headers with #include.

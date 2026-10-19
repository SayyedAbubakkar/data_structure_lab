#include <iostream>
#include <string>
using namespace std;


struct Patient {
    string id;
    int priority;
};


class EmergencyQueue {
private:
    static const int SIZE = 10;
    Patient patients[SIZE];
    int count;

    
    static bool urgentThan(const Patient& a, const Patient& b) {
        return a.priority < b.priority;
    }

public:
    EmergencyQueue() : count(0) {}

    bool isFull() const { return count == SIZE; }
    bool isEmpty() const { return count == 0; }

    void insert(const string& id, int priority) {
        if (isFull()) {
            cout << "Queue full: cannot admit patient " << id << ".\n";
            return;
        }
        int pos = count;
        while (pos > 0 && urgentThan({id, priority}, patients[pos - 1])) {
            patients[pos] = patients[pos - 1];
            pos--;
        }
        patients[pos] = {id, priority};
        count++;
        cout << "Patient " << id << " admitted with priority " << priority << ".\n";
    }

    void treatNext() {
        if (isEmpty()) {
            cout << "No patients waiting.\n";
            return;
        }
        cout << "Treating patient " << patients[0].id
             << " (priority " << patients[0].priority << ").\n";
        for (int i = 1; i < count; i++)
            patients[i - 1] = patients[i];
        count--;
    }

    void display() const {
        if (isEmpty()) {
            cout << "No patients waiting.\n";
            return;
        }
        cout << "Waiting patients (next to be treated first):\n";
        for (int i = 0; i < count; i++)
            cout << "  " << patients[i].id << "  priority " << patients[i].priority << "\n";
    }
};


void showMenu() {
    cout << "\n--- Hospital Emergency Department ---\n"
         << "1. Admit patient\n"
         << "2. Treat next patient\n"
         << "3. Display waiting patients\n"
         << "4. Exit\n"
         << "Enter choice: ";
}


int main() {
    EmergencyQueue queue;
    int choice, priority;
    string id;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter patient ID: ";
                cin >> id;
                cout << "Enter priority (1 = highest): ";
                cin >> priority;
                if (priority < 1) {
                    cout << "Invalid priority. Must be 1 or greater.\n";
                    break;
                }
                queue.insert(id, priority);
                break;
            case 2:
                queue.treatNext();
                break;
            case 3:
                queue.display();
                break;
            case 4:
                cout << "Exiting.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 4);

    return 0;
}
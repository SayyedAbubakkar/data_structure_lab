
#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct Patient {
    int id;
    string name;
    int age;
    Patient* next;
};

class PatientList {
    Patient* head;
public:
    PatientList() : head(nullptr) {}
    ~PatientList() {
        while (head) { Patient* t = head; head = head->next; delete t; }
    }

    Patient* createNode(int id, const string& name, int age) {
        return new Patient{id, name, age, nullptr};
    }

    bool exists(int id) {
        for (Patient* c = head; c; c = c->next) if (c->id == id) return true;
        return false;
    }

    // Add a normal patient at the end
    void addAtEnd(int id, const string& name, int age) {
        if (exists(id)) { cout << "Patient ID " << id << " already exists.\n"; return; }
        Patient* n = createNode(id, name, age);
        if (!head) head = n;
        else {
            Patient* c = head;
            while (c->next) c = c->next;
            c->next = n;
        }
        cout << "Patient " << name << " added at the end of the waiting list.\n";
    }

    // Add an emergency patient at the beginning
    void addAtBeginning(int id, const string& name, int age) {
        if (exists(id)) { cout << "Patient ID " << id << " already exists.\n"; return; }
        Patient* n = createNode(id, name, age);
        n->next = head;
        head = n;
        cout << "EMERGENCY patient " << name << " added at the beginning.\n";
    }

    void search(int id) {
        for (Patient* c = head; c; c = c->next) {
            if (c->id == id) {
                cout << "Patient found -> ID: " << c->id << ", Name: " << c->name
                     << ", Age: " << c->age << "\n";
                return;
            }
        }
        cout << "Patient with ID " << id << " does not exist.\n";
    }

    void removeById(int id) {
        if (!head) { cout << "Waiting list is empty. Patient does not exist.\n"; return; }
        if (head->id == id) {
            Patient* t = head; head = head->next;
            cout << "Patient " << t->name << " treated and removed.\n";
            delete t; return;
        }
        Patient* c = head;
        while (c->next && c->next->id != id) c = c->next;
        if (!c->next) { cout << "Patient with ID " << id << " does not exist.\n"; return; }
        Patient* t = c->next;
        c->next = t->next;
        cout << "Patient " << t->name << " treated and removed.\n";
        delete t;
    }

    void display() {
        if (!head) { cout << "No patients in the waiting list.\n"; return; }
        cout << "\n--- Waiting Patients ---\n";
        for (Patient* c = head; c; c = c->next)
            cout << "[ID: " << c->id << " | " << c->name << " | Age: " << c->age << "] -> ";
        cout << "NULL\n";
    }
};

int readInt(const string& prompt) {
    int x;
    cout << prompt;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. " << prompt;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return x;
}

string readLine(const string& prompt) {
    string s;
    cout << prompt;
    getline(cin, s);
    return s;
}

int main() {
    PatientList list;
    int choice;
    do {
        cout << "\n===== Hospital Emergency Patient Management =====\n"
             << "1. Add new patient at end\n"
             << "2. Add emergency patient at beginning\n"
             << "3. Search patient by ID\n"
             << "4. Remove patient after treatment\n"
             << "5. Display all waiting patients\n"
             << "0. Exit\n";
        choice = readInt("Enter choice: ");
        int id, age; string name;
        switch (choice) {
            case 1:
            case 2:
                id = readInt("Patient ID: ");
                name = readLine("Patient Name: ");
                age = readInt("Patient Age: ");
                if (choice == 1) list.addAtEnd(id, name, age);
                else list.addAtBeginning(id, name, age);
                break;
            case 3:
                id = readInt("Enter Patient ID to search: ");
                list.search(id);
                break;
            case 4:
                id = readInt("Enter Patient ID to remove: ");
                list.removeById(id);
                break;
            case 5:
                list.display();
                break;
            case 0:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 0);
    return 0;
}
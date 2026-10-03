
#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct Student {
    int roll;
    string name;
    string status;   // "Present" or "Absent"
    Student* next;
};

class AttendanceList {
    Student* head;
public:
    AttendanceList() : head(nullptr) {}
    ~AttendanceList() {
        while (head) { Student* t = head; head = head->next; delete t; }
    }

    void addStudent(int roll, const string& name, const string& status) {
        for (Student* c = head; c; c = c->next)
            if (c->roll == roll) { cout << "Roll Number " << roll << " already exists.\n"; return; }
        Student* n = new Student{roll, name, status, nullptr};
        if (!head) head = n;
        else {
            Student* c = head;
            while (c->next) c = c->next;
            c->next = n;
        }
        cout << "Student " << name << " added to the attendance list.\n";
    }

    void search(int roll) {
        for (Student* c = head; c; c = c->next) {
            if (c->roll == roll) {
                cout << "Found -> Roll No: " << c->roll << ", Name: " << c->name
                     << ", Status: " << c->status << "\n";
                return;
            }
        }
        cout << "Student not found.\n";
    }

    void deleteStudent(int roll) {
        if (!head) { cout << "Student not found.\n"; return; }
        if (head->roll == roll) {
            Student* t = head; head = head->next;
            cout << "Student " << t->name << " deleted.\n";
            delete t; return;
        }
        Student* c = head;
        while (c->next && c->next->roll != roll) c = c->next;
        if (!c->next) { cout << "Student not found.\n"; return; }
        Student* t = c->next;
        c->next = t->next;
        cout << "Student " << t->name << " deleted.\n";
        delete t;
    }

    void display() {
        if (!head) { cout << "Attendance list is empty.\n"; return; }
        cout << "\nRoll No\tName\t\tStatus\n";
        cout << "-----------------------------------\n";
        for (Student* c = head; c; c = c->next)
            cout << c->roll << "\t" << c->name << "\t\t" << c->status << "\n";
    }

    int countPresent() {
        int count = 0;
        for (Student* c = head; c; c = c->next)
            if (c->status == "Present") count++;
        return count;
    }

    int countTotal() {
        int count = 0;
        for (Student* c = head; c; c = c->next) count++;
        return count;
    }

    void displayFinal() {
        cout << "\n===== FINAL ATTENDANCE LIST =====";
        display();
        cout << "-----------------------------------\n";
        cout << "Total students : " << countTotal() << "\n";
        cout << "Total present  : " << countPresent() << "\n";
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

int main() {
    AttendanceList list;
    int choice;
    do {
        cout << "\n===== Student Attendance System =====\n"
             << "1. Add student\n"
             << "2. Search student by Roll Number\n"
             << "3. Delete student\n"
             << "4. Display all students\n"
             << "5. Count students present\n"
             << "6. Display final attendance list\n"
             << "0. Exit\n";
        choice = readInt("Enter choice: ");
        int roll; string name, status;
        switch (choice) {
            case 1: {
                roll = readInt("Roll Number: ");
                cout << "Student Name: "; getline(cin, name);
                int s = readInt("Attendance (1 = Present, 2 = Absent): ");
                status = (s == 1) ? "Present" : "Absent";
                list.addStudent(roll, name, status);
                break;
            }
            case 2:
                roll = readInt("Enter Roll Number to search: ");
                list.search(roll);
                break;
            case 3:
                roll = readInt("Enter Roll Number to delete: ");
                list.deleteStudent(roll);
                break;
            case 4:
                list.display();
                break;
            case 5:
                cout << "Total students present: " << list.countPresent() << "\n";
                break;
            case 6:
                list.displayFinal();
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
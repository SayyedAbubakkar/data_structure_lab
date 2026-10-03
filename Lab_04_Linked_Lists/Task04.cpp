#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct Course {
    string code;
    string name;
    int credits;
    Course* next;
};

// ---------- Utility ----------
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

// ---------- List operations ----------
bool courseExists(Course* head, const string& code) {
    for (Course* c = head; c; c = c->next) if (c->code == code) return true;
    return false;
}

void addAtBeginning(Course*& head, const string& code, const string& name, int cr) {
    if (courseExists(head, code)) { cout << "Course " << code << " already exists.\n"; return; }
    head = new Course{code, name, cr, head};
    cout << "Course " << code << " added at beginning.\n";
}

void addAtEnd(Course*& head, const string& code, const string& name, int cr) {
    if (courseExists(head, code)) { cout << "Course " << code << " already exists.\n"; return; }
    Course* n = new Course{code, name, cr, nullptr};
    if (!head) head = n;
    else {
        Course* c = head;
        while (c->next) c = c->next;
        c->next = n;
    }
    cout << "Course " << code << " added at end.\n";
}

void searchCourse(Course* head, const string& code) {
    for (Course* c = head; c; c = c->next) {
        if (c->code == code) {
            cout << "Course found -> Code: " << c->code << ", Name: " << c->name
                 << ", Credit Hours: " << c->credits << "\n";
            return;
        }
    }
    cout << "Course " << code << " not found.\n";
}

void deleteCourse(Course*& head, const string& code) {
    if (!head) { cout << "Course " << code << " not found (list is empty).\n"; return; }
    if (head->code == code) {
        Course* t = head; head = head->next;
        cout << "Course " << code << " deleted.\n";
        delete t; return;
    }
    Course* c = head;
    while (c->next && c->next->code != code) c = c->next;
    if (!c->next) { cout << "Course " << code << " not found.\n"; return; }
    Course* t = c->next;
    c->next = t->next;
    cout << "Course " << code << " deleted.\n";
    delete t;
}

void displayCourses(Course* head) {
    if (!head) { cout << "No courses in the list.\n"; return; }
    for (Course* c = head; c; c = c->next) {
        cout << c->code;
        if (c->next) cout << " -> ";
    }
    cout << "\n";
    for (Course* c = head; c; c = c->next)
        cout << "  " << c->code << " | " << c->name << " | " << c->credits << " CH\n";
}

int countCourses(Course* head) {
    int n = 0;
    for (Course* c = head; c; c = c->next) n++;
    return n;
}

// Appends list2 to the end of list1 (list2 becomes empty, nodes are moved)
void concatenate(Course*& list1, Course*& list2) {
    if (!list2) { cout << "Second list is empty. Nothing to concatenate.\n"; return; }
    if (!list1) list1 = list2;
    else {
        Course* c = list1;
        while (c->next) c = c->next;
        c->next = list2;
    }
    list2 = nullptr;
    cout << "Lists concatenated.\n";
}

void freeList(Course*& head) {
    while (head) { Course* t = head; head = head->next; delete t; }
}

// Loads the sample data from the task description
void loadSample(Course*& morning, Course*& evening) {
    addAtEnd(morning, "CS101", "Intro to Computing", 3);
    addAtEnd(morning, "AI201", "Artificial Intelligence", 3);
    addAtEnd(morning, "DS301", "Data Structures", 4);
    addAtEnd(evening, "SE101", "Software Engineering", 3);
    addAtEnd(evening, "WEB201", "Web Technologies", 3);
    addAtEnd(evening, "DB301", "Database Systems", 4);
}

int main() {
    Course* morning = nullptr;
    Course* evening = nullptr;
    int choice;

    cout << "Loading sample courses...\n";
    loadSample(morning, evening);

    do {
        cout << "\n===== Course Management (Morning / Evening) =====\n"
             << "1. Add Course at Beginning\n"
             << "2. Add Course at End\n"
             << "3. Search Course\n"
             << "4. Delete Course\n"
             << "5. Display All Courses\n"
             << "6. Count Total Courses\n"
             << "7. Concatenate Another Course List\n"
             << "8. Exit\n";
        choice = readInt("Enter choice: ");

        if (choice >= 1 && choice <= 6) {
            int w = readInt("Select list (1 = Morning, 2 = Evening): ");
            Course*& list = (w == 2) ? evening : morning;
            string lname = (w == 2) ? "Evening" : "Morning";
            string code, name; int cr;
            switch (choice) {
                case 1:
                case 2:
                    code = readLine("Course Code: ");
                    name = readLine("Course Name: ");
                    cr = readInt("Credit Hours: ");
                    if (choice == 1) addAtBeginning(list, code, name, cr);
                    else addAtEnd(list, code, name, cr);
                    break;
                case 3:
                    code = readLine("Enter Course Code to search: ");
                    searchCourse(list, code);
                    break;
                case 4:
                    code = readLine("Enter Course Code to delete: ");
                    deleteCourse(list, code);
                    break;
                case 5:
                    cout << lname << " Courses:\n";
                    displayCourses(list);
                    break;
                case 6:
                    cout << "Total " << lname << " courses: " << countCourses(list) << "\n";
                    break;
            }
        } else if (choice == 7) {
            concatenate(morning, evening);
            cout << "Combined Course List:\n";
            displayCourses(morning);
            cout << "Total courses: " << countCourses(morning) << "\n";
        } else if (choice == 8) {
            cout << "Exiting program.\n";
        } else {
            cout << "Invalid choice.\n";
        }
    } while (choice != 8);

    freeList(morning);
    freeList(evening);
    return 0;
}
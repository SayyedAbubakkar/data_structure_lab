#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct Order {
    string id;
    string customer;
    string food;
    Order* next;
};

class OrderList {
    Order* head;
public:
    OrderList() : head(nullptr) {}
    ~OrderList() {
        while (head) { Order* t = head; head = head->next; delete t; }
    }

    bool exists(const string& id) {
        for (Order* c = head; c; c = c->next) if (c->id == id) return true;
        return false;
    }

    void addAtEnd(const string& id, const string& cust, const string& food) {
        if (exists(id)) { cout << "Order " << id << " already exists.\n"; return; }
        Order* n = new Order{id, cust, food, nullptr};
        if (!head) head = n;
        else {
            Order* c = head;
            while (c->next) c = c->next;
            c->next = n;
        }
        cout << "New order " << id << " added.\n";
    }

    void addUrgent(const string& id, const string& cust, const string& food) {
        if (exists(id)) { cout << "Order " << id << " already exists.\n"; return; }
        head = new Order{id, cust, food, head};
        cout << "Urgent Order " << id << " received.\n";
    }

    void search(const string& id) {
        for (Order* c = head; c; c = c->next) {
            if (c->id == id) {
                cout << "Order found -> ID: " << c->id << ", Customer: " << c->customer
                     << ", Food: " << c->food << "\n";
                return;
            }
        }
        cout << "Order " << id << " not found.\n";
    }

    void removeDelivered(const string& id) {
        if (!head) { cout << "No pending orders.\n"; return; }
        if (head->id == id) {
            Order* t = head; head = head->next;
            cout << "Order " << id << " delivered.\n";
            delete t; return;
        }
        Order* c = head;
        while (c->next && c->next->id != id) c = c->next;
        if (!c->next) { cout << "Order " << id << " not found.\n"; return; }
        Order* t = c->next;
        c->next = t->next;
        cout << "Order " << id << " delivered.\n";
        delete t;
    }

    // Shows the chain of IDs, e.g. O104 -> O101 -> O102
    void displayChain() {
        if (!head) { cout << "No pending orders.\n"; return; }
        for (Order* c = head; c; c = c->next) {
            cout << c->id;
            if (c->next) cout << " -> ";
        }
        cout << "\n";
    }

    void displayDetails() {
        if (!head) { cout << "No pending orders.\n"; return; }
        cout << "Pending Orders:\n";
        for (Order* c = head; c; c = c->next)
            cout << "  " << c->id << " | " << c->customer << " | " << c->food << "\n";
        cout << "Chain: ";
        displayChain();
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
    OrderList list;
    int choice;
    do {
        cout << "\n===== Online Food Delivery Orders =====\n"
             << "1. Add new order at end\n"
             << "2. Add urgent order at beginning\n"
             << "3. Search order by ID\n"
             << "4. Remove delivered order\n"
             << "5. Display pending orders\n"
             << "0. Exit\n";
        choice = readInt("Enter choice: ");
        string id, cust, food;
        switch (choice) {
            case 1:
            case 2:
                id = readLine("Order ID: ");
                cust = readLine("Customer Name: ");
                food = readLine("Food Item: ");
                if (choice == 1) list.addAtEnd(id, cust, food);
                else list.addUrgent(id, cust, food);
                cout << "Updated list: "; list.displayChain();
                break;
            case 3:
                id = readLine("Enter Order ID to search: ");
                list.search(id);
                break;
            case 4:
                id = readLine("Enter delivered Order ID: ");
                list.removeDelivered(id);
                cout << "Updated list: "; list.displayChain();
                break;
            case 5:
                list.displayDetails();
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
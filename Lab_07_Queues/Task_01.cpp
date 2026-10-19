#include <iostream>
using namespace std;


class BankQueue {
private:
    static const int SIZE = 5;
    int tokens[SIZE];
    int front;
    int rear;

public:
    BankQueue() : front(0), rear(-1) {}

    bool isFull() const { return rear == SIZE - 1; }
    bool isEmpty() const { return front > rear; }
    int count() const { return isEmpty() ? 0 : rear - front + 1; }

    void enqueue(int token) {
        if (isFull()) {
            cout << "Overflow: queue is full, cannot add token " << token << ".\n";
            return;
        }
        tokens[++rear] = token;
        cout << "Customer " << token << " added to the queue.\n";
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Underflow: no customers are waiting.\n";
            return;
        }
        cout << "Serving customer " << tokens[front++] << ".\n";
    }

    void display() const {
        if (isEmpty()) {
            cout << "No customers waiting.\n";
            return;
        }
        cout << "Waiting customers (front to rear): ";
        for (int i = front; i <= rear; i++)
            cout << tokens[i] << " ";
        cout << "\n";
    }

    void displayCount() const {
        cout << "Number of waiting customers: " << count() << "\n";
    }
};


void showMenu() {
    cout << "\n--- Bank Customer Service System ---\n"
         << "1. Add customer (enqueue)\n"
         << "2. Serve customer (dequeue)\n"
         << "3. Display waiting customers\n"
         << "4. Display number of waiting customers\n"
         << "5. Exit\n"
         << "Enter choice: ";
}


int main() {
    BankQueue queue;
    int choice, token;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter token number: ";
                cin >> token;
                queue.enqueue(token);
                break;
            case 2:
                queue.dequeue();
                break;
            case 3:
                queue.display();
                break;
            case 4:
                queue.displayCount();
                break;
            case 5:
                cout << "Exiting.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}
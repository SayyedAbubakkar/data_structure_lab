#include <iostream>
using namespace std;


class StationDeque {
private:
    static const int SIZE = 6;
    int requests[SIZE];
    int front;
    int rear;
    int count;

public:
    StationDeque() : front(0), rear(SIZE - 1), count(0) {}

    bool isFull() const { return count == SIZE; }
    bool isEmpty() const { return count == 0; }

    void insertFront(int id) {
        if (isFull()) {
            cout << "Deque full: cannot insert request " << id << ".\n";
            return;
        }
        front = (front - 1 + SIZE) % SIZE;
        requests[front] = id;
        count++;
        cout << "Request " << id << " inserted at the front.\n";
    }

    void insertRear(int id) {
        if (isFull()) {
            cout << "Deque full: cannot insert request " << id << ".\n";
            return;
        }
        rear = (rear + 1) % SIZE;
        requests[rear] = id;
        count++;
        cout << "Request " << id << " inserted at the rear.\n";
    }

    void removeFront() {
        if (isEmpty()) {
            cout << "Deque empty: nothing to remove from the front.\n";
            return;
        }
        cout << "Request " << requests[front] << " removed from the front.\n";
        front = (front + 1) % SIZE;
        count--;
    }

    void removeRear() {
        if (isEmpty()) {
            cout << "Deque empty: nothing to remove from the rear.\n";
            return;
        }
        cout << "Request " << requests[rear] << " removed from the rear.\n";
        rear = (rear - 1 + SIZE) % SIZE;
        count--;
    }

    void display() const {
        if (isEmpty()) {
            cout << "No requests waiting.\n";
            return;
        }
        cout << "Front -> ";
        for (int i = 0; i < count; i++) {
            cout << requests[(front + i) % SIZE];
            if (i < count - 1) cout << ", ";
        }
        cout << " <- Rear\n";
    }
};


void showMenu() {
    cout << "\n--- Train Station Passenger Management ---\n"
         << "1. Insert request at front\n"
         << "2. Insert request at rear\n"
         << "3. Remove request from front\n"
         << "4. Remove request from rear\n"
         << "5. Display requests\n"
         << "6. Exit\n"
         << "Enter choice: ";
}


int main() {
    StationDeque deque;
    int choice, id;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter request ID: ";
                cin >> id;
                deque.insertFront(id);
                break;
            case 2:
                cout << "Enter request ID: ";
                cin >> id;
                deque.insertRear(id);
                break;
            case 3:
                deque.removeFront();
                break;
            case 4:
                deque.removeRear();
                break;
            case 5:
                deque.display();
                break;
            case 6:
                cout << "Exiting.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 6);

    return 0;
}
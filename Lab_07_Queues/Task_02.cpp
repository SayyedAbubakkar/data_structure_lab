#include <iostream>
using namespace std;


class PacketQueue {
private:
    static const int SIZE = 5;
    int packets[SIZE];
    int front;
    int rear;
    int count;

public:
    PacketQueue() : front(0), rear(-1), count(0) {}

    bool isFull() const { return count == SIZE; }
    bool isEmpty() const { return count == 0; }

    void enqueue(int id) {
        if (isFull()) {
            cout << "Queue full: packet " << id << " dropped.\n";
            return;
        }
        rear = (rear + 1) % SIZE;
        packets[rear] = id;
        count++;
        cout << "Packet " << id << " stored at index " << rear << ".\n";
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Queue empty: no packets to transmit.\n";
            return;
        }
        cout << "Transmitting packet " << packets[front]
             << " from index " << front << ".\n";
        front = (front + 1) % SIZE;
        count--;
    }

    void display() const {
        if (isEmpty()) {
            cout << "No packets waiting.\n";
            return;
        }
        cout << "Waiting packets (front to rear): ";
        for (int i = 0; i < count; i++)
            cout << packets[(front + i) % SIZE] << " ";
        cout << "\n";
    }
};


void showMenu() {
    cout << "\n--- Network Packet Management ---\n"
         << "1. Insert packet\n"
         << "2. Transmit packet\n"
         << "3. Display waiting packets\n"
         << "4. Exit\n"
         << "Enter choice: ";
}


int main() {
    PacketQueue queue;
    int choice, id;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter packet ID: ";
                cin >> id;
                queue.enqueue(id);
                break;
            case 2:
                queue.dequeue();
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
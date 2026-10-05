#include <iostream>
#include <string>
using namespace std;


class Node {
public:
    string name;
    Node* next;

    Node(const string& playerName) : name(playerName), next(NULL) {}
};


class GameTurns {
private:
    Node* tail;

public:
    GameTurns() : tail(NULL) {}

    ~GameTurns() {
        if (tail == NULL) return;
        Node* current = tail->next;
        tail->next = NULL;
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }

    void addPlayer(const string& name) {
        Node* newNode = new Node(name);
        if (tail == NULL) {
            newNode->next = newNode;
            tail = newNode;
            return;
        }
        newNode->next = tail->next;
        tail->next = newNode;
        tail = newNode;
    }

    void displayTurns() const {
        if (tail == NULL) return;
        Node* first = tail->next;
        Node* current = first;
        int turn = 1;
        do {
            cout << "Turn " << turn++ << ": " << current->name << endl;
            current = current->next;
        } while (current != first);
    }

    void showWrapAround() const {
        if (tail == NULL) return;
        cout << "Last player: " << tail->name << endl;
        cout << "Next turn goes to: " << tail->next->name << " (first player)" << endl;
    }
};


int main() {
    GameTurns game;

    game.addPlayer("Ali");
    game.addPlayer("Sara");
    game.addPlayer("Ahmed");
    game.addPlayer("Fatima");
    game.addPlayer("Usman");

    cout << "Player turns:" << endl;
    game.displayTurns();

    cout << "\nAfter the last player:" << endl;
    game.showWrapAround();

    return 0;
}
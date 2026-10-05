#include <iostream>
#include <string>
using namespace std;

// Node
class Node {
public:
    string song;
    Node* next;

    Node(const string& songName) : song(songName), next(NULL) {}
};


class Playlist {
private:
    Node* tail;
    int count;

public:
    Playlist() : tail(NULL), count(0) {}

    ~Playlist() {
        if (tail == NULL) return;
        Node* current = tail->next;
        tail->next = NULL;
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }

    void addSong(const string& name) {
        Node* newNode = new Node(name);
        if (tail == NULL) {
            newNode->next = newNode;
            tail = newNode;
        } else {
            newNode->next = tail->next;
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }

    void displayAll() const {
        if (tail == NULL) return;
        Node* first = tail->next;
        Node* current = first;
        do {
            cout << current->song << endl;
            current = current->next;
        } while (current != first);
    }

    void play(int rounds) const {
        if (tail == NULL) return;
        Node* current = tail->next;
        for (int round = 1; round <= rounds; round++) {
            cout << "Round " << round << ":" << endl;
            for (int i = 0; i < count; i++) {
                cout << "  Playing: " << current->song << endl;
                current = current->next;
            }
        }
    }
};


int main() {
    Playlist playlist;

    playlist.addSong("Song A");
    playlist.addSong("Song B");
    playlist.addSong("Song C");
    playlist.addSong("Song D");
    playlist.addSong("Song E");

    cout << "Playlist:" << endl;
    playlist.displayAll();

    cout << "\nPlaying 2 complete rounds:" << endl;
    playlist.play(2);

    return 0;
}
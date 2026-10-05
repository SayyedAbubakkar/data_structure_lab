#include <iostream>
#include <string>
using namespace std;


class Node {
public:
    string image;
    Node* prev;
    Node* next;

    Node(const string& imageName) : image(imageName), prev(NULL), next(NULL) {}
};


class ImageGallery {
private:
    Node* head;
    Node* tail;

public:
    ImageGallery() : head(NULL), tail(NULL) {}

    ~ImageGallery() {
        Node* current = head;
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }

    void addImage(const string& name) {
        Node* newNode = new Node(name);
        if (head == NULL) {
            head = tail = newNode;
            return;
        }
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    void displayForward() const {
        for (Node* current = head; current != NULL; current = current->next) {
            cout << current->image << endl;
        }
    }

    void displayBackward() const {
        for (Node* current = tail; current != NULL; current = current->prev) {
            cout << current->image << endl;
        }
    }

    void demonstrateNavigation() const {
        Node* current = head;
        cout << "Start at first image: " << current->image << endl;

        current = current->next;
        cout << "next -> " << current->image << endl;

        current = current->next;
        cout << "next -> " << current->image << endl;

        current = current->prev;
        cout << "prev -> " << current->image << endl;

        current = current->prev;
        cout << "prev -> " << current->image << endl;
    }
};


int main() {
    ImageGallery gallery;

    gallery.addImage("sunset.jpg");
    gallery.addImage("mountain.png");
    gallery.addImage("beach.jpg");
    gallery.addImage("city.png");
    gallery.addImage("forest.jpg");

    cout << "Images (first -> last):" << endl;
    gallery.displayForward();

    cout << "\nImages (last -> first):" << endl;
    gallery.displayBackward();

    cout << "\nNavigation using next and prev:" << endl;
    gallery.demonstrateNavigation();

    return 0;
}
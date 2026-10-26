#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int v) : data(v), left(nullptr), right(nullptr) {}
};

class BST {
    Node* root;

    Node* insert(Node* node, int value) {
        if (!node) return new Node(value);
        if (value < node->data) node->left = insert(node->left, value);
        else if (value > node->data) node->right = insert(node->right, value);
        return node;
    }

    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }

    void insert(int value) { root = insert(root, value); }

    bool search(int key, int& comparisons) const {
        Node* current = root;
        comparisons = 0;
        while (current) {
            comparisons++;
            if (key == current->data) return true;
            current = (key < current->data) ? current->left : current->right;
        }
        return false;
    }
};

int main() {
    BST library;

    // Book IDs
    int ids[] = {40, 20, 60, 10, 30, 50, 70};
    for (int id : ids) library.insert(id);

    // Search
    int key, comparisons;
    cout << "Enter book ID to search: ";
    cin >> key;

    if (library.search(key, comparisons)) cout << "Book Found\n";
    else cout << "Book Not Found\n";
    cout << "Number of comparisons: " << comparisons << endl;
    return 0;
}
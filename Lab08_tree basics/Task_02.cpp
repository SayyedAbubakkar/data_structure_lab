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
        else cout << "Roll number " << value << " already exists, skipped.\n";
        return node;
    }

    void inorder(Node* node) const {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
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

    void inorder() const {
        inorder(root);
        cout << endl;
    }
};

int main() {
    BST tree;

    // Initial roll numbers
    int rolls[] = {45, 25, 65, 15, 35, 55, 75};
    for (int r : rolls) tree.insert(r);

    cout << "Initial roll numbers (ascending): ";
    tree.inorder();

    // User input
    for (int i = 1; i <= 2; i++) {
        int value;
        cout << "Enter additional roll number " << i << ": ";
        cin >> value;
        tree.insert(value);
    }

    cout << "Updated roll numbers (ascending): ";
    tree.inorder();
    return 0;
}
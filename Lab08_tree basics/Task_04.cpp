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
    const char* lastCase = "";

    Node* insert(Node* node, int value) {
        if (!node) return new Node(value);
        if (value < node->data) node->left = insert(node->left, value);
        else if (value > node->data) node->right = insert(node->right, value);
        return node;
    }

    Node* minNode(Node* node) const {
        while (node->left) node = node->left;
        return node;
    }

    Node* remove(Node* node, int key, bool& found) {
        if (!node) return nullptr;

        if (key < node->data) {
            node->left = remove(node->left, key, found);
        } else if (key > node->data) {
            node->right = remove(node->right, key, found);
        } else {
            found = true;

            // Leaf node
            if (!node->left && !node->right) {
                lastCase = "leaf node";
                delete node;
                return nullptr;
            }

            // One child
            if (!node->left || !node->right) {
                lastCase = "node with one child";
                Node* child = node->left ? node->left : node->right;
                delete node;
                return child;
            }

            // Two children
            Node* successor = minNode(node->right);
            node->data = successor->data;
            bool dummy;
            node->right = remove(node->right, successor->data, dummy);
            lastCase = "node with two children";
        }
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

    bool remove(int key) {
        bool found = false;
        root = remove(root, key, found);
        if (found) cout << "Case: " << lastCase << " deleted.\n";
        return found;
    }

    void inorder() const {
        inorder(root);
        cout << endl;
    }
};

int main() {
    BST company;

    // Employee IDs
    int ids[] = {50, 30, 70, 20, 40, 60, 80};
    for (int id : ids) company.insert(id);

    cout << "Employee IDs: ";
    company.inorder();

    // Deletion loop
    char again;
    do {
        int key;
        cout << "\nEnter employee ID to delete: ";
        cin >> key;

        if (company.remove(key)) {
            cout << "Remaining IDs: ";
            company.inorder();
        } else {
            cout << "Employee ID " << key << " not found.\n";
        }

        cout << "Delete another? (y/n): ";
        cin >> again;
    } while (again == 'y' || again == 'Y');

    return 0;
}
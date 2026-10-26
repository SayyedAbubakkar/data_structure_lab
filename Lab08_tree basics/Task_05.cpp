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

    void inorder(Node* node) const {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void preorder(Node* node) const {
        if (!node) return;
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node) const {
        if (!node) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
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
    void inorder() const { inorder(root); cout << endl; }
    void preorder() const { preorder(root); cout << endl; }
    void postorder() const { postorder(root); cout << endl; }
};

int main() {
    BST hospital;

    // Patient IDs
    int ids[] = {40, 20, 60, 10, 30, 50, 70};
    for (int id : ids) hospital.insert(id);

    // Traversals
    cout << "In-order   (Left, Root, Right): ";
    hospital.inorder();
    cout << "Pre-order  (Root, Left, Right): ";
    hospital.preorder();
    cout << "Post-order (Left, Right, Root): ";
    hospital.postorder();

    cout << "\nIn-order traversal displays the IDs in ascending order.\n";
    return 0;
}
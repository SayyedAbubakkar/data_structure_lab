#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string name;
    Node* left;
    Node* right;

    Node(const string& n) : name(n), left(nullptr), right(nullptr) {}
};

void display(Node* root) {
    if (!root) return;
    cout << root->name
         << " | Left: " << (root->left ? root->left->name : "None")
         << " | Right: " << (root->right ? root->right->name : "None") << endl;
    display(root->left);
    display(root->right);
}

void destroy(Node* root) {
    if (!root) return;
    destroy(root->left);
    destroy(root->right);
    delete root;
}

int main() {
    // Build tree
    Node* root = new Node("Grandfather");
    root->left = new Node("Father");
    root->right = new Node("Uncle");
    root->left->left = new Node("Ali");
    root->left->right = new Node("Sara");
    root->right->left = new Node("Hamza");
    root->right->right = new Node("Ayesha");

    // Display
    cout << "Family Tree\n-----------\n";
    display(root);

    destroy(root);
    return 0;
}
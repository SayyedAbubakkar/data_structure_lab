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

    Node* insert(Node* node, int value, bool& inserted) {
        if (!node) {
            inserted = true;
            return new Node(value);
        }
        if (value < node->data) node->left = insert(node->left, value, inserted);
        else if (value > node->data) node->right = insert(node->right, value, inserted);
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
            if (!node->left || !node->right) {
                Node* child = node->left ? node->left : node->right;
                delete node;
                return child;
            }
            Node* successor = minNode(node->right);
            node->data = successor->data;
            bool dummy;
            node->right = remove(node->right, successor->data, dummy);
        }
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

    void insertProduct(int id) {
        bool inserted = false;
        root = insert(root, id, inserted);
        if (inserted) cout << "Product " << id << " inserted.\n";
        else cout << "Product " << id << " already exists. Duplicate not added.\n";
    }

    void searchProduct(int id) const {
        Node* current = root;
        while (current) {
            if (id == current->data) {
                cout << "Product " << id << " found.\n";
                return;
            }
            current = (id < current->data) ? current->left : current->right;
        }
        cout << "Product " << id << " not found.\n";
    }

    void deleteProduct(int id) {
        bool found = false;
        root = remove(root, id, found);
        if (found) cout << "Product " << id << " deleted.\n";
        else cout << "Product " << id << " not found. Nothing deleted.\n";
    }

    void displayInorder() const {
        if (!root) { cout << "Inventory is empty.\n"; return; }
        cout << "In-order: ";
        inorder(root);
        cout << endl;
    }

    void displayPreorder() const {
        if (!root) { cout << "Inventory is empty.\n"; return; }
        cout << "Pre-order: ";
        preorder(root);
        cout << endl;
    }

    void displayPostorder() const {
        if (!root) { cout << "Inventory is empty.\n"; return; }
        cout << "Post-order: ";
        postorder(root);
        cout << endl;
    }
};

int readId() {
    int id;
    cout << "Enter product ID: ";
    cin >> id;
    return id;
}

int main() {
    BST inventory;
    int choice;

    do {
        cout << "\n--- Online Store Inventory ---\n"
             << "1. Insert a product ID\n"
             << "2. Search for a product ID\n"
             << "3. Delete a product ID\n"
             << "4. Display in-order traversal\n"
             << "5. Display pre-order traversal\n"
             << "6. Display post-order traversal\n"
             << "7. Exit\n"
             << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            choice = 0;
        }

        switch (choice) {
            case 1: inventory.insertProduct(readId()); break;
            case 2: inventory.searchProduct(readId()); break;
            case 3: inventory.deleteProduct(readId()); break;
            case 4: inventory.displayInorder(); break;
            case 5: inventory.displayPreorder(); break;
            case 6: inventory.displayPostorder(); break;
            case 7: cout << "Exiting.\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 7);

    return 0;
}
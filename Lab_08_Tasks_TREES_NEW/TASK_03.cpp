
#include <iostream>
#include <string>
using namespace std;

class Node
{
public:
    string name;
    Node* left;
    Node* right;

    Node(string n)
    {
        name = n;
        left = NULL;
        right = NULL;
    }
};

void InOrder(Node* root)
{
    if (root == NULL)
        return;

    InOrder(root->left);
    cout << root->name << " ";
    InOrder(root->right);
}

void PreOrder(Node* root)
{
    if (root == NULL)
        return;

    cout << root->name << " ";
    PreOrder(root->left);
    PreOrder(root->right);
}

void PostOrder(Node* root)
{
    if (root == NULL)
        return;

    PostOrder(root->left);
    PostOrder(root->right);
    cout << root->name << " ";
}

int main()
{
    Node* root = new Node("C");

    root->left = new Node("Documents");
    root->right = new Node("Downloads");

    root->left->left = new Node("Assignments");
    root->left->right = new Node("Projects");

    root->right->left = new Node("Images");
    root->right->right = new Node("Videos");

    cout << "Computer File Explorer" << endl;

    cout << "\nIn-order Traversal: ";
    InOrder(root);

    cout << "\nPre-order Traversal: ";
    PreOrder(root);

    cout << "\nPost-order Traversal: ";
    PostOrder(root);

    return 0;
}

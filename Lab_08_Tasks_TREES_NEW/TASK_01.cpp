
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

int main()
{
    Node* root = new Node("HOD");

    root->left = new Node("Coordinator A");
    root->right = new Node("Coordinator B");

    root->left->left = new Node("Faculty A");
    root->left->right = new Node("Faculty B");

    root->right->left = new Node("Faculty C");
    root->right->right = new Node("Faculty D");

    cout << "University Department Hierarchy" << endl;
    cout << endl;

    cout << "Member: " << root->name << endl;
    cout << "Left Child: " << root->left->name << endl;
    cout << "Right Child: " << root->right->name << endl;
    cout << endl;

    cout << "Member: " << root->left->name << endl;
    cout << "Left Child: " << root->left->left->name << endl;
    cout << "Right Child: " << root->left->right->name << endl;
    cout << endl;

    cout << "Member: " << root->right->name << endl;
    cout << "Left Child: " << root->right->left->name << endl;
    cout << "Right Child: " << root->right->right->name << endl;
    cout << endl;

    cout << "Member: " << root->left->left->name << endl;
    cout << "Member: " << root->left->right->name << endl;
    cout << "Member: " << root->right->left->name << endl;
    cout << "Member: " << root->right->right->name << endl;

    return 0;
}

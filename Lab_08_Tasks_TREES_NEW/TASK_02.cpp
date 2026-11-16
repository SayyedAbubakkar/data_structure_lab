
#include <iostream>
#include <queue>
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

void BFS(Node* root)
{
    if (root == NULL)
        return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty())
    {
        Node* temp = q.front();
        q.pop();

        cout << temp->name << " ";

        if (temp->left != NULL)
            q.push(temp->left);

        if (temp->right != NULL)
            q.push(temp->right);
    }
}

int main()
{
    Node* root = new Node("Electronics");

    root->left = new Node("Clothing");
    root->right = new Node("Mobiles");

    root->left->left = new Node("Men");
    root->left->right = new Node("Women");

    root->right->left = new Node("Laptops");
    root->right->right = new Node("Accessories");

    cout << "Online Shopping Categories" << endl;
    cout << "BFS Traversal: ";

    BFS(root);

    return 0;
}

#include <iostream> 
#include <stack> 

// Write a program to illustrate operations on a BST holding
// numeric keys. The menu must include: • Insert • Mirror
// Image • Find • Post order (nonrecursive)

using namespace std;

struct Node { 
    int val = val;
    Node* right;
    Node* left; 

    Node(int value) {
        val = value;
        right = nullptr;
        left = nullptr;
    }
};

void postOrder(Node* root) { 
    if(!root) return; 

    stack<Node*> s1;
    stack<Node*> s2;

    s1.push(root); 

    while(!s1.empty()) { 
        Node* current = s1.top();
        s1.pop(); 
        s2.push(current); 

        if(current->left) s1.push(current->left); 
        if(current->right) s1.push(current->right); 
    }

    while(!s2.empty()) { 
        cout << s2.top()->val << " "; 
        s2.pop(); 
    }
}

int main() { 

    // Creating a sample BST:
    //        50
    //      /    \
    //     30     70
    //    /  \   /  \
    //   20  40 60  80

    Node* root = new Node(50);
    root->left = new Node(30);
    root->right = new Node(70);
    root->left->left = new Node(20);
    root->left->right = new Node(40);
    root->right->left = new Node(60);
    root->right->right = new Node(80);

    cout << "Post-order traversal: ";
    postOrder(root);
    
    return 0;

}
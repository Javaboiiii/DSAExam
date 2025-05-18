#include <iostream>
#include <queue> 
using namespace std; 

// Write a Program to create a Binary Search Tree and
// perform following nonrecursive operations on it. a.
// Preorder Traversal b. Postorder Traversal c. Display total
// Number of Nodes d. Display Leaf nodes.

struct Node{ 
    int val; 
    Node* left; 
    Node* right;

    Node(int v) { 
        val = v; 
        left = nullptr;
        right = nullptr; 
    }
};

void displayLeaf(Node* root) { 
    if(!root) return ; 

    queue<Node*> q; 
    q.push(root); 

    while(!q.empty()) { 
        int size = q.size(); 
        for(int i = 0; i < size; i ++) { 
            Node* node = q.front(); 
            q.pop(); 
            if(!node->left && !node->right) {
                cout << node->val << " ";
                continue; 
            } 
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right); 
        }
    }
}

int main() { 
    // Create a sample BST:
    //        50
    //      /    \
    //     30     70
    //    /  \   /  \
    //   20  40 60  80
    //  /        \
    // 10        65

    Node* root = new Node(50);
    root->left = new Node(30);
    root->right = new Node(70);
    root->left->left = new Node(20);
    root->left->right = new Node(40);
    root->right->left = new Node(60);
    root->right->right = new Node(80);
    root->left->left->left = new Node(10);
    root->right->left->right = new Node(65);

    cout << "Leaf nodes: ";
    displayLeaf(root);
    // Expected output: Leaf nodes: 10 40 65 80
    
    return 0;
}
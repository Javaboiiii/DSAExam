#include <iostream>
#include <queue> 

// Write a Program to create a Binary Search Tree holding
// numeric keys and perform following nonrecursive
// operations on it. a. Levelwise display, b. Mirror image, c.
// Display height of a tree.

using namespace std; 

struct  Node{
    int val; 
    Node* left; 
    Node* right; 
};


void levelWiseDisplay(Node* root) { 
    if(!root) return ; 

    queue<Node*> q; 
    q.push(root); 

    while(!q.empty()) { 
        int count = q.size(); 
        for(int i = 0; i < count; i ++) { 
            Node* node = q.front();  
            q.pop(); 
            cout << node->val << " "; 
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right); 
        }
        cout << endl; 
    }
}

void inorder(Node* root) { 
    if(!root) return ; 

    if(root->left) inorder(root->left); 
    cout << root->val << " "; 
    if(root->right) inorder(root->right); 
}

Node* mirror(Node* root) { 
    if(!root) return nullptr; 

    queue<Node*> q; 

    q.push(root); 

    while(!q.empty()) { 
        int count = q.size(); 

        for(int i = 0; i < count; i ++ ) { 
            Node* node = q.front(); 
            q.pop(); 
            Node* right = node->right;
            Node* left = node->left;
            node->left = right;
            node->right = left; 
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right); 
        }
    }

    return root; 
}

int main() { 
    // Create a sample Binary Search Tree
    //       50
    //      /  \
    //    30    70
    //   /  \   / \
    //  20  40 60  80

    Node* root = new Node{50, nullptr, nullptr};
    
    root->left = new Node{30, nullptr, nullptr};
    root->left->left = new Node{20, nullptr, nullptr};
    root->left->right = new Node{40, nullptr, nullptr};
    
    root->right = new Node{70, nullptr, nullptr};
    root->right->left = new Node{60, nullptr, nullptr};
    root->right->right = new Node{80, nullptr, nullptr};
    
    cout << "Levelwise display of BST:" << endl;
    levelWiseDisplay(root);
    
    cout << "\nInorder traversal before mirroring: ";
    inorder(root);
    cout << endl;
    
    root = mirror(root);
    cout << "\nAfter mirroring the BST:" << endl;
    levelWiseDisplay(root);
    
    cout << "\nInorder traversal after mirroring: ";
    inorder(root);
    cout << endl;
    
    return 0;
}
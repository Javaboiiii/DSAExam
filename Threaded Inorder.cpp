// Write a Program to create Inorder Threaded Binary Tree and Traverse it in
//  Preorder way.

#include <iostream> 

using namespace std; 

struct Node { 
    int val; 
    Node* left; 
    Node* right; 
    bool isThreaded; 

    Node(int v) { 
        val = v; 
        left = nullptr;
        right = nullptr; 
        isThreaded = false; 
    }
}; 

void preOrder(Node* root) { 
    Node* curr = root; 

    while(curr) {  
        cout << curr->val << " "; 

        if(curr->left) curr = curr->left; 
        else { 
            while(curr && curr->isThreaded){ 
                curr = curr->right; 
            }

            if(curr) curr = curr->right; 
        }
    }
}

void createThread(Node* root, Node*& prev) { 
    if(!root) return ; 
    
    createThread(root->left, prev); 

    if(prev && !prev->right) { 
        prev->right = root; 
        prev->isThreaded = true; 
    }

    prev = root; 

    createThread(root->right, prev); 

}

int main() {
    // Create a sample binary tree
    Node* root = new Node(20);
    root->left = new Node(10);
    root->right = new Node(30);
    root->left->left = new Node(5);
    root->left->right = new Node(15);

    // Create threads for the tree
    Node* prev = nullptr;
    createThread(root, prev);

    // Traverse the tree in Preorder
    cout << "Preorder Traversal of Threaded Binary Tree: ";
    preOrder(root);

    return 0;
}
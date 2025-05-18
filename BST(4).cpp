#include <iostream> 

// Write a Program to create a Binary Search Tree and
// perform deletion of a node from it. Also display the tree in
// nonrecursive postorder way.

using namespace std; 

struct Node { 
    int val; 
    Node* right; 
    Node* left; 

    Node(int v) { 
        val = v; 
        right = nullptr;
        left = nullptr;
    }
}; 

Node* rightMost(Node* root) { 
    while(root->right) { 
        root=root->right; 
    }

    return root;
}

Node* helper(Node* root) { 
    if(!root->left) return root->right; 
    if(!root->right) return root->left; 

    Node* left = root->left; 

    Node* rightNode = root->right; 
    Node* leftRightMost = rightMost(root->left);   
    leftRightMost->right = rightNode; 

    delete root; 

    return left; 
}


Node* deleteNode(Node* root, int val) { 
    if(!root) return nullptr; 

    Node* dummyNode = root; 

    while(root) { 
        if(val < root->val) { 
            if(root->left && root->left->val == val ) { 
                root->left = helper(root->left); 
                break; 
            }else { 
                root = root->left; 
            }
        }else { 
            if(root->right && root->right->val == val) { 
                root->right = helper(root->right); 
                break; 
            }else { 
                root = root->right; 
            }
        }
    }




    return dummyNode; 
}


void inOrder(Node* root) { 
    if(!root) return ; 

    if(root->left) inOrder(root->left);
    cout << root->val << " "; 
    if(root->right) inOrder(root->right); 
}

int main() {
    // Create a sample BST
    //        50
    //       /  \
    //      30   70
    //     /  \  / \
    //    20  40 60 80

    // Create the BST using the constructor properly
    Node* root = new Node(50);
    
    root->left = new Node(30);
    root->right = new Node(70);
    
    root->left->left = new Node(20);
    root->left->right = new Node(40);
    
    root->right->left = new Node(60);
    root->right->right = new Node(80);
    
    cout << "Original tree (inorder): ";
    inOrder(root);
    cout << endl;
    
    root = deleteNode(root, 20);
    cout << "After deleting 20 (inorder): ";
    inOrder(root);
    cout << endl;
    
    root = deleteNode(root, 30);
    cout << "After deleting 30 (inorder): ";
    inOrder(root);
    cout << endl;

    root = deleteNode(root, 50);
    cout << "After deleting 50 (inorder): ";
    inOrder(root);
    cout << endl;
    
    return 0;
    
}
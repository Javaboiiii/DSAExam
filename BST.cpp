#include <iostream>

// Write a program to illustrate operations on a BST holding
// numeric keys. The menu must include: • Insert • Delete •
// Find • display in Inorder way

using namespace std; 

struct Node { 
    int val; 
    Node* left;
    Node* right; 

    Node(int v){
        val = v; 
        left = nullptr;
        right = nullptr;
    }
}; 

Node* findNode(Node* root, int val) { 

    if(!root) return nullptr; 

    if(root->val < val) 
        return findNode(root->right, val); 
    else if(root->val > val) 
        return findNode(root->left, val); 
    else 
        return root; 

}

Node* deleteNode(Node* root, int val) {  
    if(!root) return nullptr; 
    
    if(val < root->val) 
        root->left = deleteNode(root->left, val); 
    else if(val > root->val) 
        root->right = deleteNode(root->right, val); 
    else { 
        // leafNode 
        if(!root->right && !root->left) {
            delete root; 
            return nullptr; 
        }

        // left is not null 
        if(!root->right){ 
            Node* temp = root->left; 
            delete root;
            return temp; 
        }
        
        // right is not null
        if(!root->left){ 
            Node* temp = root->right; 
            delete root;
            return temp; 
        }

        // Both are not null 
        else { 
            // find right most node of the left subtree 
            Node* right = root->right; 
            Node* curr = root->left; 
            while(curr->right) { 
                curr=curr->right; 
            }
            curr->right = right; 
            root->right = nullptr;
            Node* left = root->left; 
            delete root; 
            return left; 

        }

    }

    return root; 
}

Node* insert(Node* root, int val) { 
    if(!root) return new Node(val);  

    Node* curr = root; 

    while(true) { 
        if(val > curr->val) {
            if(!curr->right) { 
                curr->right = new Node(val); 
                break; 
            }
            curr = curr->right; 
        }  
        else {
            if(!curr->left) { 
                curr->left = new Node(val);  
                break; 
            }
            curr = curr->left; 
        } 
    }

    return root; 
    
}

void displayInorder(Node* root) {
    if (!root) return;
    
    if (root->left) displayInorder(root->left);
    cout << root->val << " ";
    if (root->right) displayInorder(root->right);
}

int main() {
    Node* root = new Node(50);
    
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);
    
    cout << "Inorder traversal of the BST: ";
    displayInorder(root);
    cout << endl;
    
    int findValue = 40;
    Node* found = findNode(root, findValue);
    if (found)
        cout << "Found value " << findValue << " in the BST." << endl;
    else
        cout << "Value " << findValue << " not found in the BST." << endl;
    
    int deleteValue = 30;
    cout << "Deleting node with value " << deleteValue << endl;
    root = deleteNode(root, deleteValue);
    
    cout << "Inorder traversal after deletion: ";
    displayInorder(root);
    cout << endl;
    
    return 0;
}

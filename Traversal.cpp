#include <iostream>
#include <queue>
// Write a Program to create a Binary Tree and perform
// following nonrecursive operations on it. a. Preorder
// Traversal, b. Postorder Traversal, c. Count total no. of
// nodes, d. Display height of a tree.

using namespace std; 

struct Node { 
    int val; 
    Node* left; 
    Node* right; 
};

int getHeight(Node* root) { 
    queue<Node*> q; 
    if(!root) { 
        cout << "Null root" << endl; 
        return -1; 
    }

    int height = 0; 

    q.push(root);
    
    while(!q.empty()) { 
        int count = q.size();  
        height ++; 
        for(int i = 0; i < count; i++) { 
            Node* node = q.front(); 
            q.pop(); 
            if(node->left) q.push(node->left); 
            if(node->right) q.push(node->right);  
        }
    }

    return height; 

}

int preOrder(Node* root, int& count) {   
    if(!root) { 
        cout << "Null root" << endl; 
        return -1; 
    }

    count ++; 

    cout << root->val << " "; 
    if(root->left) preOrder(root->left, count); 
    if(root->right) preOrder(root->right, count); 


    return count; 
    
}

void postOrder(Node* root) { 
    if(!root) { 
        cout << "Null root" << endl; 
        return ; 
    }

    if(root->left) postOrder(root->left); 
    if(root->right) postOrder(root->right); 
    cout << root->val << " "; 

}

int main() {
    // Create a sample binary tree
    //        1
    //       / \
    //      2   3
    //     / \   \
    //    4   5   6
    //       /
    //      7
    
    Node* root = new Node{1, nullptr, nullptr};
    root->left = new Node{2, nullptr, nullptr};
    root->right = new Node{3, nullptr, nullptr};
    root->left->left = new Node{4, nullptr, nullptr};
    root->left->right = new Node{5, nullptr, nullptr};
    root->right->right = new Node{6, nullptr, nullptr};
    root->left->right->left = new Node{7, nullptr, nullptr};
    
    cout << "Height of the tree: " << getHeight(root) << endl;
    
    int count = 0;
    cout << "Preorder traversal: ";
    count = preOrder(root, count);
    cout << "\nTotal number of nodes: " << count << endl;
    
    cout << "Postorder traversal: ";
    postOrder(root);
    cout << endl;
    
    return 0;
}
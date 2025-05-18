#include <iostream>
#include <queue> 
// Write a Program to create a Binary Tree and perform
// following nonrecursive operations on it. a. inorder
// Traversal; b. Count no. of nodes on longest path; c.
// display tree levelwise; d. Display height of a tree.

using namespace std; 

struct Node { 
    int val; 
    Node* left; 
    Node* right; 
}; 

int LongestPath(Node* root, int depth) { 
    if(!root) return depth;  

    int lh = LongestPath(root->left, depth + 1); 
    int rh = LongestPath(root->right, depth + 1); 

    return max(lh, rh); 
}

void inOrder(Node* root) { 
    if(!root) return ; 

    if(root->left) inOrder(root->left);
    cout << root->val << " "; 
    if(root->right) inOrder(root->right);
}

int displayLevelWise(Node* root) { 

    if(!root) return -1; 

    queue<Node*> q; 

    q.push(root); 

    int height = 0; 

    while(!q.empty()) { 
        int count = q.size(); 
        height ++; 
        for(int i = 0; i < count; i ++) { 
            Node* node = q.front(); 
            cout << node->val << " "; 
            q.pop(); 
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right); 
        }

        cout << endl; 
    }

    return height; 
}

int main() {
    //        1
    //       / \
    //      2   3
    //     / \   \
    //    4   5   6
    //       /     \
    //      7       8
    
    Node* root = new Node{1, nullptr, nullptr};
    root->left = new Node{2, nullptr, nullptr};
    root->right = new Node{3, nullptr, nullptr};
    root->left->left = new Node{4, nullptr, nullptr};
    root->left->right = new Node{5, nullptr, nullptr};
    root->right->right = new Node{6, nullptr, nullptr};
    root->left->right->left = new Node{7, nullptr, nullptr};
    root->right->right->right = new Node{8, nullptr, nullptr};
    
    cout << "Level-wise traversal of tree:" << endl;
    int height = displayLevelWise(root);
    cout << "Height of the tree: " << height << endl;
    
    cout << "Inorder traversal: ";
    inOrder(root);
    cout << endl;

    cout << "Longest depth is : " << LongestPath(root, 0) << endl; 
    
    return 0;
}
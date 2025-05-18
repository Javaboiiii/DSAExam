#include <iostream> 
#include <queue> 

// Write a Program to create a Binary Search Tree and display its mirror
//  image with and without disturbing the original tree. Also display height of 
//  a tree using nonrecursion.

using namespace std; 

struct Node { 
    int val; 
    Node* left ; 
    Node* right; 

    Node(int v) { 
        val = v; 
        right = nullptr; 
        left = nullptr; 
    }
};

void printMirror(Node* root) { 
   if(!root)  return ; 

   queue<Node*> q; 
   q.push(root); 

   while(!q.empty()) { 
    int size = q.size(); 

    for(int i = 0; i < size; i ++) { 
        Node* node = q.front(); 
        q.pop(); 
        cout << node->val << " "; 
        if(node->right) q.push(node->right); 
        if(node->left) q.push(node->left); 
    }
    cout << endl; 
   }
}


int main() { 

    Node* root = new Node(50);
    root->left = new Node(30);
    root->right = new Node(70);
    root->left->left = new Node(20);
    root->left->right = new Node(40);
    root->right->left = new Node(60);
    root->right->right = new Node(80);

    printMirror(root); 

    return 0;

}

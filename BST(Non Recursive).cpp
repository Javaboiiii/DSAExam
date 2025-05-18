#include <iostream> 
#include <stack> 
// Write a Program to create a Binary Search Tree and
// perform following nonrecursive operations on it. a.
// Preorder Traversal b. Inorder Traversal c. Display Number
// of Leaf Nodes d. Mirror Image

using namespace std; 

struct Node { 
    int val; 
    Node* right;
    Node* left; 

    Node(int v) { 
        val = v ;
        left = nullptr; 
        right = nullptr; 
    }
}; 

void preOrder(Node* root) { 
    if(!root) return ; 

    stack<Node*> st; 

    st.push(root);

    while(!st.empty()) { 
        Node* curr = st.top();
        st.pop();
        cout << curr->val << " "; 
        if(curr->left) st.push(curr->left);
        if(curr->right) st.push(curr->right); 
    }
    
}

void inOrder(Node* root) { 
    if(!root) return ; 
    
    stack<Node*> st; 
    
    Node* curr = root ;
    
    while(curr != nullptr || !st.empty()) { 
        while(curr != nullptr){ 
            st.push(curr);
            curr = curr->left; 
        }
        curr = st.top(); 
        cout << curr->val << " " ; 
        st.pop(); 
        curr = curr->right; 
    }
    
}

int main() { 
    // Create a sample BST:
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

    cout << "Pre-order traversal: ";
    preOrder(root);
    cout << endl;

    cout << "In-order traversal: ";
    inOrder(root);
    cout << endl;
    
    return 0;
}

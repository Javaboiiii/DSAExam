// 38.	Write a Program to create Inorder Threaded Binary Tree and Traverse it in Postorder way.

#include <iostream>
#include <stack>

using namespace std;

// Node structure for inorder threaded binary tree
struct Node {
    int data;           // Node value
    Node* left;         // Pointer to left child
    Node* right;        // Pointer to right child
    bool isThreaded;    // Flag to indicate if right pointer is a thread
    
    // Constructor
    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
        isThreaded = false;
    }
};

// Class to manage Inorder Threaded Binary Tree operations
class InorderThreadedBinaryTree {
private:
    Node* root;
    
public:
    // Constructor
    InorderThreadedBinaryTree() : root(nullptr) {}
    
    // Create a new node
    Node* createNode(int val) {
        return new Node(val);
    }
    
    // Get root of the tree
    Node* getRoot() {
        return root;
    }
    
    // Set root of the tree
    void setRoot(Node* node) {
        root = node;
    }
    
    // Create threads in the binary tree (inorder threading)
    void createThreads() {
        Node* prev = nullptr;
        createInorderThreads(root, prev);
    }
    
    // Helper function to create inorder threads
    void createInorderThreads(Node* current, Node*& prev) {
        if (current == nullptr) {
            return;
        }
        
        // First process left subtree
        createInorderThreads(current->left, prev);
        
        // Process current node - create thread from previous node
        if (prev != nullptr && prev->right == nullptr) {
            prev->right = current;  // Thread creation
            prev->isThreaded = true;
        }
        
        // Update prev to current node
        prev = current;
        
        // Process right subtree only if not threaded
        if (!current->isThreaded) {
            createInorderThreads(current->right, prev);
        }
    }
    
    // Function to perform postorder traversal on inorder threaded binary tree
    void postorderTraversal() {
        if (root == nullptr) {
            cout << "Tree is empty." << endl;
            return;
        }
        
        cout << "Postorder Traversal: ";
        // Postorder traversal using two stacks
        postorderTraversalImpl(root);
        cout << endl;
    }
    
    // Helper function for postorder traversal on threaded tree
    void postorderTraversalImpl(Node* root) {
        if (root == nullptr) {
            return;
        }
        
        // We'll use two stacks for postorder traversal
        stack<Node*> stack1;
        stack<Node*> stack2;
        
        // Push root to first stack
        stack1.push(root);
        
        // Process all nodes and build the second stack
        while (!stack1.empty()) {
            // Pop from stack1 and push to stack2
            Node* temp = stack1.top();
            stack1.pop();
            stack2.push(temp);
            
            // Push left child to stack1 if exists
            if (temp->left) {
                stack1.push(temp->left);
            }
            
            // Push right child to stack1 if exists and not a thread
            if (temp->right && !temp->isThreaded) {
                stack1.push(temp->right);
            }
        }
        
        // Print all elements from stack2 (will be in postorder)
        while (!stack2.empty()) {
            cout << stack2.top()->data << " ";
            stack2.pop();
        }
    }
    
    // Insert a node into the binary search tree (no threading yet)
    void insert(int val) {
        root = insertNode(root, val);
    }
    
    // Helper function to insert a node into BST
    Node* insertNode(Node* node, int val) {
        // Base case: empty tree or reached leaf node
        if (node == nullptr) {
            return createNode(val);
        }
        
        // If value is less than node's data, insert in left subtree
        if (val < node->data) {
            node->left = insertNode(node->left, val);
        } 
        // If value is greater than node's data, insert in right subtree
        else if (val > node->data) {
            // Check if current node has a threaded right pointer
            if (node->isThreaded) {
                Node* temp = createNode(val);
                temp->right = node->right;
                temp->isThreaded = true;
                node->right = temp;
                node->isThreaded = false;
            } else {
                node->right = insertNode(node->right, val);
            }
        }
        // Duplicate values are not allowed
        
        return node;
    }
    
    // Free memory by deleting all nodes in the tree
    void deleteTree() {
        deleteTreeNodes(root);
        root = nullptr;
    }
    
    // Helper function to delete all nodes
    void deleteTreeNodes(Node* node) {
        if (node == nullptr) {
            return;
        }
        
        // First delete left subtree
        deleteTreeNodes(node->left);
        
        // Store right child
        Node* right = node->isThreaded ? nullptr : node->right;
        
        // Delete current node
        delete node;
        
        // Delete right subtree
        deleteTreeNodes(right);
    }
    
    // Display inorder traversal of the threaded tree
    void inorderTraversal() {
        if (root == nullptr) {
            cout << "Tree is empty." << endl;
            return;
        }
        
        cout << "Inorder Traversal: ";
        
        // Start from leftmost node
        Node* current = root;
        while (current->left != nullptr) {
            current = current->left;
        }
        
        // Traverse the tree using threads
        while (current != nullptr) {
            cout << current->data << " ";
            
            // If right pointer is a thread, follow it
            if (current->isThreaded) {
                current = current->right;
            } else {
                // Otherwise, move to the leftmost node in the right subtree
                current = current->right;
                
                if (current != nullptr) {
                    while (current->left != nullptr) {
                        current = current->left;
                    }
                }
            }
        }
        
        cout << endl;
    }
};

int main() {
    InorderThreadedBinaryTree tree;
    
    cout << "=== Inorder Threaded Binary Tree with Postorder Traversal ===" << endl;
    
    // Create a sample tree
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);
    
    // Create threads in the tree
    tree.createThreads();
    
    // Display inorder traversal of the tree
    tree.inorderTraversal();
    
    // Display postorder traversal of the tree
    tree.postorderTraversal();
    
    // Interactive menu for user operations
    char choice;
    int value;
    
    do {
        cout << "\nMenu:" << endl;
        cout << "1. Insert a node" << endl;
        cout << "2. Inorder traversal" << endl;
        cout << "3. Postorder traversal" << endl;
        cout << "q. Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case '1':
                cout << "Enter value to insert: ";
                cin >> value;
                tree.insert(value);
                // Recreate threads after each insertion
                tree.createThreads();
                cout << value << " inserted." << endl;
                break;
                
            case '2':
                tree.inorderTraversal();
                break;
                
            case '3':
                tree.postorderTraversal();
                break;
                
            case 'q':
            case 'Q':
                cout << "Exiting program..." << endl;
                break;
                
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 'q' && choice != 'Q');
    
    // Clean up memory
    tree.deleteTree();
    
    return 0;
}
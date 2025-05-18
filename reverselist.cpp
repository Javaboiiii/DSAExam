// Write an iterative / noniterative Reverse() function that reverses a list by rearranging all
//  the next pointers and the head pointer. Ideally, Reverse() should only need to make one pass/scan of the list.

#include <iostream>
using namespace std;

// Node structure for singly linked list
struct Node {
    int data;       // Data value
    Node* next;     // Pointer to next node
    
    // Constructor
    Node(int val) : data(val), next(nullptr) {}
};

// Function to insert a node at the end of the list
void insertAtEnd(Node*& head, int val) {
    Node* newNode = new Node(val);
    
    if (head == nullptr) {
        head = newNode;
        return;
    }
    
    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Function to display a linked list
void displayList(Node* head) {
    if (head == nullptr) {
        cout << "Empty List" << endl;
        return;
    }
    
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data;
        if (temp->next != nullptr) {
            cout << " -> ";
        }
        temp = temp->next;
    }
    cout << endl;
}

// Iterative function to reverse a linked list
// Makes only one pass through the list
Node* reverseIterative(Node* head) {
    // If list is empty or has only one node
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    
    Node* prev = nullptr;  // Previous node (starts as nullptr)
    Node* current = head;  // Current node (starts as head)
    Node* next = nullptr;  // Next node
    
    // Traverse the list, reversing next pointers
    while (current != nullptr) {
        // Store next node
        next = current->next;
        
        // Reverse the next pointer of current node
        current->next = prev;
        
        // Move prev and current one step forward
        prev = current;
        current = next;
    }
    
    // prev is the new head of the reversed list
    return prev;
}

// Recursive function to reverse a linked list
Node* reverseRecursive(Node* head) {
    // Base case: If list is empty or has only one node
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    
    // Recursive call: Reverse the rest of the list
    Node* rest = reverseRecursive(head->next);
    
    // Fix the next pointer of the node after head
    head->next->next = head;
    
    // Set head's next to nullptr (will be the last node)
    head->next = nullptr;
    
    // Return the new head (which was originally the last node)
    return rest;
}

// Function to free memory allocated for the linked list
void deleteList(Node*& head) {
    Node* current = head;
    Node* next;
    
    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }
    
    head = nullptr;
}

int main() {
    Node* head = nullptr;
    int choice, val;
    
    cout << "=== Linked List Reversal Program ===" << endl;
    
    // Create a linked list
    cout << "\nEnter elements for the linked list (enter -1 to stop): " << endl;
    while (true) {
        cin >> val;
        if (val == -1) break;
        insertAtEnd(head, val);
    }
    
    // Display original list
    cout << "\nOriginal Linked List: ";
    displayList(head);
    
    // Menu for reversal methods
    cout << "\nChoose reversal method:" << endl;
    cout << "1. Iterative Reversal" << endl;
    cout << "2. Recursive Reversal" << endl;
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;
    
    // Create a copy of the list for demonstration purposes
    Node* iterativeHead = nullptr;
    Node* recursiveHead = nullptr;
    
    // Copy the original list
    Node* temp = head;
    while (temp != nullptr) {
        insertAtEnd(iterativeHead, temp->data);
        insertAtEnd(recursiveHead, temp->data);
        temp = temp->next;
    }
    
    // Perform selected reversal method
    if (choice == 1) {
        // Iterative reversal
        cout << "\nUsing Iterative Reversal:" << endl;
        cout << "Before: ";
        displayList(iterativeHead);
        
        iterativeHead = reverseIterative(iterativeHead);
        
        cout << "After:  ";
        displayList(iterativeHead);
        
        // Also demonstrate recursive method
        cout << "\nFor comparison, Recursive Reversal:" << endl;
        cout << "Before: ";
        displayList(recursiveHead);
        
        recursiveHead = reverseRecursive(recursiveHead);
        
        cout << "After:  ";
        displayList(recursiveHead);
    } else if (choice == 2) {
        // Recursive reversal
        cout << "\nUsing Recursive Reversal:" << endl;
        cout << "Before: ";
        displayList(recursiveHead);
        
        recursiveHead = reverseRecursive(recursiveHead);
        
        cout << "After:  ";
        displayList(recursiveHead);
        
        // Also demonstrate iterative method
        cout << "\nFor comparison, Iterative Reversal:" << endl;
        cout << "Before: ";
        displayList(iterativeHead);
        
        iterativeHead = reverseIterative(iterativeHead);
        
        cout << "After:  ";
        displayList(iterativeHead);
    } else {
        cout << "Invalid choice!" << endl;
    }
    
    // Clean up memory
    deleteList(head);
    deleteList(iterativeHead);
    deleteList(recursiveHead);
    
    return 0;
}
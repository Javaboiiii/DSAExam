// WAP to create doubly linked list and perform following operations on it. A) Insert (all cases) 2. Delete (all cases).

#include <iostream>
using namespace std;

// Node structure for doubly linked list
struct Node {
    int data;       // Data value
    Node* prev;     // Pointer to previous node
    Node* next;     // Pointer to next node
    
    // Constructor
    Node(int val) : data(val), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
private:
    Node* head;     // Pointer to the first node
    Node* tail;     // Pointer to the last node
    int size;       // Number of nodes in the list
    
public:
    // Constructor
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    
    // Destructor
    ~DoublyLinkedList() {
        // Delete all nodes to prevent memory leaks
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        head = tail = nullptr;
        size = 0;
    }
    
    // Get the size of the list
    int getSize() {
        return size;
    }
    
    // Check if the list is empty
    bool isEmpty() {
        return size == 0;
    }
    
    // ==== INSERTION OPERATIONS ====
    
    // 1. Insert at the beginning
    void insertAtBeginning(int val) {
        Node* newNode = new Node(val);
        
        if (isEmpty()) {
            // List is empty
            head = tail = newNode;
        } else {
            // List has at least one node
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        
        size++;
        cout << val << " inserted at the beginning." << endl;
    }
    
    // 2. Insert at the end
    void insertAtEnd(int val) {
        Node* newNode = new Node(val);
        
        if (isEmpty()) {
            // List is empty
            head = tail = newNode;
        } else {
            // List has at least one node
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        
        size++;
        cout << val << " inserted at the end." << endl;
    }
    
    // 3. Insert after a specific node (by value)
    bool insertAfterValue(int key, int val) {
        if (isEmpty()) {
            cout << "List is empty. Cannot insert after a value." << endl;
            return false;
        }
        
        Node* current = head;
        // Find the node with value 'key'
        while (current != nullptr && current->data != key) {
            current = current->next;
        }
        
        if (current == nullptr) {
            cout << key << " not found in the list." << endl;
            return false;
        }
        
        // Check if we're inserting after the tail
        if (current == tail) {
            insertAtEnd(val);
            return true;
        }
        
        // Insert between current and current->next
        Node* newNode = new Node(val);
        newNode->prev = current;
        newNode->next = current->next;
        current->next->prev = newNode;
        current->next = newNode;
        
        size++;
        cout << val << " inserted after " << key << "." << endl;
        return true;
    }
    
    // 4. Insert before a specific node (by value)
    bool insertBeforeValue(int key, int val) {
        if (isEmpty()) {
            cout << "List is empty. Cannot insert before a value." << endl;
            return false;
        }
        
        Node* current = head;
        // Find the node with value 'key'
        while (current != nullptr && current->data != key) {
            current = current->next;
        }
        
        if (current == nullptr) {
            cout << key << " not found in the list." << endl;
            return false;
        }
        
        // Check if we're inserting before the head
        if (current == head) {
            insertAtBeginning(val);
            return true;
        }
        
        // Insert between current->prev and current
        Node* newNode = new Node(val);
        newNode->next = current;
        newNode->prev = current->prev;
        current->prev->next = newNode;
        current->prev = newNode;
        
        size++;
        cout << val << " inserted before " << key << "." << endl;
        return true;
    }
    
    // 5. Insert at a specific position (0-based index)
    bool insertAtPosition(int pos, int val) {
        // Check for valid position
        if (pos < 0 || pos > size) {
            cout << "Invalid position. Valid range is 0 to " << size << "." << endl;
            return false;
        }
        
        // Insert at the beginning
        if (pos == 0) {
            insertAtBeginning(val);
            return true;
        }
        
        // Insert at the end
        if (pos == size) {
            insertAtEnd(val);
            return true;
        }
        
        // Insert at position in the middle
        Node* current = head;
        for (int i = 0; i < pos; i++) {
            current = current->next;
        }
        
        // Now current is at the position where we want to insert
        Node* newNode = new Node(val);
        newNode->next = current;
        newNode->prev = current->prev;
        current->prev->next = newNode;
        current->prev = newNode;
        
        size++;
        cout << val << " inserted at position " << pos << "." << endl;
        return true;
    }
    
    // ==== DELETION OPERATIONS ====
    
    // 1. Delete from the beginning
    bool deleteFromBeginning() {
        if (isEmpty()) {
            cout << "List is empty. Cannot delete." << endl;
            return false;
        }
        
        Node* temp = head;
        
        // If only one node exists
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        
        int deletedValue = temp->data;
        delete temp;
        size--;
        
        cout << deletedValue << " deleted from the beginning." << endl;
        return true;
    }
    
    // 2. Delete from the end
    bool deleteFromEnd() {
        if (isEmpty()) {
            cout << "List is empty. Cannot delete." << endl;
            return false;
        }
        
        Node* temp = tail;
        
        // If only one node exists
        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        
        int deletedValue = temp->data;
        delete temp;
        size--;
        
        cout << deletedValue << " deleted from the end." << endl;
        return true;
    }
    
    // 3. Delete a specific node (by value)
    bool deleteByValue(int val) {
        if (isEmpty()) {
            cout << "List is empty. Cannot delete." << endl;
            return false;
        }
        
        // If the value is at the head
        if (head->data == val) {
            return deleteFromBeginning();
        }
        
        // If the value is at the tail
        if (tail->data == val) {
            return deleteFromEnd();
        }
        
        // Search for the node with the value
        Node* current = head->next;
        while (current != nullptr && current->data != val) {
            current = current->next;
        }
        
        if (current == nullptr) {
            cout << val << " not found in the list." << endl;
            return false;
        }
        
        // Remove the node from the list
        current->prev->next = current->next;
        current->next->prev = current->prev;
        
        delete current;
        size--;
        
        cout << val << " deleted from the list." << endl;
        return true;
    }
    
    // 4. Delete a node at a specific position (0-based index)
    bool deleteAtPosition(int pos) {
        // Check for valid position
        if (pos < 0 || pos >= size) {
            cout << "Invalid position. Valid range is 0 to " << size - 1 << "." << endl;
            return false;
        }
        
        // Delete from the beginning
        if (pos == 0) {
            return deleteFromBeginning();
        }
        
        // Delete from the end
        if (pos == size - 1) {
            return deleteFromEnd();
        }
        
        // Delete from the middle
        Node* current = head;
        for (int i = 0; i < pos; i++) {
            current = current->next;
        }
        
        current->prev->next = current->next;
        current->next->prev = current->prev;
        
        int deletedValue = current->data;
        delete current;
        size--;
        
        cout << deletedValue << " deleted from position " << pos << "." << endl;
        return true;
    }
    
    // Display the list from head to tail
    void displayForward() {
        if (isEmpty()) {
            cout << "List is empty." << endl;
            return;
        }
        
        Node* current = head;
        cout << "List (forward): ";
        while (current != nullptr) {
            cout << current->data;
            if (current->next != nullptr) {
                cout << " <-> ";
            }
            current = current->next;
        }
        cout << " [Size: " << size << "]" << endl;
    }
    
    // Display the list from tail to head
    void displayBackward() {
        if (isEmpty()) {
            cout << "List is empty." << endl;
            return;
        }
        
        Node* current = tail;
        cout << "List (backward): ";
        while (current != nullptr) {
            cout << current->data;
            if (current->prev != nullptr) {
                cout << " <-> ";
            }
            current = current->prev;
        }
        cout << " [Size: " << size << "]" << endl;
    }
};

int main() {
    DoublyLinkedList dll;
    int choice, value, position, key;
    
    cout << "=== Doubly Linked List Operations ===" << endl;
    
    do {
        cout << "\nMenu:" << endl;
        cout << "1. Insert at the beginning" << endl;
        cout << "2. Insert at the end" << endl;
        cout << "3. Insert after a specific value" << endl;
        cout << "4. Insert before a specific value" << endl;
        cout << "5. Insert at a specific position" << endl;
        cout << "6. Delete from the beginning" << endl;
        cout << "7. Delete from the end" << endl;
        cout << "8. Delete a specific value" << endl;
        cout << "9. Delete at a specific position" << endl;
        cout << "10. Display list (forward)" << endl;
        cout << "11. Display list (backward)" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                dll.insertAtBeginning(value);
                break;
                
            case 2:
                cout << "Enter value to insert: ";
                cin >> value;
                dll.insertAtEnd(value);
                break;
                
            case 3:
                cout << "Enter the value after which to insert: ";
                cin >> key;
                cout << "Enter value to insert: ";
                cin >> value;
                dll.insertAfterValue(key, value);
                break;
                
            case 4:
                cout << "Enter the value before which to insert: ";
                cin >> key;
                cout << "Enter value to insert: ";
                cin >> value;
                dll.insertBeforeValue(key, value);
                break;
                
            case 5:
                cout << "Enter position to insert at: ";
                cin >> position;
                cout << "Enter value to insert: ";
                cin >> value;
                dll.insertAtPosition(position, value);
                break;
                
            case 6:
                dll.deleteFromBeginning();
                break;
                
            case 7:
                dll.deleteFromEnd();
                break;
                
            case 8:
                cout << "Enter value to delete: ";
                cin >> value;
                dll.deleteByValue(value);
                break;
                
            case 9:
                cout << "Enter position to delete from: ";
                cin >> position;
                dll.deleteAtPosition(position);
                break;
                
            case 10:
                dll.displayForward();
                break;
                
            case 11:
                dll.displayBackward();
                break;
                
            case 0:
                cout << "Exiting program..." << endl;
                break;
                
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
    
    return 0;
}
// 37.	       WAP to merge two sorted Doubly linked lists and display their result.

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
    
    // Get head pointer (needed for merge operation)
    Node* getHead() {
        return head;
    }
    
    // Set head pointer (needed for merge operation)
    void setHead(Node* newHead) {
        head = newHead;
    }
    
    // Set tail pointer (needed for merge operation)
    void setTail(Node* newTail) {
        tail = newTail;
    }
    
    // Set size (needed for merge operation)
    void setSize(int newSize) {
        size = newSize;
    }
    
    // Insert at the end
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
    }
    
    // Create sorted list from array
    void createFromArray(int arr[], int n) {
        for (int i = 0; i < n; i++) {
            insertAtEnd(arr[i]);
        }
    }
    
    // Display the list from head to tail
    void display() {
        if (isEmpty()) {
            cout << "List is empty." << endl;
            return;
        }
        
        Node* current = head;
        cout << "List: ";
        while (current != nullptr) {
            cout << current->data;
            if (current->next != nullptr) {
                cout << " <-> ";
            }
            current = current->next;
        }
        cout << " [Size: " << size << "]" << endl;
    }
};

// Function to merge two sorted doubly linked lists
DoublyLinkedList mergeSortedLists(DoublyLinkedList& list1, DoublyLinkedList& list2) {
    // Create a new list to store the merged result
    DoublyLinkedList mergedList;
    
    // Check if any of the lists is empty
    if (list1.isEmpty()) {
        return list2;
    }
    if (list2.isEmpty()) {
        return list1;
    }
    
    // Get head pointers of both lists
    Node* head1 = list1.getHead();
    Node* head2 = list2.getHead();
    Node* current = nullptr;
    
    // Determine the head of the merged list
    if (head1->data <= head2->data) {
        mergedList.setHead(head1);
        current = head1;
        head1 = head1->next;
    } else {
        mergedList.setHead(head2);
        current = head2;
        head2 = head2->next;
    }
    
    // Set the prev pointer of the head to nullptr
    current->prev = nullptr;
    
    // Merge the lists
    while (head1 != nullptr && head2 != nullptr) {
        if (head1->data <= head2->data) {
            current->next = head1;
            head1->prev = current;
            current = head1;
            head1 = head1->next;
        } else {
            current->next = head2;
            head2->prev = current;
            current = head2;
            head2 = head2->next;
        }
    }
    
    // If there are remaining elements in list1, attach them
    if (head1 != nullptr) {
        current->next = head1;
        head1->prev = current;
        
        // Find the tail of the merged list
        while (current->next != nullptr) {
            current = current->next;
        }
    }
    
    // If there are remaining elements in list2, attach them
    if (head2 != nullptr) {
        current->next = head2;
        head2->prev = current;
        
        // Find the tail of the merged list
        while (current->next != nullptr) {
            current = current->next;
        }
    }
    
    // Set the tail of the merged list
    mergedList.setTail(current);
    
    // Set the size of the merged list
    mergedList.setSize(list1.getSize() + list2.getSize());
    
    return mergedList;
}

int main() {
    DoublyLinkedList list1, list2, mergedList;
    
    cout << "=== Merge Two Sorted Doubly Linked Lists ===" << endl;
    
    // Create the first sorted list
    int arr1[] = {2, 5, 8, 12, 18};
    list1.createFromArray(arr1, 5);
    cout << "First ";
    list1.display();
    
    // Create the second sorted list
    int arr2[] = {3, 7, 9, 15, 20};
    list2.createFromArray(arr2, 5);
    cout << "Second ";
    list2.display();
    
    // Merge the two lists
    mergedList = mergeSortedLists(list1, list2);
    
    // Display the merged list
    cout << "Merged ";
    mergedList.display();
    
    // Allow user input for custom lists
    char choice;
    cout << "\nDo you want to create custom lists? (y/n): ";
    cin >> choice;
    
    if (choice == 'y' || choice == 'Y') {
        DoublyLinkedList customList1, customList2, customMergedList;
        int n1, n2, value;
        
        // Create first custom list
        cout << "\nEnter the number of elements for the first list: ";
        cin >> n1;
        cout << "Enter " << n1 << " integers in sorted order:" << endl;
        for (int i = 0; i < n1; i++) {
            cout << "Element " << i+1 << ": ";
            cin >> value;
            customList1.insertAtEnd(value);
        }
        cout << "First ";
        customList1.display();
        
        // Create second custom list
        cout << "\nEnter the number of elements for the second list: ";
        cin >> n2;
        cout << "Enter " << n2 << " integers in sorted order:" << endl;
        for (int i = 0; i < n2; i++) {
            cout << "Element " << i+1 << ": ";
            cin >> value;
            customList2.insertAtEnd(value);
        }
        cout << "Second ";
        customList2.display();
        
        // Merge the two custom lists
        customMergedList = mergeSortedLists(customList1, customList2);
        
        // Display the merged custom list
        cout << "Merged ";
        customMergedList.display();
    }
    
    return 0;
}
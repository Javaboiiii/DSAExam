// 33.	Given a list, split it into two sublists — one for the front half, and one for the back
//  half. If the number of elements is odd, the extra element should go in the front list. So FrontBackSplit() on the list {2, 3
// , 5, 7, 11} should yield the two lists {2, 3, 5} and {7, 11}. Getting this right for all the cases is harder than
//  it looks. You should check your solution against a few cases (length = 2, length = 3, length=4) to make sure
//  that the list gets split correctly near the short-list boundary conditions. 
// If it works right for length=4, it probably works right for length=1000. You will probably need special case code
//  to deal with the (length <2) cases.

#include <iostream>
using namespace std;

// Node structure for the linked list
struct Node {
    int data;
    Node* next;
    
    // Constructor for easy node creation
    Node(int val) : data(val), next(nullptr) {}
};

// Function to insert a new node at the end of the linked list
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
void display(Node* head) {
    if (head == nullptr) {
        cout << "Empty List" << endl;
        return;
    }
    
    Node* temp = head;
    cout << "{";
    while (temp != nullptr) {
        cout << temp->data;
        if (temp->next != nullptr) {
            cout << ", ";
        }
        temp = temp->next;
    }
    cout << "}" << endl;
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

// Method 1: Using slow and fast pointers (efficient approach)
void FrontBackSplit(Node* source, Node*& front, Node*& back) {
    // Handle empty list and single-node list
    if (source == nullptr) {
        front = nullptr;
        back = nullptr;
        return;
    }
    
    if (source->next == nullptr) {
        // If there's only one element, put it in the front list
        front = source;
        back = nullptr;
        return;
    }
    
    // Use slow and fast pointers to find the middle
    Node* slow = source;
    Node* fast = source->next;
    
    // Move fast two nodes ahead and slow one node ahead
    // When fast reaches the end, slow will be at the middle
    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    
    // Now slow is at the middle (or middle-left for odd-length lists)
    // Split the list into two parts
    front = source;
    back = slow->next;
    slow->next = nullptr;  // Terminate the first list
}

// Method 2: Count the nodes first, then split (alternate approach)
void FrontBackSplitByCount(Node* source, Node*& front, Node*& back) {
    // Handle empty list
    if (source == nullptr) {
        front = nullptr;
        back = nullptr;
        return;
    }
    
    // Handle single-node list
    if (source->next == nullptr) {
        front = source;
        back = nullptr;
        return;
    }
    
    // Count the number of nodes
    int count = 0;
    Node* current = source;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    
    // Calculate the middle (front will contain ceiling(count/2) nodes)
    int middlePos = (count + 1) / 2;
    
    // Traverse to the middle position
    front = source;
    current = source;
    
    for (int i = 1; i < middlePos; i++) {
        current = current->next;
    }
    
    // Split the list
    back = current->next;
    current->next = nullptr;  // Terminate the first list
}

// Function to create a test list with given values
Node* createTestList(int arr[], int size) {
    Node* head = nullptr;
    for (int i = 0; i < size; i++) {
        insertAtEnd(head, arr[i]);
    }
    return head;
}

// Function to test the FrontBackSplit function with different list lengths
void testFrontBackSplit() {
    cout << "\n=== Testing FrontBackSplit with different list lengths ===\n";
    
    // Test case 1: Empty list
    {
        Node* source = nullptr;
        Node* front = nullptr;
        Node* back = nullptr;
        
        cout << "\nTest Case 1: Empty list\n";
        cout << "Original list: ";
        display(source);
        
        FrontBackSplit(source, front, back);
        
        cout << "Front list: ";
        display(front);
        cout << "Back list: ";
        display(back);
    }
    
    // Test case 2: Single node
    {
        Node* source = new Node(1);
        Node* front = nullptr;
        Node* back = nullptr;
        
        cout << "\nTest Case 2: Single node\n";
        cout << "Original list: ";
        display(source);
        
        FrontBackSplit(source, front, back);
        
        cout << "Front list: ";
        display(front);
        cout << "Back list: ";
        display(back);
        
        // Clean up
        deleteList(front);
    }
    
    // Test case 3: Two nodes
    {
        int arr[] = {1, 2};
        Node* source = createTestList(arr, 2);
        Node* front = nullptr;
        Node* back = nullptr;
        
        cout << "\nTest Case 3: Two nodes\n";
        cout << "Original list: ";
        display(source);
        
        FrontBackSplit(source, front, back);
        
        cout << "Front list: ";
        display(front);
        cout << "Back list: ";
        display(back);
        
        // Clean up
        deleteList(front);
        deleteList(back);
    }
    
    // Test case 4: Three nodes (odd)
    {
        int arr[] = {1, 2, 3};
        Node* source = createTestList(arr, 3);
        Node* front = nullptr;
        Node* back = nullptr;
        
        cout << "\nTest Case 4: Three nodes (odd)\n";
        cout << "Original list: ";
        display(source);
        
        FrontBackSplit(source, front, back);
        
        cout << "Front list: ";
        display(front);
        cout << "Back list: ";
        display(back);
        
        // Clean up
        deleteList(front);
        deleteList(back);
    }
    
    // Test case 5: Four nodes (even)
    {
        int arr[] = {1, 2, 3, 4};
        Node* source = createTestList(arr, 4);
        Node* front = nullptr;
        Node* back = nullptr;
        
        cout << "\nTest Case 5: Four nodes (even)\n";
        cout << "Original list: ";
        display(source);
        
        FrontBackSplit(source, front, back);
        
        cout << "Front list: ";
        display(front);
        cout << "Back list: ";
        display(back);
        
        // Clean up
        deleteList(front);
        deleteList(back);
    }
    
    // Test case 6: Five nodes (odd) - the example from the problem statement
    {
        int arr[] = {2, 3, 5, 7, 11};
        Node* source = createTestList(arr, 5);
        Node* front = nullptr;
        Node* back = nullptr;
        
        cout << "\nTest Case 6: Five nodes (odd) - Example from problem\n";
        cout << "Original list: ";
        display(source);
        
        FrontBackSplit(source, front, back);
        
        cout << "Front list: ";
        display(front);
        cout << "Back list: ";
        display(back);
        
        // Clean up
        deleteList(front);
        deleteList(back);
    }
}

int main() {
    cout << "=== FrontBackSplit Implementation ===\n";
    
    // Allow user to create a custom list
    Node* head = nullptr;
    int choice, val;
    
    cout << "Enter list elements (enter -1 to stop):\n";
    while (true) {
        cin >> val;
        if (val == -1) break;
        insertAtEnd(head, val);
    }
    
    cout << "\nOriginal list: ";
    display(head);
    
    // Split the list
    Node* front = nullptr;
    Node* back = nullptr;
    
    FrontBackSplit(head, front, back);
    
    cout << "After splitting:\n";
    cout << "Front half: ";
    display(front);
    cout << "Back half: ";
    display(back);
    
    // Clean up memory
    deleteList(front);
    deleteList(back);
    
    // Run automated tests
    testFrontBackSplit();
    
    return 0;
}
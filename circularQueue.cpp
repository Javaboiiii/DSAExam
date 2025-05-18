// 30.	       Write a Program to implement circular double ended queue where user can add and remove the elements from
//  both front and rear of the queue

#include <iostream>
using namespace std;

class CircularDeque {
private:
    int* arr;       // Array to store the elements
    int front;      // Index of the front element
    int rear;       // Index of the rear element
    int size;       // Maximum size of the queue
    int count;      // Current number of elements in the queue

public:
    // Constructor
    CircularDeque(int n) {
        size = n;
        arr = new int[size];
        front = -1;
        rear = -1;
        count = 0;
    }
    
    // Destructor
    ~CircularDeque() {
        delete[] arr;
    }
    
    // Check if the queue is empty
    bool isEmpty() {
        return (count == 0);
    }
    
    // Check if the queue is full
    bool isFull() {
        return (count == size);
    }
    
    // Insert element at the front
    bool insertFront(int item) {
        if (isFull()) {
            cout << "Deque Overflow! Cannot insert at front." << endl;
            return false;
        }
        
        // If queue is initially empty
        if (isEmpty()) {
            front = 0;
            rear = 0;
        } 
        // Front is at the first position
        else if (front == 0) {
            front = size - 1;
        } 
        // Normal case
        else {
            front--;
        }
        
        arr[front] = item;
        count++;
        return true;
    }
    
    // Insert element at the rear
    bool insertRear(int item) {
        if (isFull()) {
            cout << "Deque Overflow! Cannot insert at rear." << endl;
            return false;
        }
        
        // If queue is initially empty
        if (isEmpty()) {
            front = 0;
            rear = 0;
        } 
        // Rear is at the last position
        else if (rear == size - 1) {
            rear = 0;
        } 
        // Normal case
        else {
            rear++;
        }
        
        arr[rear] = item;
        count++;
        return true;
    }
    
    // Delete element from the front
    int deleteFront() {
        if (isEmpty()) {
            cout << "Deque Underflow! Cannot delete from front." << endl;
            return -1;
        }
        
        int item = arr[front];
        
        // Only one element in the queue
        if (front == rear) {
            front = -1;
            rear = -1;
        } 
        // Front is at the last position
        else if (front == size - 1) {
            front = 0;
        } 
        // Normal case
        else {
            front++;
        }
        
        count--;
        return item;
    }
    
    // Delete element from the rear
    int deleteRear() {
        if (isEmpty()) {
            cout << "Deque Underflow! Cannot delete from rear." << endl;
            return -1;
        }
        
        int item = arr[rear];
        
        // Only one element in the queue
        if (front == rear) {
            front = -1;
            rear = -1;
        } 
        // Rear is at the first position
        else if (rear == 0) {
            rear = size - 1;
        } 
        // Normal case
        else {
            rear--;
        }
        
        count--;
        return item;
    }
    
    // Get the front element without removing it
    int getFront() {
        if (isEmpty()) {
            cout << "Deque is empty!" << endl;
            return -1;
        }
        return arr[front];
    }
    
    // Get the rear element without removing it
    int getRear() {
        if (isEmpty()) {
            cout << "Deque is empty!" << endl;
            return -1;
        }
        return arr[rear];
    }
    
    // Display all elements of the deque
    void display() {
        if (isEmpty()) {
            cout << "Deque is empty!" << endl;
            return;
        }
        
        cout << "Deque elements: ";
        int i = front;
        int elements = 0;
        
        while (elements < count) {
            cout << arr[i] << " ";
            i = (i + 1) % size;
            elements++;
        }
        cout << endl;
    }
};

int main() {
    int size, choice, value;
    
    cout << "Enter the size of the circular deque: ";
    cin >> size;
    
    CircularDeque deque(size);
    
    do {
        cout << "\n=== CIRCULAR DOUBLE ENDED QUEUE OPERATIONS ===" << endl;
        cout << "1. Insert at Front" << endl;
        cout << "2. Insert at Rear" << endl;
        cout << "3. Delete from Front" << endl;
        cout << "4. Delete from Rear" << endl;
        cout << "5. Get Front Element" << endl;
        cout << "6. Get Rear Element" << endl;
        cout << "7. Check if Empty" << endl;
        cout << "8. Check if Full" << endl;
        cout << "9. Display Queue" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter value to insert at front: ";
                cin >> value;
                deque.insertFront(value);
                break;
                
            case 2:
                cout << "Enter value to insert at rear: ";
                cin >> value;
                deque.insertRear(value);
                break;
                
            case 3:
                value = deque.deleteFront();
                if (value != -1)
                    cout << "Deleted from front: " << value << endl;
                break;
                
            case 4:
                value = deque.deleteRear();
                if (value != -1)
                    cout << "Deleted from rear: " << value << endl;
                break;
                
            case 5:
                value = deque.getFront();
                if (value != -1)
                    cout << "Front element: " << value << endl;
                break;
                
            case 6:
                value = deque.getRear();
                if (value != -1)
                    cout << "Rear element: " << value << endl;
                break;
                
            case 7:
                if (deque.isEmpty())
                    cout << "The deque is empty." << endl;
                else
                    cout << "The deque is not empty." << endl;
                break;
                
            case 8:
                if (deque.isFull())
                    cout << "The deque is full." << endl;
                else
                    cout << "The deque is not full." << endl;
                break;
                
            case 9:
                deque.display();
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
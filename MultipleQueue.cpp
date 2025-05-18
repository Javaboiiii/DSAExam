// Write a Program to implement multiple queue i.e. two queues using array and perform following operations on it. A
// . Addq, B. Delq, C. Display Queue.

#include <iostream>
using namespace std;

class MultipleQueue {
private:
    int* arr;           // Array to store elements of both queues
    int size;           // Total size of the array
    int front1, rear1;  // Front and rear pointers for first queue
    int front2, rear2;  // Front and rear pointers for second queue

public:
    // Constructor
    MultipleQueue(int n) {
        size = n;
        arr = new int[size];
        
        // Initialize first queue at the beginning of the array
        front1 = -1;
        rear1 = -1;
        
        // Initialize second queue at the end of the array
        front2 = size;
        rear2 = size;
    }
    
    // Destructor
    ~MultipleQueue() {
        delete[] arr;
    }
    
    // Check if first queue is empty
    bool isQueue1Empty() {
        return (front1 == -1);
    }
    
    // Check if second queue is empty
    bool isQueue2Empty() {
        return (front2 == size);
    }
    
    // Check if first queue is full
    bool isQueue1Full() {
        return (rear1 + 1 == front2);
    }
    
    // Check if second queue is full
    bool isQueue2Full() {
        return (rear2 - 1 == rear1);
    }
    
    // Add element to first queue (from left side of array)
    bool addQueue1(int item) {
        if (isQueue1Full()) {
            cout << "Queue 1 is full! Cannot add element." << endl;
            return false;
        }
        
        // If this is the first element in queue 1
        if (front1 == -1) {
            front1 = 0;
            rear1 = 0;
        } else {
            rear1++;
        }
        
        arr[rear1] = item;
        cout << item << " added to Queue 1" << endl;
        return true;
    }
    
    // Add element to second queue (from right side of array)
    bool addQueue2(int item) {
        if (isQueue2Full()) {
            cout << "Queue 2 is full! Cannot add element." << endl;
            return false;
        }
        
        // If this is the first element in queue 2
        if (front2 == size) {
            front2 = size - 1;
            rear2 = size - 1;
        } else {
            rear2--;
        }
        
        arr[rear2] = item;
        cout << item << " added to Queue 2" << endl;
        return true;
    }
    
    // Delete element from first queue
    int deleteQueue1() {
        if (isQueue1Empty()) {
            cout << "Queue 1 is empty! Cannot delete element." << endl;
            return -1;
        }
        
        int item = arr[front1];
        
        // If this is the last element in queue 1
        if (front1 == rear1) {
            front1 = -1;
            rear1 = -1;
        } else {
            front1++;
        }
        
        cout << item << " deleted from Queue 1" << endl;
        return item;
    }
    
    // Delete element from second queue
    int deleteQueue2() {
        if (isQueue2Empty()) {
            cout << "Queue 2 is empty! Cannot delete element." << endl;
            return -1;
        }
        
        int item = arr[front2];
        
        // If this is the last element in queue 2
        if (front2 == rear2) {
            front2 = size;
            rear2 = size;
        } else {
            front2++;
        }
        
        cout << item << " deleted from Queue 2" << endl;
        return item;
    }
    
    // Display first queue
    void displayQueue1() {
        if (isQueue1Empty()) {
            cout << "Queue 1 is empty!" << endl;
            return;
        }
        
        cout << "Queue 1 elements: ";
        for (int i = front1; i <= rear1; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    
    // Display second queue
    void displayQueue2() {
        if (isQueue2Empty()) {
            cout << "Queue 2 is empty!" << endl;
            return;
        }
        
        cout << "Queue 2 elements: ";
        for (int i = front2; i >= rear2; i--) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    
    // Display both queues
    void displayBothQueues() {
        displayQueue1();
        displayQueue2();
    }
    
    // Display the array with markers for queue boundaries
    void displayFullArray() {
        cout << "Array representation: [";
        for (int i = 0; i < size; i++) {
            if (i >= front1 && i <= rear1) {
                cout << arr[i] << "(Q1)";
            } else if (i <= front2 && i >= rear2) {
                cout << arr[i] << "(Q2)";
            } else {
                cout << "_ ";
            }
            
            if (i < size - 1) {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }
};

int main() {
    int size, choice, queueNum, value;
    
    cout << "Enter the total size for both queues: ";
    cin >> size;
    
    MultipleQueue queues(size);
    
    do {
        cout << "\n==== MULTIPLE QUEUE OPERATIONS ====" << endl;
        cout << "1. Add to Queue" << endl;
        cout << "2. Delete from Queue" << endl;
        cout << "3. Display Queue" << endl;
        cout << "4. Display Both Queues" << endl;
        cout << "5. Display Full Array" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: // Add to Queue
                cout << "Enter queue number (1 or 2): ";
                cin >> queueNum;
                cout << "Enter value to add: ";
                cin >> value;
                
                if (queueNum == 1) {
                    queues.addQueue1(value);
                } else if (queueNum == 2) {
                    queues.addQueue2(value);
                } else {
                    cout << "Invalid queue number!" << endl;
                }
                break;
                
            case 2: // Delete from Queue
                cout << "Enter queue number (1 or 2): ";
                cin >> queueNum;
                
                if (queueNum == 1) {
                    queues.deleteQueue1();
                } else if (queueNum == 2) {
                    queues.deleteQueue2();
                } else {
                    cout << "Invalid queue number!" << endl;
                }
                break;
                
            case 3: // Display Queue
                cout << "Enter queue number (1 or 2): ";
                cin >> queueNum;
                
                if (queueNum == 1) {
                    queues.displayQueue1();
                } else if (queueNum == 2) {
                    queues.displayQueue2();
                } else {
                    cout << "Invalid queue number!" << endl;
                }
                break;
                
            case 4: // Display Both Queues
                queues.displayBothQueues();
                break;
                
            case 5: // Display Full Array
                queues.displayFullArray();
                break;
                
            case 0: // Exit
                cout << "Exiting program..." << endl;
                break;
                
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 0);
    
    return 0;
}
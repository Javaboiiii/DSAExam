// 24.	WAP to implement multiple stack i.e. More than two stacks using array
//  and perform following operations on it. A. PUSH, B. POP, C. StackFull D. StackeEmpty E. Display Stack.

#include <iostream>
#include <vector>
using namespace std;

class MultiStack {
private:
    int* arr;               // Array to store elements of all stacks
    int* top;               // Array to store top indices of each stack
    int* base;              // Array to store base indices of each stack
    int* capacity;          // Array to store capacity of each stack
    int numStacks;          // Number of stacks
    int totalSize;          // Total size of the array

public:
    // Constructor
    MultiStack(int n, vector<int> sizes) {
        numStacks = n;
        totalSize = 0;
        
        // Calculate total size needed for the array
        for (int i = 0; i < n; i++) {
            totalSize += sizes[i];
        }
        
        // Initialize arrays
        arr = new int[totalSize];
        top = new int[numStacks];
        base = new int[numStacks];
        capacity = new int[numStacks];
        
        // Set the base, top, and capacity for each stack
        int currentBase = 0;
        for (int i = 0; i < numStacks; i++) {
            base[i] = currentBase;
            top[i] = currentBase - 1;  // Initially, stack is empty
            capacity[i] = sizes[i];
            currentBase += sizes[i];
        }
    }
    
    // Destructor
    ~MultiStack() {
        delete[] arr;
        delete[] top;
        delete[] base;
        delete[] capacity;
    }
    
    // Push operation - Add an element to a specific stack
    bool push(int stackNum, int value) {
        // Check if the stack is full
        if (isStackFull(stackNum)) {
            cout << "Stack " << stackNum << " is full. Cannot push element " << value << endl;
            return false;
        }
        
        // Increment top and push the value
        top[stackNum - 1]++;
        arr[top[stackNum - 1]] = value;
        cout << "Pushed " << value << " to Stack " << stackNum << endl;
        return true;
    }
    
    // Pop operation - Remove the top element from a specific stack
    int pop(int stackNum) {
        // Check if the stack is empty
        if (isStackEmpty(stackNum)) {
            cout << "Stack " << stackNum << " is empty. Cannot pop element." << endl;
            return -1;
        }
        
        // Get the top value and decrement top
        int value = arr[top[stackNum - 1]];
        top[stackNum - 1]--;
        cout << "Popped " << value << " from Stack " << stackNum << endl;
        return value;
    }
    
    // Check if a specific stack is full
    bool isStackFull(int stackNum) {
        // Adjust stackNum to 0-based index
        stackNum--;
        
        // Check if top has reached the maximum allowed index for this stack
        return (top[stackNum] == base[stackNum] + capacity[stackNum] - 1);
    }
    
    // Check if a specific stack is empty
    bool isStackEmpty(int stackNum) {
        // Adjust stackNum to 0-based index
        stackNum--;
        
        // Check if top is less than the base index for this stack
        return (top[stackNum] < base[stackNum]);
    }
    
    // Display a specific stack
    void displayStack(int stackNum) {
        // Adjust stackNum to 0-based index
        stackNum--;
        
        if (top[stackNum] < base[stackNum]) {
            cout << "Stack " << stackNum + 1 << " is empty." << endl;
            return;
        }
        
        cout << "Stack " << stackNum + 1 << " elements: ";
        for (int i = base[stackNum]; i <= top[stackNum]; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    
    // Display all stacks
    void displayAllStacks() {
        for (int i = 1; i <= numStacks; i++) {
            displayStack(i);
        }
    }
};

int main() {
    int n, size;
    
    cout << "Enter the number of stacks: ";
    cin >> n;
    
    vector<int> sizes(n);
    cout << "Enter the size of each stack: " << endl;
    for (int i = 0; i < n; i++) {
        cout << "Size of stack " << i + 1 << ": ";
        cin >> sizes[i];
    }
    
    MultiStack stacks(n, sizes);
    int choice, stackNum, value;
    
    do {
        cout << "\n----- MULTIPLE STACK OPERATIONS -----" << endl;
        cout << "1. PUSH" << endl;
        cout << "2. POP" << endl;
        cout << "3. Check if stack is FULL" << endl;
        cout << "4. Check if stack is EMPTY" << endl;
        cout << "5. Display a specific stack" << endl;
        cout << "6. Display all stacks" << endl;
        cout << "0. EXIT" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: // PUSH
                cout << "Enter stack number: ";
                cin >> stackNum;
                if (stackNum < 1 || stackNum > n) {
                    cout << "Invalid stack number." << endl;
                    break;
                }
                cout << "Enter value to push: ";
                cin >> value;
                stacks.push(stackNum, value);
                break;
                
            case 2: // POP
                cout << "Enter stack number: ";
                cin >> stackNum;
                if (stackNum < 1 || stackNum > n) {
                    cout << "Invalid stack number." << endl;
                    break;
                }
                stacks.pop(stackNum);
                break;
                
            case 3: // Check if stack is FULL
                cout << "Enter stack number: ";
                cin >> stackNum;
                if (stackNum < 1 || stackNum > n) {
                    cout << "Invalid stack number." << endl;
                    break;
                }
                if (stacks.isStackFull(stackNum)) {
                    cout << "Stack " << stackNum << " is full." << endl;
                } else {
                    cout << "Stack " << stackNum << " is not full." << endl;
                }
                break;
                
            case 4: // Check if stack is EMPTY
                cout << "Enter stack number: ";
                cin >> stackNum;
                if (stackNum < 1 || stackNum > n) {
                    cout << "Invalid stack number." << endl;
                    break;
                }
                if (stacks.isStackEmpty(stackNum)) {
                    cout << "Stack " << stackNum << " is empty." << endl;
                } else {
                    cout << "Stack " << stackNum << " is not empty." << endl;
                }
                break;
                
            case 5: // Display a specific stack
                cout << "Enter stack number: ";
                cin >> stackNum;
                if (stackNum < 1 || stackNum > n) {
                    cout << "Invalid stack number." << endl;
                    break;
                }
                stacks.displayStack(stackNum);
                break;
                
            case 6: // Display all stacks
                stacks.displayAllStacks();
                break;
                
            case 0: // EXIT
                cout << "Exiting program." << endl;
                break;
                
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
    
    return 0;
}
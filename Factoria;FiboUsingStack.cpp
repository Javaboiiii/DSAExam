// 26.	WAP to implement following by using stack. A. Factorial of a given number B. Generation of
//  Fibonacci series.

#include <iostream>
#include <stack>
using namespace std;

// A. Factorial calculation using stack
unsigned long long calculateFactorial(int n) {
    if (n < 0) {
        cout << "Factorial is not defined for negative numbers." << endl;
        return 0;
    }
    
    if (n == 0 || n == 1) {
        return 1;
    }
    
    stack<int> numStack;
    
    // Push all numbers from n down to 2 onto the stack
    for (int i = n; i >= 2; i--) {
        numStack.push(i);
    }
    
    unsigned long long result = 1;
    
    // Pop numbers and multiply
    while (!numStack.empty()) {
        result *= numStack.top();
        numStack.pop();
    }
    
    return result;
}

// B. Fibonacci series generation using stack
void generateFibonacci(int n) {
    if (n <= 0) {
        cout << "Number of terms must be positive." << endl;
        return;
    }
    
    stack<int> fibStack; // Will store terms in reverse order
    
    // Calculate Fibonacci terms
    int a = 0, b = 1, c;
    
    if (n >= 1) {
        fibStack.push(a); // Push first term
    }
    
    if (n >= 2) {
        fibStack.push(b); // Push second term
    }
    
    for (int i = 3; i <= n; i++) {
        c = a + b;
        fibStack.push(c);
        a = b;
        b = c;
    }
    
    // Print terms in correct order by reversing the stack
    stack<int> tempStack;
    while (!fibStack.empty()) {
        tempStack.push(fibStack.top());
        fibStack.pop();
    }
    
    cout << "Fibonacci Series: ";
    while (!tempStack.empty()) {
        cout << tempStack.top() << " ";
        tempStack.pop();
    }
    cout << endl;
}

// Alternative Fibonacci implementation using two stacks directly
void generateFibonacciAlt(int n) {
    if (n <= 0) {
        cout << "Number of terms must be positive." << endl;
        return;
    }
    
    // Using two stacks to avoid having to reverse
    stack<int> valueStack;    // Stores the actual values
    stack<int> indexStack;    // Stores the indices
    
    cout << "Fibonacci Series (Alternative): ";
    
    if (n >= 1) {
        cout << "0 ";
    }
    
    if (n >= 2) {
        cout << "1 ";
    }
    
    if (n <= 2) {
        cout << endl;
        return;
    }
    
    // Initialize with the computation for the 3rd number
    indexStack.push(3);
    valueStack.push(0);    // First number in the addition (Fib(1))
    valueStack.push(1);    // Second number in the addition (Fib(2))
    
    while (!indexStack.empty()) {
        int idx = indexStack.top();
        indexStack.pop();
        
        int b = valueStack.top();
        valueStack.pop();
        
        int a = valueStack.top();
        valueStack.pop();
        
        int c = a + b;
        cout << c << " ";
        
        if (idx < n) {
            indexStack.push(idx + 1);
            valueStack.push(b);    // New first number (previous second)
            valueStack.push(c);    // New second number (previous result)
        }
    }
    
    cout << endl;
}

// Function to demonstrate non-stack solution for comparison
void fibonacciWithoutStack(int n) {
    if (n <= 0) {
        cout << "Number of terms must be positive." << endl;
        return;
    }
    
    cout << "Fibonacci Series (Without Stack): ";
    
    int a = 0, b = 1, c;
    
    if (n >= 1) {
        cout << a << " ";
    }
    
    if (n >= 2) {
        cout << b << " ";
    }
    
    for (int i = 3; i <= n; i++) {
        c = a + b;
        cout << c << " ";
        a = b;
        b = c;
    }
    
    cout << endl;
}

int main() {
    int choice, n;
    
    do {
        cout << "\n==== MENU ====" << endl;
        cout << "1. Calculate Factorial using Stack" << endl;
        cout << "2. Generate Fibonacci Series using Stack (Reverse and Print)" << endl;
        cout << "3. Generate Fibonacci Series using Stack (Alternative Method)" << endl;
        cout << "4. Generate Fibonacci Series without Stack (For Comparison)" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter a non-negative integer: ";
                cin >> n;
                cout << "Factorial of " << n << " is: " << calculateFactorial(n) << endl;
                break;
                
            case 2:
                cout << "Enter the number of Fibonacci terms to generate: ";
                cin >> n;
                generateFibonacci(n);
                break;
                
            case 3:
                cout << "Enter the number of Fibonacci terms to generate: ";
                cin >> n;
                generateFibonacciAlt(n);
                break;
                
            case 4:
                cout << "Enter the number of Fibonacci terms to generate: ";
                cin >> n;
                fibonacciWithoutStack(n);
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
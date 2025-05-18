// 23.	WAP to convert a given Infix expression into its equivalent Prefix expression and evaluate it using stack.

#include <iostream>
#include <string>
#include <stack>
#include <algorithm>
#include <cmath>
using namespace std;

// Function to check if the character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Function to check if the character is an operand (alphanumeric)
bool isOperand(char c) {
    return isalnum(c);
}

// Function to get the precedence of operators
int getPrecedence(char op) {
    if (op == '^')
        return 3;
    else if (op == '*' || op == '/')
        return 2;
    else if (op == '+' || op == '-')
        return 1;
    else
        return -1; // For '(' or other non-operators
}

// Function to convert infix expression to prefix expression
string infixToPrefix(string infix) {
    // Reverse the infix expression
    reverse(infix.begin(), infix.end());
    
    // Replace '(' with ')' and vice versa
    for (int i = 0; i < infix.length(); i++) {
        if (infix[i] == '(')
            infix[i] = ')';
        else if (infix[i] == ')')
            infix[i] = '(';
    }
    
    stack<char> stk;
    string prefix = "";
    
    for (int i = 0; i < infix.length(); i++) {
        char c = infix[i];
        
        // If the scanned character is an operand, add it to the output string
        if (isOperand(c)) {
            prefix += c;
        }
        // If the scanned character is '(', push it to the stack
        else if (c == '(') {
            stk.push(c);
        }
        // If the scanned character is ')', pop from stack and add to output until '(' is found
        else if (c == ')') {
            while (!stk.empty() && stk.top() != '(') {
                prefix += stk.top();
                stk.pop();
            }
            
            if (!stk.empty() && stk.top() == '(') {
                stk.pop(); // Remove '(' from stack
            }
        }
        // If an operator is encountered
        else if (isOperator(c)) {
            // Note: the condition is slightly different from infix to postfix
            // as in prefix, operators with equal precedence are processed right to left
            while (!stk.empty() && stk.top() != '(' && 
                   getPrecedence(c) < getPrecedence(stk.top())) {
                prefix += stk.top();
                stk.pop();
            }
            stk.push(c);
        }
        // Skip whitespace
        else if (c != ' ') {
            cout << "Invalid character in infix expression: " << c << endl;
            return "";
        }
    }
    
    // Pop all the remaining elements from the stack
    while (!stk.empty()) {
        if (stk.top() == '(') {
            cout << "Invalid expression: Unmatched parenthesis" << endl;
            return "";
        }
        prefix += stk.top();
        stk.pop();
    }
    
    // Reverse the prefix expression to get the final result
    reverse(prefix.begin(), prefix.end());
    
    return prefix;
}

// Function to perform an operation
int performOperation(int operand1, int operand2, char op) {
    switch(op) {
        case '+': return operand1 + operand2;
        case '-': return operand1 - operand2;
        case '*': return operand1 * operand2;
        case '/': return operand1 / operand2;
        case '^': return pow(operand1, operand2);
        default: return 0;
    }
}

// Function to evaluate a prefix expression
int evaluatePrefix(string prefix) {
    stack<int> stk;
    
    // Scan the prefix expression from right to left
    for (int i = prefix.length() - 1; i >= 0; i--) {
        char c = prefix[i];
        
        // If the scanned character is an operand, push it to the stack
        if (isOperand(c)) {
            // Convert char to int
            stk.push(c - '0');
        }
        // If the scanned character is an operator, pop two elements from stack,
        // perform operation and push the result back
        else if (isOperator(c)) {
            if (stk.size() < 2) {
                cout << "Invalid prefix expression" << endl;
                return -1;
            }
            
            int operand1 = stk.top();
            stk.pop();
            
            int operand2 = stk.top();
            stk.pop();
            
            int result = performOperation(operand1, operand2, c);
            stk.push(result);
        }
    }
    
    // Return the final result
    if (stk.size() != 1) {
        cout << "Invalid prefix expression" << endl;
        return -1;
    }
    
    return stk.top();
}

int main() {
    string infixExpression;
    
    cout << "Enter an infix expression (use single digits for operands): ";
    getline(cin, infixExpression);
    
    string prefixExpression = infixToPrefix(infixExpression);
    
    if (!prefixExpression.empty()) {
        cout << "Infix Expression: " << infixExpression << endl;
        cout << "Prefix Expression: " << prefixExpression << endl;
        
        int result = evaluatePrefix(prefixExpression);
        if (result != -1) {
            cout << "Evaluation Result: " << result << endl;
        }
    }
    
    return 0;
}
// 22.	WAP to convert a given Infix expression into its equivalent Postfix expression and
//  evaluate it using stack.

#include <iostream>
#include <string>
#include <stack>
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

// Function to convert infix expression to postfix expression
string infixToPostfix(string infix) {
    stack<char> stk;
    string postfix = "";
    
    for (int i = 0; i < infix.length(); i++) {
        char c = infix[i];
        
        // If the scanned character is an operand, add it to the output string
        if (isOperand(c)) {
            postfix += c;
        }
        // If the scanned character is '(', push it to the stack
        else if (c == '(') {
            stk.push(c);
        }
        // If the scanned character is ')', pop from stack and add to output until '(' is found
        else if (c == ')') {
            while (!stk.empty() && stk.top() != '(') {
                postfix += stk.top();
                stk.pop();
            }
            
            if (!stk.empty() && stk.top() == '(') {
                stk.pop(); // Remove '(' from stack
            }
        }
        // If an operator is encountered
        else if (isOperator(c)) {
            while (!stk.empty() && stk.top() != '(' && 
                   getPrecedence(c) <= getPrecedence(stk.top())) {
                postfix += stk.top();
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
        postfix += stk.top();
        stk.pop();
    }
    
    return postfix;
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

// Function to evaluate a postfix expression
int evaluatePostfix(string postfix) {
    stack<int> stk;
    
    for (int i = 0; i < postfix.length(); i++) {
        char c = postfix[i];
        
        // If the scanned character is an operand, push it to the stack
        if (isOperand(c)) {
            // Convert char to int
            stk.push(c - '0');
        }
        // If the scanned character is an operator, pop two elements from stack,
        // perform operation and push the result back
        else if (isOperator(c)) {
            if (stk.size() < 2) {
                cout << "Invalid postfix expression" << endl;
                return -1;
            }
            
            int operand2 = stk.top();
            stk.pop();
            
            int operand1 = stk.top();
            stk.pop();
            
            int result = performOperation(operand1, operand2, c);
            stk.push(result);
        }
    }
    
    // Return the final result
    if (stk.size() != 1) {
        cout << "Invalid postfix expression" << endl;
        return -1;
    }
    
    return stk.top();
}

int main() {
    string infixExpression;
    
    cout << "Enter an infix expression (use single digits for operands): ";
    getline(cin, infixExpression);
    
    string postfixExpression = infixToPostfix(infixExpression);
    
    if (!postfixExpression.empty()) {
        cout << "Infix Expression: " << infixExpression << endl;
        cout << "Postfix Expression: " << postfixExpression << endl;
        
        int result = evaluatePostfix(postfixExpression);
        if (result != -1) {
            cout << "Evaluation Result: " << result << endl;
        }
    }
    
    return 0;
}
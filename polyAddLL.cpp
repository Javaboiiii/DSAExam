// WAP to perform addition of two polynomials using singly linked list.

#include <iostream>
#include <iomanip>
using namespace std;

// Node structure for polynomial terms
struct Node {
    int coefficient;  // Coefficient of the term
    int exponent;     // Exponent/power of the term
    Node* next;       // Pointer to the next term
    
    // Constructor for easy node creation
    Node(int coeff, int exp) : coefficient(coeff), exponent(exp), next(nullptr) {}
};

// Function to insert a term into a polynomial
// Terms are inserted in descending order of exponents
void insertTerm(Node* &head, int coeff, int exp) {
    // Skip if coefficient is 0
    if (coeff == 0) {
        return;
    }
    
    Node* newNode = new Node(coeff, exp);
    
    // If list is empty or new term has higher exponent than head
    if (head == nullptr || exp > head->exponent) {
        newNode->next = head;
        head = newNode;
        return;
    }
    
    // Find the right position to insert (descending order of exponents)
    Node* current = head;
    
    // If term with same exponent exists, add coefficients
    if (current->exponent == exp) {
        current->coefficient += coeff;
        // If coefficient becomes zero, remove the term
        if (current->coefficient == 0) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        delete newNode;
        return;
    }
    
    // Traverse to find the correct position
    while (current->next != nullptr && current->next->exponent > exp) {
        current = current->next;
    }
    
    // If term with same exponent exists in the middle of the list
    if (current->next != nullptr && current->next->exponent == exp) {
        current->next->coefficient += coeff;
        // If coefficient becomes zero, remove the term
        if (current->next->coefficient == 0) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
        delete newNode;
        return;
    }
    
    // Insert the new term
    newNode->next = current->next;
    current->next = newNode;
}

// Function to add two polynomials
Node* addPolynomials(Node* poly1, Node* poly2) {
    Node* result = nullptr;
    Node* p1 = poly1;
    Node* p2 = poly2;
    
    // Process both polynomials until one of them is fully processed
    while (p1 != nullptr && p2 != nullptr) {
        if (p1->exponent > p2->exponent) {
            // p1's exponent is higher, add it to result
            insertTerm(result, p1->coefficient, p1->exponent);
            p1 = p1->next;
        } else if (p1->exponent < p2->exponent) {
            // p2's exponent is higher, add it to result
            insertTerm(result, p2->coefficient, p2->exponent);
            p2 = p2->next;
        } else {
            // Exponents are equal, add coefficients
            int sumCoeff = p1->coefficient + p2->coefficient;
            if (sumCoeff != 0) {
                insertTerm(result, sumCoeff, p1->exponent);
            }
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    
    // Process remaining terms of polynomial 1
    while (p1 != nullptr) {
        insertTerm(result, p1->coefficient, p1->exponent);
        p1 = p1->next;
    }
    
    // Process remaining terms of polynomial 2
    while (p2 != nullptr) {
        insertTerm(result, p2->coefficient, p2->exponent);
        p2 = p2->next;
    }
    
    return result;
}

// Function to display a polynomial
void displayPolynomial(Node* head) {
    if (head == nullptr) {
        cout << "0" << endl;
        return;
    }
    
    Node* current = head;
    bool isFirst = true;
    
    while (current != nullptr) {
        // Print + sign for all terms except the first one
        if (!isFirst) {
            if (current->coefficient > 0) {
                cout << " + ";
            } else {
                cout << " - ";
            }
        } else if (current->coefficient < 0) {
            cout << "-";
        }
        
        // Print coefficient (absolute value for non-first negative terms)
        int coeffAbs = abs(current->coefficient);
        if (coeffAbs != 1 || current->exponent == 0) {
            cout << coeffAbs;
        }
        
        // Print variable and exponent
        if (current->exponent > 0) {
            cout << "x";
            if (current->exponent > 1) {
                cout << "^" << current->exponent;
            }
        }
        
        current = current->next;
        isFirst = false;
    }
    cout << endl;
}

// Function to create a polynomial from user input
Node* createPolynomial() {
    Node* poly = nullptr;
    int numTerms, coeff, exp;
    
    cout << "Enter number of terms: ";
    cin >> numTerms;
    
    for (int i = 0; i < numTerms; i++) {
        cout << "Term " << i+1 << " - Enter coefficient: ";
        cin >> coeff;
        cout << "Term " << i+1 << " - Enter exponent: ";
        cin >> exp;
        
        insertTerm(poly, coeff, exp);
    }
    
    return poly;
}

// Function to free memory allocated for a polynomial
void deletePolynomial(Node* &head) {
    Node* current = head;
    Node* next = nullptr;
    
    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }
    
    head = nullptr;
}

int main() {
    cout << "=== Polynomial Addition using Linked List ===" << endl;
    
    cout << "\nEnter the first polynomial:" << endl;
    Node* poly1 = createPolynomial();
    
    cout << "\nEnter the second polynomial:" << endl;
    Node* poly2 = createPolynomial();
    
    cout << "\nFirst Polynomial: ";
    displayPolynomial(poly1);
    
    cout << "Second Polynomial: ";
    displayPolynomial(poly2);
    
    Node* result = addPolynomials(poly1, poly2);
    
    cout << "\nResultant Polynomial (Sum): ";
    displayPolynomial(result);
    
    // Clean up memory
    deletePolynomial(poly1);
    deletePolynomial(poly2);
    deletePolynomial(result);
    
    return 0;
}
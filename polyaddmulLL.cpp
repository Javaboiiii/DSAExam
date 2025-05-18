// 41.	Implement a Polynomial addition and multiplication using Linked Lists.

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
    
    // If term with same exponent exists at head
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

// Function to create a deep copy of a polynomial
Node* copyPolynomial(Node* poly) {
    Node* result = nullptr;
    Node* current = poly;
    
    while (current != nullptr) {
        insertTerm(result, current->coefficient, current->exponent);
        current = current->next;
    }
    
    return result;
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

// Function to multiply two polynomials
Node* multiplyPolynomials(Node* poly1, Node* poly2) {
    Node* result = nullptr;
    Node* p1 = poly1;
    
    // Multiply each term of poly1 with every term of poly2
    while (p1 != nullptr) {
        Node* p2 = poly2;
        Node* tempResult = nullptr;
        
        while (p2 != nullptr) {
            // Multiply coefficients and add exponents
            int newCoeff = p1->coefficient * p2->coefficient;
            int newExp = p1->exponent + p2->exponent;
            
            // Add this term to the temporary result
            insertTerm(tempResult, newCoeff, newExp);
            
            p2 = p2->next;
        }
        
        // Add tempResult to the final result
        // This is equivalent to accumulating the partial results
        Node* oldResult = result;
        result = addPolynomials(result, tempResult);
        
        // Free memory of old result and temporary result
        while (oldResult != nullptr) {
            Node* temp = oldResult;
            oldResult = oldResult->next;
            delete temp;
        }
        
        while (tempResult != nullptr) {
            Node* temp = tempResult;
            tempResult = tempResult->next;
            delete temp;
        }
        
        p1 = p1->next;
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
    int n, coeff, exp;
    
    cout << "Enter the number of terms: ";
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        cout << "Term " << i + 1 << ":" << endl;
        cout << "Enter coefficient: ";
        cin >> coeff;
        cout << "Enter exponent: ";
        cin >> exp;
        
        insertTerm(poly, coeff, exp);
    }
    
    return poly;
}

// Function to free memory of a polynomial
void freePolynomial(Node* &poly) {
    while (poly != nullptr) {
        Node* temp = poly;
        poly = poly->next;
        delete temp;
    }
}

int main() {
    cout << "=== Polynomial Operations using Linked Lists ===" << endl;
    
    // Create first polynomial
    cout << "\nCreate first polynomial:" << endl;
    Node* poly1 = createPolynomial();
    cout << "First polynomial: ";
    displayPolynomial(poly1);
    
    // Create second polynomial
    cout << "\nCreate second polynomial:" << endl;
    Node* poly2 = createPolynomial();
    cout << "Second polynomial: ";
    displayPolynomial(poly2);
    
    // Addition
    Node* sumPoly = addPolynomials(poly1, poly2);
    cout << "\nSum of polynomials: ";
    displayPolynomial(sumPoly);
    
    // Multiplication
    Node* productPoly = multiplyPolynomials(poly1, poly2);
    cout << "Product of polynomials: ";
    displayPolynomial(productPoly);
    
    // Memory cleanup
    freePolynomial(poly1);
    freePolynomial(poly2);
    freePolynomial(sumPoly);
    freePolynomial(productPoly);
    
    return 0;
}
#include <iostream> 

// 11.	Write a program to efficiently search a particular employee
//  record by using Tree data structure. Also sort the data on emp-id in
//   ascending order.

using namespace std; 

struct Node { 
    int id; 
    string name; 
    int salary; 
    Node* right; 
    Node* left; 

    Node(int id, string name, int salary) { 
        id = id; 
        name = name; 
        salary = salary; 
        left = nullptr; 
        right = nullptr; 
    }
};

int main() { 
    return 0; 
}
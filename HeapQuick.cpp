// 20.	WAP to implement Heap sort and Quick Sort on 1D array of Student structure
//  (contains student_name, student_roll_no, total_marks), with key as student_roll_no.
//  And count the number of swap performed.

#include <iostream>
#include <string>
using namespace std;

// Student structure with required fields
struct Student {
    string student_name;
    int student_roll_no;
    int total_marks;
};

// Function to display student details
void displayStudent(const Student& student) {
    cout << "Roll No: " << student.student_roll_no 
         << ", Name: " << student.student_name 
         << ", Marks: " << student.total_marks << endl;
}

// Function to display array of students
void displayStudents(Student arr[], int n) {
    for (int i = 0; i < n; i++) {
        displayStudent(arr[i]);
    }
    cout << endl;
}

// HEAP SORT Implementation
int heapSwapCount = 0;

// Heapify a subtree rooted with node i
void heapify(Student arr[], int n, int i) {
    int largest = i;     // Initialize largest as root
    int left = 2 * i + 1;    // left child
    int right = 2 * i + 2;   // right child
    
    // If left child is larger than root
    if (left < n && arr[left].student_roll_no > arr[largest].student_roll_no)
        largest = left;
    
    // If right child is larger than largest so far
    if (right < n && arr[right].student_roll_no > arr[largest].student_roll_no)
        largest = right;
    
    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapSwapCount++;
        
        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// Main function to perform heap sort
void heapSort(Student arr[], int n) {
    heapSwapCount = 0;
    
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    
    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap(arr[0], arr[i]);
        heapSwapCount++;
        
        // Call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

// QUICK SORT Implementation
int quickSwapCount = 0;

// Function to partition the array
int partition(Student arr[], int low, int high) {
    int pivot = arr[high].student_roll_no;  // pivot
    int i = (low - 1);  // Index of smaller element
    
    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than the pivot
        if (arr[j].student_roll_no < pivot) {
            i++;    // increment index of smaller element
            swap(arr[i], arr[j]);
            quickSwapCount++;
        }
    }
    swap(arr[i + 1], arr[high]);
    quickSwapCount++;
    return (i + 1);
}

// The main function that implements QuickSort
void quickSort(Student arr[], int low, int high) {
    if (low < high) {
        // pi is partitioning index, arr[p] is now at right place
        int pi = partition(arr, low, high);
        
        // Separately sort elements before and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to initialize quick sort and reset swap counter
void performQuickSort(Student arr[], int n) {
    quickSwapCount = 0;
    quickSort(arr, 0, n - 1);
}

int main() {
    const int SIZE = 5;
    Student students[SIZE] = {
        {"Alice", 104, 85},
        {"Bob", 102, 92},
        {"Charlie", 101, 78},
        {"David", 105, 95},
        {"Eve", 103, 88}
    };
    
    // Display original array
    cout << "Original Student Array:" << endl;
    displayStudents(students, SIZE);
    
    // Create a copy for heap sort
    Student heapStudents[SIZE];
    for (int i = 0; i < SIZE; i++) {
        heapStudents[i] = students[i];
    }
    
    // Perform Heap Sort
    heapSort(heapStudents, SIZE);
    cout << "\nAfter Heap Sort:" << endl;
    displayStudents(heapStudents, SIZE);
    cout << "Number of swaps in Heap Sort: " << heapSwapCount << endl;
    
    // Create a copy for quick sort
    Student quickStudents[SIZE];
    for (int i = 0; i < SIZE; i++) {
        quickStudents[i] = students[i];
    }
    
    // Perform Quick Sort
    performQuickSort(quickStudents, SIZE);
    cout << "\nAfter Quick Sort:" << endl;
    displayStudents(quickStudents, SIZE);
    cout << "Number of swaps in Quick Sort: " << quickSwapCount << endl;
    
    return 0;
}
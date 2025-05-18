// 21.	WAP to implement Heap sort and Merge Sort on 1D array of Student structure (contains
//  student_name, student_roll_no, total_marks), with key as student_roll_no. And count the number of swap performed.

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

// MERGE SORT Implementation
int mergeSwapCount = 0;

// Merge two subarrays L and R into arr
void merge(Student arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    // Create temporary arrays
    Student* L = new Student[n1];
    Student* R = new Student[n2];
    
    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    // Merge the temporary arrays back into arr[left..right]
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = left; // Initial index of merged subarray
    
    while (i < n1 && j < n2) {
        if (L[i].student_roll_no <= R[j].student_roll_no) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
            // Count swaps: we consider each time a right element is placed before a left element as a swap
            mergeSwapCount += (n1 - i);
        }
        k++;
    }
    
    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    // Free allocated memory
    delete[] L;
    delete[] R;
}

// Main function that sorts arr[left..right] using merge()
void mergeSort(Student arr[], int left, int right) {
    if (left < right) {
        // Same as (left+right)/2, but avoids overflow for large left and right
        int mid = left + (right - left) / 2;
        
        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        
        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

// Function to initialize merge sort and reset swap counter
void performMergeSort(Student arr[], int n) {
    mergeSwapCount = 0;
    mergeSort(arr, 0, n - 1);
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
    
    // Create a copy for merge sort
    Student mergeStudents[SIZE];
    for (int i = 0; i < SIZE; i++) {
        mergeStudents[i] = students[i];
    }
    
    // Perform Merge Sort
    performMergeSort(mergeStudents, SIZE);
    cout << "\nAfter Merge Sort:" << endl;
    displayStudents(mergeStudents, SIZE);
    cout << "Number of swaps in Merge Sort: " << mergeSwapCount << endl;
    
    return 0;
}
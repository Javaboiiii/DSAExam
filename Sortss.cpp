// 40.	WAP to implement Insertion sort, Merge Sort, Bubble Sort and Quick Sort on 1D array of Student
//  structure (contains student_name, student_roll_no, total_marks ), with key as student_roll_no. and count the
//  number of swap performed

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

// ==================== 1. BUBBLE SORT Implementation ====================
int bubbleSwapCount = 0;

void bubbleSort(Student arr[], int n) {
    bubbleSwapCount = 0;
    
    for (int i = 0; i < n - 1; i++) {
        // Flag to optimize if no swaps are made in a pass
        bool swapped = false;
        
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].student_roll_no > arr[j + 1].student_roll_no) {
                swap(arr[j], arr[j + 1]);
                bubbleSwapCount++;
                swapped = true;
            }
        }
        
        // If no swaps were made in this pass, array is sorted
        if (!swapped) {
            break;
        }
    }
}

// ==================== 2. INSERTION SORT Implementation ====================
int insertionSwapCount = 0;

void insertionSort(Student arr[], int n) {
    insertionSwapCount = 0;
    
    for (int i = 1; i < n; i++) {
        Student key = arr[i];
        int j = i - 1;
        
        // Move elements of arr[0..i-1] that are greater than key
        // to one position ahead of their current position
        while (j >= 0 && arr[j].student_roll_no > key.student_roll_no) {
            arr[j + 1] = arr[j];
            insertionSwapCount++;
            j--;
        }
        
        arr[j + 1] = key;
    }
}

// ==================== 3. MERGE SORT Implementation ====================
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
            // Count swaps when elements from right subarray come before left
            mergeSwapCount += (n1 - i);
        }
        k++;
    }
    
    // Copy remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    // Copy remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    // Free allocated memory
    delete[] L;
    delete[] R;
}

// Main merge sort function
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

// Wrapper function for merge sort
void mergeSortWrapper(Student arr[], int n) {
    mergeSwapCount = 0;
    mergeSort(arr, 0, n - 1);
}

// ==================== 4. QUICK SORT Implementation ====================
int quickSwapCount = 0;

// Function to partition the array and place pivot at its correct position
int partition(Student arr[], int low, int high) {
    // Select the pivot element (using the last element)
    int pivot = arr[high].student_roll_no;
    int i = low - 1; // Index of smaller element
    
    for (int j = low; j < high; j++) {
        // If current element is smaller than or equal to pivot
        if (arr[j].student_roll_no <= pivot) {
            i++; // Increment index of smaller element
            swap(arr[i], arr[j]);
            quickSwapCount++;
        }
    }
    
    // Place the pivot element at its correct position
    swap(arr[i + 1], arr[high]);
    quickSwapCount++;
    
    return i + 1;
}

// Main quick sort function
void quickSort(Student arr[], int low, int high) {
    if (low < high) {
        // pi is partitioning index, arr[pi] is now at right place
        int pi = partition(arr, low, high);
        
        // Separately sort elements before and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Wrapper function for quick sort
void quickSortWrapper(Student arr[], int n) {
    quickSwapCount = 0;
    quickSort(arr, 0, n - 1);
}

// Function to create a copy of the original array
void copyArray(Student source[], Student destination[], int n) {
    for (int i = 0; i < n; i++) {
        destination[i] = source[i];
    }
}

int main() {
    int n;
    cout << "Enter the number of students: ";
    cin >> n;
    
    // Allocate memory for student arrays
    Student* originalArray = new Student[n];
    Student* workingArray = new Student[n];
    
    // Input student details
    cout << "\nEnter student details:\n";
    for (int i = 0; i < n; i++) {
        cout << "\nStudent " << i + 1 << ":\n";
        cout << "Name: ";
        cin.ignore(); // Clear input buffer
        getline(cin, originalArray[i].student_name);
        cout << "Roll No: ";
        cin >> originalArray[i].student_roll_no;
        cout << "Total Marks: ";
        cin >> originalArray[i].total_marks;
    }
    
    // Display original array
    cout << "\nOriginal array of students:\n";
    displayStudents(originalArray, n);
    
    // 1. Bubble Sort
    copyArray(originalArray, workingArray, n);
    cout << "\n1. Bubble Sort:\n";
    bubbleSort(workingArray, n);
    cout << "Sorted array (by Roll No):\n";
    displayStudents(workingArray, n);
    cout << "Number of swaps performed: " << bubbleSwapCount << endl;
    
    // 2. Insertion Sort
    copyArray(originalArray, workingArray, n);
    cout << "\n2. Insertion Sort:\n";
    insertionSort(workingArray, n);
    cout << "Sorted array (by Roll No):\n";
    displayStudents(workingArray, n);
    cout << "Number of swaps performed: " << insertionSwapCount << endl;
    
    // 3. Merge Sort
    copyArray(originalArray, workingArray, n);
    cout << "\n3. Merge Sort:\n";
    mergeSortWrapper(workingArray, n);
    cout << "Sorted array (by Roll No):\n";
    displayStudents(workingArray, n);
    cout << "Number of swaps performed: " << mergeSwapCount << endl;
    
    // 4. Quick Sort
    copyArray(originalArray, workingArray, n);
    cout << "\n4. Quick Sort:\n";
    quickSortWrapper(workingArray, n);
    cout << "Sorted array (by Roll No):\n";
    displayStudents(workingArray, n);
    cout << "Number of swaps performed: " << quickSwapCount << endl;
    
    // Free allocated memory
    delete[] originalArray;
    delete[] workingArray;
    
    return 0;
}
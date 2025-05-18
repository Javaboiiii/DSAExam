// 39.	Implement following problems based on Arrays. A. a. i/p- { 2,2,3,4} o/p: 1 b. i/p: {1,3,2,5,4,9}
//  o/p: 3 c. i/p: { 1,5,3,4,6,2,12} o/p: 5 B. Find saddle point in the Matrix. C. Magic square
//  Matrix. (Check) D. Represent given matrix in its Sparse form.

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <iomanip>

using namespace std;

// ==================== Problem A: Find missing numbers in arrays ====================

// Function to find the first missing positive integer
int findFirstMissingPositive(vector<int>& nums) {
    int n = nums.size();
    
    // Step 1: Convert all negative, zero, and out-of-range numbers to n+1
    for (int i = 0; i < n; i++) {
        if (nums[i] <= 0 || nums[i] > n) {
            nums[i] = n + 1;
        }
    }
    
    // Step 2: Mark numbers as visited by negating the value at the index
    for (int i = 0; i < n; i++) {
        int num = abs(nums[i]);
        if (num <= n) {
            nums[num - 1] = -abs(nums[num - 1]);
        }
    }
    
    // Step 3: Find the first positive index
    for (int i = 0; i < n; i++) {
        if (nums[i] > 0) {
            return i + 1;
        }
    }
    
    // If all numbers from 1 to n are present, return n+1
    return n + 1;
}

// Function to find the missing number in a sequence
int findMissingNumber(vector<int>& nums) {
    // For the specific case where we have a sequence with one missing number
    // Sort the array first
    sort(nums.begin(), nums.end());
    
    int start = nums[0];
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] != start + i) {
            return start + i;
        }
    }
    
    // If no missing number found, return the next expected number
    return nums.back() + 1;
}

// ==================== Problem B: Find saddle point in a matrix ====================

// Function to find saddle points in a matrix
// A saddle point is an element which is minimum in its row and maximum in its column
vector<pair<int, int>> findSaddlePoints(vector<vector<int>>& matrix) {
    int rows = matrix.size();
    if (rows == 0) return {};
    int cols = matrix[0].size();
    
    vector<pair<int, int>> saddlePoints;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // Check if current element is minimum in its row
            bool isMinInRow = true;
            for (int k = 0; k < cols; k++) {
                if (matrix[i][k] < matrix[i][j]) {
                    isMinInRow = false;
                    break;
                }
            }
            
            // Check if current element is maximum in its column
            bool isMaxInCol = true;
            for (int k = 0; k < rows; k++) {
                if (matrix[k][j] > matrix[i][j]) {
                    isMaxInCol = false;
                    break;
                }
            }
            
            // If both conditions are met, it's a saddle point
            if (isMinInRow && isMaxInCol) {
                saddlePoints.push_back({i, j});
            }
        }
    }
    
    return saddlePoints;
}

// ==================== Problem C: Check if a matrix is a magic square ====================

// Function to check if a matrix is a magic square
bool isMagicSquare(vector<vector<int>>& matrix) {
    int n = matrix.size();
    if (n == 0) return false;
    
    // Check if the matrix is square
    for (int i = 0; i < n; i++) {
        if (matrix[i].size() != n) return false;
    }
    
    // Calculate the expected sum (n * (n^2 + 1) / 2) / n = (n^2 + 1) / 2 * n
    int expectedSum = n * (n * n + 1) / 2;
    
    // Check rows
    for (int i = 0; i < n; i++) {
        int rowSum = 0;
        for (int j = 0; j < n; j++) {
            rowSum += matrix[i][j];
        }
        if (rowSum != expectedSum) return false;
    }
    
    // Check columns
    for (int j = 0; j < n; j++) {
        int colSum = 0;
        for (int i = 0; i < n; i++) {
            colSum += matrix[i][j];
        }
        if (colSum != expectedSum) return false;
    }
    
    // Check main diagonal
    int diagSum1 = 0;
    for (int i = 0; i < n; i++) {
        diagSum1 += matrix[i][i];
    }
    if (diagSum1 != expectedSum) return false;
    
    // Check anti-diagonal
    int diagSum2 = 0;
    for (int i = 0; i < n; i++) {
        diagSum2 += matrix[i][n - 1 - i];
    }
    if (diagSum2 != expectedSum) return false;
    
    // Check for duplicates (each number should be unique and from 1 to n^2)
    set<int> numSet;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // Check if the number is in the valid range
            if (matrix[i][j] < 1 || matrix[i][j] > n * n) return false;
            // Check for duplicates
            if (numSet.find(matrix[i][j]) != numSet.end()) return false;
            numSet.insert(matrix[i][j]);
        }
    }
    
    return true;
}

// ==================== Problem D: Represent a matrix in sparse form ====================

// Structure to represent a sparse matrix element
struct SparseElement {
    int row;
    int col;
    int value;
    
    SparseElement(int r, int c, int v) : row(r), col(c), value(v) {}
};

// Function to convert a matrix to sparse form
vector<SparseElement> convertToSparse(vector<vector<int>>& matrix) {
    vector<SparseElement> sparse;
    
    int rows = matrix.size();
    if (rows == 0) return sparse;
    int cols = matrix[0].size();
    
    // Count non-zero elements
    int nonZeroCount = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                nonZeroCount++;
                sparse.push_back(SparseElement(i, j, matrix[i][j]));
            }
        }
    }
    
    return sparse;
}

// Function to display a sparse matrix
void displaySparseMatrix(const vector<SparseElement>& sparse, int rows, int cols) {
    cout << "Sparse Matrix Representation:" << endl;
    cout << "Row\tColumn\tValue" << endl;
    cout << rows << "\t" << cols << "\t" << sparse.size() << endl; // Dimensions and count
    
    for (const auto& elem : sparse) {
        cout << elem.row << "\t" << elem.col << "\t" << elem.value << endl;
    }
}

// ==================== Main function ====================

int main() {
    int choice;
    
    do {
        cout << "\n===== Array Problems =====" << endl;
        cout << "1. Find missing number in an array" << endl;
        cout << "2. Find saddle point in a matrix" << endl;
        cout << "3. Check if a matrix is a magic square" << endl;
        cout << "4. Represent matrix in sparse form" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                int subChoice;
                cout << "\nSelect test case:" << endl;
                cout << "1. Array: {2,2,3,4} (Expected output: 1)" << endl;
                cout << "2. Array: {1,3,2,5,4,9} (Expected output: 6 or 7 or 8)" << endl;
                cout << "3. Array: {1,5,3,4,6,2,12} (Expected output: 7 or 8 or 9 or 10 or 11)" << endl;
                cout << "4. Enter custom array" << endl;
                cout << "Enter choice: ";
                cin >> subChoice;
                
                vector<int> nums;
                
                if (subChoice == 1) {
                    nums = {2, 2, 3, 4};
                } else if (subChoice == 2) {
                    nums = {1, 3, 2, 5, 4, 9};
                } else if (subChoice == 3) {
                    nums = {1, 5, 3, 4, 6, 2, 12};
                } else if (subChoice == 4) {
                    int n;
                    cout << "Enter number of elements: ";
                    cin >> n;
                    cout << "Enter array elements: ";
                    for (int i = 0; i < n; i++) {
                        int val;
                        cin >> val;
                        nums.push_back(val);
                    }
                } else {
                    cout << "Invalid choice!" << endl;
                    break;
                }
                
                cout << "Array: { ";
                for (int num : nums) {
                    cout << num << " ";
                }
                cout << "}" << endl;
                
                // First approach: Finding the first missing positive integer
                vector<int> numsCopy = nums;
                int missingPositive = findFirstMissingPositive(numsCopy);
                
                // Second approach: Finding the missing number in a sorted sequence
                int missingInSequence = findMissingNumber(nums);
                
                cout << "First missing positive integer: " << missingPositive << endl;
                cout << "Missing number (assuming sequence): " << missingInSequence << endl;
                break;
            }
            
            case 2: {
                int rows, cols;
                cout << "\nEnter dimensions of the matrix:" << endl;
                cout << "Rows: ";
                cin >> rows;
                cout << "Columns: ";
                cin >> cols;
                
                vector<vector<int>> matrix(rows, vector<int>(cols));
                
                cout << "Enter matrix elements:" << endl;
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        cout << "matrix[" << i << "][" << j << "]: ";
                        cin >> matrix[i][j];
                    }
                }
                
                cout << "\nMatrix:" << endl;
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        cout << setw(4) << matrix[i][j] << " ";
                    }
                    cout << endl;
                }
                
                vector<pair<int, int>> saddlePoints = findSaddlePoints(matrix);
                
                if (saddlePoints.empty()) {
                    cout << "No saddle points found in the matrix." << endl;
                } else {
                    cout << "Saddle points found at positions:" << endl;
                    for (auto& point : saddlePoints) {
                        cout << "(" << point.first << ", " << point.second << ") = " 
                             << matrix[point.first][point.second] << endl;
                    }
                }
                break;
            }
            
            case 3: {
                int n;
                cout << "\nEnter the size of the square matrix: ";
                cin >> n;
                
                vector<vector<int>> matrix(n, vector<int>(n));
                
                cout << "Enter matrix elements:" << endl;
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        cout << "matrix[" << i << "][" << j << "]: ";
                        cin >> matrix[i][j];
                    }
                }
                
                cout << "\nMatrix:" << endl;
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        cout << setw(4) << matrix[i][j] << " ";
                    }
                    cout << endl;
                }
                
                if (isMagicSquare(matrix)) {
                    cout << "The matrix is a magic square!" << endl;
                    cout << "Magic constant: " << n * (n*n + 1) / 2 << endl;
                } else {
                    cout << "The matrix is NOT a magic square." << endl;
                }
                break;
            }
            
            case 4: {
                int rows, cols;
                cout << "\nEnter dimensions of the matrix:" << endl;
                cout << "Rows: ";
                cin >> rows;
                cout << "Columns: ";
                cin >> cols;
                
                vector<vector<int>> matrix(rows, vector<int>(cols));
                
                cout << "Enter matrix elements:" << endl;
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        cout << "matrix[" << i << "][" << j << "]: ";
                        cin >> matrix[i][j];
                    }
                }
                
                cout << "\nOriginal Matrix:" << endl;
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        cout << setw(4) << matrix[i][j] << " ";
                    }
                    cout << endl;
                }
                
                vector<SparseElement> sparse = convertToSparse(matrix);
                displaySparseMatrix(sparse, rows, cols);
                
                break;
            }
            
            case 0:
                cout << "Exiting program. Goodbye!" << endl;
                break;
                
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
        
    } while (choice != 0);
    
    return 0;
}
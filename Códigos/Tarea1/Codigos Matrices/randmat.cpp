#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to generate a random matrix with specific rows and columns
vector<vector<int>> generateRandomMatrix(int rows, int cols, int minValue, int maxValue) {
    vector<vector<int>> matrix(rows, vector<int>(cols));
    
    // Seed for random number generation
    srand(static_cast<unsigned>(time(0)));
    
    // Fill the matrix with random values
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = minValue + rand() % (maxValue - minValue + 1);
        }
    }
    
    return matrix;
}

// Function to print the matrix
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int value : row) {
            cout << value << ' ';
        }
        cout << endl;
    }
}

int main() {
    int rows, cols, minValue, maxValue;

    cout << "Enter the number of rows of the matrix: ";
    cin >> rows;
    cout << "Enter the number of columns of the matrix: ";
    cin >> cols;
    cout << "Enter the minimum value for the matrix elements: ";
    cin >> minValue;
    cout << "Enter the maximum value for the matrix elements: ";
    cin >> maxValue;
    
    // Generate and print the random matrix
    vector<vector<int>> matrix = generateRandomMatrix(rows, cols, minValue, maxValue);
    
    cout << "Random " << rows << "x" << cols << " matrix:" << endl;
    printMatrix(matrix);

    return 0;
}

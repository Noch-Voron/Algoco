#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

// Function to generate a random matrix with specific rows and columns
vector<vector<long long>> generateRandomMatrix(int rows, int cols, int minValue, int maxValue) {
    vector<vector<long long>> matrix(rows, vector<long long>(cols));
    
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

// Function to multiply two matrices A and B
vector<vector<long long>> multiplicarMatrices(const vector<vector<long long>>& A, const vector<vector<long long>>& B) {
    int filasA = A.size();          // Number of rows of A
    int columnasA = A[0].size();    // Number of columns of A
    int filasB = B.size();          // Number of rows of B
    int columnasB = B[0].size();    // Number of columns of B

    // Check if matrices can be multiplied
    if (columnasA != filasB) {
        throw invalid_argument("The number of columns of the first matrix must be equal to the number of rows of the second matrix.");
    }

    // Create result matrix with the number of rows of A and the number of columns of B
    vector<vector<long long>> C(filasA, vector<long long>(columnasB, 0));

    // Matrix multiplication algorithm
    for (int i = 0; i < filasA; i++) {            // Iterate over rows of A
        for (int j = 0; j < columnasB; j++) {    // Iterate over columns of B
            for (int k = 0; k < columnasA; k++) { // Iterate over columns of A (and rows of B)
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

int main() {
    // Sizes for testing
    vector<int> sizes = {128, 256, 512, 1024, 2048, 4096}; // Adjust these sizes as needed

    for (int n : sizes) {
        // Example of rectangular matrices
        vector<vector<long long>> A = generateRandomMatrix(n, n, 0, 100);
        vector<vector<long long>> B = generateRandomMatrix(n, n, 0, 100);

        cout << "Testing with " << n << "x" << n << " matrices..." << endl;
        auto start = chrono::high_resolution_clock::now();

        try {
            vector<vector<long long>> C = multiplicarMatrices(A, B);
            cout << "Multiplication completed successfully.\n";
        } catch (const invalid_argument& e) {
            cerr << "Error: " << e.what() << endl;
        }

        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        cout << "Elapsed time: " << elapsed.count() << " seconds\n";
    }

    return 0;
}

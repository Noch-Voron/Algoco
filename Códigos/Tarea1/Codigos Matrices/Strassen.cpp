#include <iostream>
#include <vector>
#include <chrono>
#include <stdexcept>

using namespace std;

vector<vector<long long>> generateRandomMatrix(int rows, int cols, int minVal, int maxVal) {
    vector<vector<long long>> matrix(rows, vector<long long>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = minVal + rand() % (maxVal - minVal + 1);
        }
    }
    return matrix;
}

vector<vector<long long>> multiplicarMatrices(const vector<vector<long long>>& A, const vector<vector<long long>>& B) {
    // Placeholder implementation for matrix multiplication
    int n = A.size();
    vector<vector<long long>> C(n, vector<long long>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

int main() {
    vector<int> sizes = {128, 256, 512, 1024, 2048, 4096}; // Example sizes

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

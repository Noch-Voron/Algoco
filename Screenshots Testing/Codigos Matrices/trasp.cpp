#include <iostream>
#include <vector>
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
// Función para trasponer una matriz
vector<vector<int>> trasponerMatriz(const vector<vector<int>>& matriz) {
    int n = matriz.size();
    vector<vector<int>> transpuesta(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            transpuesta[j][i] = matriz[i][j];
        }
    }
    return transpuesta;
}

// Función para multiplicar dos matrices A y B (B está traspuesta)
vector<vector<long long>> multiplicarMatricesOpt(const vector<vector<long long>>& A, const vector<vector<long long>>& B) {
    int n = A.size(); // Asumiendo que A y B son matrices cuadradas de tamaño n x n
    vector<vector<long long>> C(n, vector<long long>(n, 0)); // Matriz de resultados inicializada en 0

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int suma = 0;
            for (int k = 0; k < n; k++) {
                suma += A[i][k] * B[j][k]; // Nota: ahora B[j][k] accede a una fila de B traspuesta
            }
            C[i][j] = suma;
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
            vector<vector<long long>> C = multiplicarMatricesOpt(A, B);
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

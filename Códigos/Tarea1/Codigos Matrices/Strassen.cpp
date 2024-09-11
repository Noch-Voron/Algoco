#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef vector<vector<long long>> Matrix;

// Función para sumar matrices
Matrix add(const Matrix &A, const Matrix &B) {
    int n = A.size();
    Matrix C(n, vector<long long>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

// Función para restar matrices
Matrix subtract(const Matrix &A, const Matrix &B) {
    int n = A.size();
    Matrix C(n, vector<long long>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

// Función recursiva para multiplicar matrices utilizando el algoritmo de Strassen
Matrix strassen(const Matrix &A, const Matrix &B) {
    int n = A.size();
    if (n == 1) {
        Matrix C(1, vector<long long>(1));
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    int newSize = n / 2;
    //submatrices nuevas
    Matrix A11(newSize, vector<long long>(newSize));
    Matrix A12(newSize, vector<long long>(newSize));
    Matrix A21(newSize, vector<long long>(newSize));
    Matrix A22(newSize, vector<long long>(newSize));
    Matrix B11(newSize, vector<long long>(newSize));
    Matrix B12(newSize, vector<long long>(newSize));
    Matrix B21(newSize, vector<long long>(newSize));
    Matrix B22(newSize, vector<long long>(newSize));

    // Dividir A y B en 4 submatrices
    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }
    //aquí está toda la magia, ni idea de como se le ocurrió pero aca es :')
    Matrix M1 = strassen(add(A11, A22), add(B11, B22));
    Matrix M2 = strassen(add(A21, A22), B11);
    Matrix M3 = strassen(A11, subtract(B12, B22));
    Matrix M4 = strassen(A22, subtract(B21, B11));
    Matrix M5 = strassen(add(A11, A12), B22);
    Matrix M6 = strassen(subtract(A21, A11), add(B11, B12));
    Matrix M7 = strassen(subtract(A12, A22), add(B21, B22));

    //submatrices finales
    Matrix C11 = add(subtract(add(M1, M4), M5), M7);
    Matrix C12 = add(M3, M5);
    Matrix C21 = add(M2, M4);
    Matrix C22 = add(subtract(add(M1, M3), M2), M6);
    //fin
    Matrix C(n, vector<long long>(n));
    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }
    return C;
}

// Función para imprimir matrices
void printMatrix(const Matrix &M) {
    for (const auto &row : M) {
        for (long long elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }
}

// Función para generar una matriz aleatoria con filas y columnas específicas
vector<vector<long long>> generateRandomMatrix(int rows, int cols, int minValue, int maxValue) {
    vector<vector<long long>> matrix(rows, vector<long long>(cols));
    
    // Semilla para la generación de números aleatorios
    srand(static_cast<unsigned>(time(0)));
    
    // Rellenar la matriz con valores aleatorios
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = minValue + rand() % (maxValue - minValue + 1);
        }
    }
    
    return matrix;
}

int main() {
    // Tamaños para las pruebas
    vector<int> sizes = {2048}; // Ajustar estos tamaños según sea necesario

    for (int n : sizes) {
        // Ejemplo de matrices cuadradas
        Matrix A = generateRandomMatrix(n, n, 0, 100);
        Matrix B = generateRandomMatrix(n, n, 0, 100);

        cout << "Testing with " << n << "x" << n << " matrices..." << endl;
        auto start = chrono::high_resolution_clock::now();

        Matrix C = strassen(A, B);
        
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        cout << "Elapsed time: " << elapsed.count() << " seconds\n";
    }

    return 0;
}

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

// Función para generar una matriz aleatoria con un número específico de filas y columnas
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

// Función para multiplicar dos matrices A y B
vector<vector<long long>> multiplicarMatrices(const vector<vector<long long>>& A, const vector<vector<long long>>& B) {
    int filasA = A.size();          // Número de filas de A
    int columnasA = A[0].size();    // Número de columnas de A
    int filasB = B.size();          // Número de filas de B
    int columnasB = B[0].size();    // Número de columnas de B

    // Verificar si las matrices se pueden multiplicar
    if (columnasA != filasB) {
        throw invalid_argument("El número de columnas de la primera matriz debe ser igual al número de filas de la segunda matriz.");
    }

    // Crear la matriz resultado con el número de filas de A y el número de columnas de B
    vector<vector<long long>> C(filasA, vector<long long>(columnasB, 0));

    // Algoritmo de multiplicación de matrices
    for (int i = 0; i < filasA; i++) {            // Iterar sobre las filas de A
        for (int j = 0; j < columnasB; j++) {     // Iterar sobre las columnas de B
            for (int k = 0; k < columnasA; k++) { // Iterar sobre las columnas de A (y filas de B)
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

int main() {
    // Tamaños para probar
    vector<int> sizes = {128, 256, 512, 1024, 2048, 4096}; // Ajusta estos tamaños según sea necesario

    for (int n : sizes) {//para cada tamaño diferente
        //se generan las matrices a multiplicar
        vector<vector<long long>> A = generateRandomMatrix(n, n, 0, 100);
        vector<vector<long long>> B = generateRandomMatrix(n, n, 0, 100);

        
        cout << "Probando con matrices de " << n << "x" << n << "..." << endl;
        auto start = chrono::high_resolution_clock::now();//se comienza a contar

        try {//para evitar que muera :)
            vector<vector<long long>> C = multiplicarMatrices(A, B);//se multiplican las matrices. longlong en caso de numeros muy grandes :)))
            cout << "Multiplicación completada exitosamente.\n";
        } catch (const invalid_argument& e) {
            cerr << "Error: " << e.what() << endl;
        }

        auto end = chrono::high_resolution_clock::now();// se deja de tomar el tiempo, no considero que el tiempo que toma en los print sea relevante.
        chrono::duration<double> elapsed = end - start;
        cout << "Tiempo transcurrido: " << elapsed.count() << " segundos\n";//misma cosa de los algoritmos de ordenamiento, se printea el tiempo que demoró.
    }

    return 0;
}

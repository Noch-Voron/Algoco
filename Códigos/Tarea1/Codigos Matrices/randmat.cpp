#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Función para generar una matriz aleatoria con un número específico de filas y columnas
vector<vector<int>> generateRandomMatrix(int rows, int cols, int minValue, int maxValue) {
    vector<vector<int>> matrix(rows, vector<int>(cols));
    
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

// Función para imprimir la matriz
void printMatrix(const vector<vector<int>>& matrix) {
    // Iterar por cada fila de la matriz
    for (const auto& row : matrix) {
        // Imprimir cada valor de la fila
        for (int value : row) {
            cout << value << ' ';
        }
        cout << endl;
    }
}

int main() {
    int rows, cols, minValue, maxValue;

    // Solicitar el número de filas, columnas y rango de valores
    cout << "Ingrese el número de filas de la matriz: ";
    cin >> rows;
    cout << "Ingrese el número de columnas de la matriz: ";
    cin >> cols;
    cout << "Ingrese el valor mínimo para los elementos de la matriz: ";
    cin >> minValue;
    cout << "Ingrese el valor máximo para los elementos de la matriz: ";
    cin >> maxValue;
    
    // Generar e imprimir la matriz aleatoria
    vector<vector<int>> matrix = generateRandomMatrix(rows, cols, minValue, maxValue);
    
    cout << "Matriz aleatoria de " << rows << "x" << cols << ":" << endl;
    printMatrix(matrix);

    return 0;
}


#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <vector>
#include <chrono>
#include <functional>

// Función para medir el tiempo de ejecución de un algoritmo de ordenamiento
double medirTiempoEjecucion(std::vector<int>& datos, std::function<void(std::vector<int>&)> algoritmo) {
    auto inicio = std::chrono::high_resolution_clock::now();
    algoritmo(datos);  // Ejecutar el algoritmo de ordenamiento
    auto fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracion = fin - inicio;
    return duracion.count();  // Devolver el tiempo en segundos
}

// Función para generar un archivo de datos desordenados
void generarArchivo(std::string nombreArchivo, int N, double porcentajeDesorden) {
    std::vector<int> numeros(N);
    for (int i = 0; i < N; ++i) {
        numeros[i] = i + 1;  // Generar números ordenados del 1 a N
    }

    // Calcular cuántos elementos deben estar desordenados
    int numDesordenados = N * porcentajeDesorden;

    // Desordenar solo el porcentaje especificado
    std::shuffle(numeros.begin(), numeros.begin() + numDesordenados, std::default_random_engine());

    // Guardar en el archivo
    std::ofstream archivo(nombreArchivo);
    for (int num : numeros) {
        archivo << num << "\n";
    }
    archivo.close();
}

void ejecutarPruebas(int numEjecuciones, std::function<void(std::vector<int>&)> algoritmo, const std::string& nombreAlgoritmo) {
    int tamanos[] = {1000, 100000, 1000000};
    double porcentajesDesorden[] = {0.0, 0.40, 0.75, 1.0};

    for (int N : tamanos) {
        for (double porcentajeDesorden : porcentajesDesorden) {
            double tiempoTotal = 0;

            for (int i = 0; i < numEjecuciones; ++i) {
                std::string nombreArchivo = "datos_" + nombreAlgoritmo + "_" + std::to_string(N) + "_" 
                    + std::to_string(porcentajeDesorden * 100) + "_iteracion_" + std::to_string(i+1) + ".txt";
                
                generarArchivo(nombreArchivo, N, porcentajeDesorden);

                std::vector<int> datos;
                std::ifstream archivo(nombreArchivo);

                // Leer los datos del archivo
                int valor;
                while (archivo >> valor) {
                    datos.push_back(valor);
                }
                archivo.close();

                tiempoTotal += medirTiempoEjecucion(datos, algoritmo);
                
                // Eliminar el archivo después de la ejecución
                if (remove(nombreArchivo.c_str()) != 0) {
                    std::cerr << "Error eliminando el archivo: " << nombreArchivo << std::endl;
                }
            }

            double tiempoPromedio = tiempoTotal / numEjecuciones;
            std::cout << nombreAlgoritmo << " - Promedio para " << N << " elementos (" << porcentajeDesorden * 100 
                      << "% desordenado): " << tiempoPromedio << " segundos\n";
        }
    }
}

// Implementación de Selection Sort
void selectionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx])
                minIdx = j;
        }
        std::swap(arr[minIdx], arr[i]);
    }
}

// Implementación de QuickSort
int medianOfThree(std::vector<int>& arr, int low, int high) {
    int mid = low + (high - low) / 2;
    if (arr[mid] < arr[low])
        std::swap(arr[low], arr[mid]);
    if (arr[high] < arr[low])
        std::swap(arr[low], arr[high]);
    if (arr[high] < arr[mid])
        std::swap(arr[mid], arr[high]);
    return mid;
}

int partition(std::vector<int>& arr, int low, int high) {
    int pivotIndex = medianOfThree(arr, low, high);
    std::swap(arr[pivotIndex], arr[high]);
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Implementación de MergeSort
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

int main() {
    int numEjecuciones = 10;

    // Adaptar QuickSort para que funcione con la firma del std::function<void(std::vector<int>&)>
    auto quickSortLambda = [](std::vector<int>& arr) {
        quickSort(arr, 0, arr.size() - 1);
    };

    // Adaptar MergeSort de manera similar
    auto mergeSortLambda = [](std::vector<int>& arr) {
        mergeSort(arr, 0, arr.size() - 1);
    };

    // Ejecutar pruebas para cada algoritmo
    ejecutarPruebas(numEjecuciones, quickSortLambda, "quicksort");
    ejecutarPruebas(numEjecuciones, mergeSortLambda, "mergesort");
    ejecutarPruebas(numEjecuciones, selectionSort, "selectionsort");

    return 0;
}

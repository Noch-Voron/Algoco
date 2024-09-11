#include <bits/stdc++.h>
using namespace std;

// Función para combinar dos subarreglos de arr[]
// El subarreglo izquierdo es arr[left..mid]
// El subarreglo derecho es arr[mid+1..right]
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1; // tamaño del subarreglo izquierdo
    int n2 = right - mid;    // tamaño del subarreglo derecho

    // Se crean arreglos temporales para los subarreglos izquierdo y derecho
    std::vector<int> L(n1), R(n2);

    // Copiar los datos al subarreglo izquierdo L[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    // Copiar los datos al subarreglo derecho R[]
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0; // índices iniciales para los subarreglos izquierdo y derecho
    int k = left;     // índice inicial del subarreglo combinado

    // Combinar los subarreglos en orden
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {  // si el elemento en L es menor o igual que el de R
            arr[k] = L[i];   // se coloca L[i] en la posición k del arreglo original
            i++;             // se incrementa el índice del subarreglo izquierdo
        } else {
            arr[k] = R[j];   // si el elemento en R es menor, se coloca en el arreglo original
            j++;             // se incrementa el índice del subarreglo derecho
        }
        k++; // se avanza al siguiente elemento del arreglo combinado
    }

    // Copiar los elementos restantes del subarreglo izquierdo, si quedan
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copiar los elementos restantes del subarreglo derecho, si quedan
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Función recursiva de MergeSort
// Divide el arreglo en dos subarreglos, los ordena y luego los combina
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left >= right) // caso base: si el subarreglo tiene un solo elemento, está ordenado
        return;

    int mid = left + (right - left) / 2; // calcular el punto medio del subarreglo
    mergeSort(arr, left, mid);           // ordenar la primera mitad
    mergeSort(arr, mid + 1, right);      // ordenar la segunda mitad
    merge(arr, left, mid, right);        // combinar las dos mitades ordenadas
}

// Driver code
int main()
{
    std::vector<int> numbers;
    std::string line;
    std::ifstream inFile("sh.txt");//modificable

    //lee el archivo
    if (inFile.is_open()) {
        while (std::getline(inFile, line)) {
            numbers.push_back(std::stoi(line));
        }
        inFile.close();
    } 
    cout << "Starting Sort...\n";
    auto start = std::chrono::high_resolution_clock::now();
    mergeSort(numbers, 0, numbers.size() - 1);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds\n";
    return 0;
}

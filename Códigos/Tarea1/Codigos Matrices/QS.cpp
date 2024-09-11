#include <bits/stdc++.h>
using namespace std;

// Implementación la tecnica de la tercera mediana
int medianOfThree(std::vector<int>& arr, int low, int high) {
    int mid = low + (high - low) / 2;// se toma el indice del medio como mid.
    //se realizan intercambios para ordenar de menor a mayor el numero del inicio, del final y del vector
    //ej, si tenemos [4,6,9,7,1] terminamos con [1,6,4,7,9]
    if (arr[mid] < arr[low])
        std::swap(arr[low], arr[mid]);
    if (arr[high] < arr[low])
        std::swap(arr[low], arr[high]);
    if (arr[high] < arr[mid])
        std::swap(arr[mid], arr[high]);
    //se retorna el valor del medio luego de realizar los intercambios
    return mid;
}

//Funcion de particionamiento para QuickSort, toma el vector, el indice menor (dado) y el índice mayor (also dado) 
int partition(std::vector<int>& arr, int low, int high) {
    int pivotIndex = medianOfThree(arr, low, high); // se usa la técnica de las tres medianas para elegir un pivote adecuado
    std::swap(arr[pivotIndex], arr[high]); // se mueve el pivote al final del vector para facilitar la partición
    int pivot = arr[high]; // se define el pivote
    int i = (low - 1); // índice del elemento más pequeño

    // se recorre el subarreglo desde 'low' hasta 'high - 1'
    for (int j = low; j <= high - 1; j++) {
        // si el elemento actual es menor o igual al pivote, se intercambia con el elemento en la posición 'i + 1'
        if (arr[j] <= pivot) {
            i++; // se incrementa el índice de los elementos más pequeños
            std::swap(arr[i], arr[j]); // se intercambia el elemento menor con el actual
        }
    }
    std::swap(arr[i + 1], arr[high]); // se coloca el pivote en su posición correcta
    return (i + 1); // se retorna la posición del pivote
}
//Implementacion QuickSort
//toma el arreglo como referencia, para no usar nueva memoria.
void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {//condición para terminar la recursividad
        int pi = partition(arr, low, high);//se particiona el vector
        
        //se utiliza recursividad para ordenar todo el vector.
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
// Driver program to test above functions
int main()
{
    vector<int> arr;
    string line;
    ifstream inFile("par.txt");

    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            // Convert the line to an integer and add it to the vector
            arr.push_back(stoi(line));
        }
        inFile.close();
    } 
    int n = arr.size();
    cout << "Starting Sort...\n";

    auto start = std::chrono::high_resolution_clock::now();

    quickSort(arr, 0, n - 1);

    auto end = std::chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "Elapsed time: " << elapsed.count() << " seconds\n";

    return 0;
}
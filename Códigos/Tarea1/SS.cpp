#include <bits/stdc++.h>
using namespace std;

// Implementación de Selection Sort (sacada de geeksforgeeks y adaptada para vectores)
void selectionSort(std::vector<int>& arr) {
    int n = arr.size();
    //doble for anidado, complejidad O(n^2)
    for (int i = 0; i < n - 1; i++) {//se recorre todo el vector
        int minIdx = i;//numero actual se considera como el menor.
        for (int j = i + 1; j < n; j++) {//por cada numero, se revisa el resto del vector hacia la derecha
            if (arr[j] < arr[minIdx])//si el numero actual es menor que el menor actual 
                minIdx = j;//se sobre-escribe el indice del numero menor.
        }
        std::swap(arr[minIdx], arr[i]);//se intercambia el numero menor con el de la posicion i (del primer for)
    }
}

int main() {
    std::vector<int> numbers;
    std::string line;
    std::ifstream inFile("org++.txt");

    //lee el archivo y guarda numeros en vector numbers
    if (inFile.is_open()) {
        while (std::getline(inFile, line)) {
            numbers.push_back(std::stoi(line));
        }
        inFile.close();
    } 
    
    cout << "Starting Sort...\n";

    auto start = std::chrono::high_resolution_clock::now();

    selectionSort(numbers);//ejecucion algoritmo

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds\n";



    return 0;
}

#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <vector>
#include <chrono>
#include <functional>

// Función para medir el tiempo de ejecución de un algoritmo de ordenamiento
double medirTiempoEjecucion(std::vector<int>& datos, std::function<void(std::vector<int>&)> algoritmo) {
    auto inicio = std::chrono::high_resolution_clock::now(); // Se comienza a tomar el tiempo
    algoritmo(datos);  // Ejecutar el algoritmo de ordenamiento
    auto fin = std::chrono::high_resolution_clock::now(); // se deja de tomar el tiempo
    std::chrono::duration<double> duracion = fin - inicio; // se calcula la duracion
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

//Funcion para ejecutar un algoritmo específico para probar para cada tamaño y sus diferentes posibles porcentajes de desorden
void ejecutarPruebas(int numEjecuciones, std::function<void(std::vector<int>&)> algoritmo, const std::string& nombreAlgoritmo) {
    int tamanos[] = {1000, 100000, 1000000};
    double porcentajesDesorden[] = {0.0, 0.40, 0.75, 1.0};
    //si se quita o se agrega alguno elemento de estas dos listas no estoy seguro de que es lo que ocurra
    //probablemente se ejecutan más o menos iteraciones dependiendo de si se añade o se quitan elementos.


    for (int N : tamanos) {
        //Para cada tamaño
        for (double porcentajeDesorden : porcentajesDesorden) {
            //Se itera para los porcentajes de desorden
            double tiempoTotal = 0;

            for (int i = 0; i < numEjecuciones    ; ++i) {
                //se ejecuta el algorimo ^^esta^^ cantidad de veces

                //se hacen archivos para cada iteracion. 
                std::string nombreArchivo = "datos_" + nombreAlgoritmo + "_" + std::to_string(N) + "_" 
                    + std::to_string(porcentajeDesorden * 100) + "_iteracion_" + std::to_string(i+1) + ".txt";
                //generacion de archivo
                generarArchivo(nombreArchivo, N, porcentajeDesorden);

                std::vector<int> datos;//definicion de vector que contendrá los numeros desordenados
                std::ifstream archivo(nombreArchivo);//se abre el archivo que tiene los numeros desordenados

                // Leer los datos del archivo
                int valor;
                while (archivo >> valor) {
                    datos.push_back(valor);
                }
                archivo.close();

                //tiempo total en todas las iteraciones del algoritmo
                tiempoTotal += medirTiempoEjecucion(datos, algoritmo);
                
                // Eliminar el archivo después de la ejecución
                if (remove(nombreArchivo.c_str()) != 0) {
                    std::cerr << "Error eliminando el archivo: " << nombreArchivo << std::endl;
                }
            }
            //se calcula el tiempo promedio y se imprime para ver resultados
            double tiempoPromedio = tiempoTotal / numEjecuciones;
            std::cout << nombreAlgoritmo << " - Promedio para " << N << " elementos (" << porcentajeDesorden * 100 
                      << "% desordenado): " << tiempoPromedio << " segundos\n";
            //recordar que esto ocurre, en este caso particular 3 (tamaños) * 4 (porcentajes desorden) = 12 veces, el mostrado en el screenshot no incluye
            //las iteraciones de 1 millon de numeros para el selection sort, mucho rato
        }
    }
}

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


int main() {
    int numEjecuciones = 10;//se puede cambiar para calcular un promedio de más o menos ejecuciones

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
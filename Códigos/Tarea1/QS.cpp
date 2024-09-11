#include <bits/stdc++.h>
using namespace std;

/* This function takes the last element as pivot, places
   the pivot element at its correct position in sorted
   array, and places all smaller (smaller than pivot)
   to the left of the pivot and all greater elements 
   to the right  of the pivot */
int medianOfThree(vector<int>& arr, int low, int high) {
    int mid = low + (high - low) / 2;
    if (arr[mid] < arr[low])
        swap(arr[low], arr[mid]);
    if (arr[high] < arr[low])
        swap(arr[low], arr[high]);
    if (arr[high] < arr[mid])
        swap(arr[mid], arr[high]);
    return mid;
}

int partition(vector<int>& arr, int low, int high)
{
    
    int pivotIndex = medianOfThree(arr, low, high);
    swap(arr[pivotIndex], arr[high]);
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}
/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quickSort(vector<int>& arr, int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
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
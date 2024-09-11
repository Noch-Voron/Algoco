#include <bits/stdc++.h>
using namespace std;

void selectionSort(std::vector<int>& vec)
{
    int n = vec.size(); // Get the size of the vector

    for (int i = 0; i < n - 1; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (vec[j] < vec[min_idx])
                min_idx = j;
        }

        if (min_idx != i)
            std::swap(vec[min_idx], vec[i]); // Use std::swap for swapping
    }
}

void printArray(vector<int> vec, int n)
{
    for(int i = 0; i < n; i++)
        cout << vec[i] << " ";
    cout << endl;
}

int main() {
    std::vector<int> numbers;
    std::string line;
    std::ifstream inFile("org++.txt");

    if (inFile.is_open()) {
        while (std::getline(inFile, line)) {
            // Convert the line to an integer and add it to the vector
            numbers.push_back(std::stoi(line));
        }
        inFile.close();
    } 
    
    cout << "Starting Sort...\n";

    auto start = std::chrono::high_resolution_clock::now();

    selectionSort(numbers);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds\n";



    return 0;
}
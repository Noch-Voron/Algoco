#include <bits/stdc++.h>
using namespace std;

void printArray(vector<int> vec, int n)
{
    for(int i = 0; i < n; i++)
        cout << vec[i] << " ";
    cout << endl;
}

int main() {
    std::vector<int> numbers;
    std::string line;
    std::ifstream inFile("or.txt");

    if (inFile.is_open()) {
        while (std::getline(inFile, line)) {
            // Convert the line to an integer and add it to the vector
            numbers.push_back(std::stoi(line));
        }
        inFile.close();
    } 
    
    cout << "Starting Sort...\n";

    auto start = std::chrono::high_resolution_clock::now();

    sort(numbers.begin(), numbers.end());

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds\n";


    return 0;
}
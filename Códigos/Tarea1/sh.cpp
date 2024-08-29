#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

int main() {
    int N = 1000;
    

    // Generate a vector with numbers from 1 to N
    std::vector<int> numbers(N);
    for(int i = 0; i < N; ++i) {
        numbers[i] = i + 1;
    }

    // Shuffle the numbers
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(numbers.begin(), numbers.end(), g);

    // Write the shuffled numbers to a file
    std::ofstream outFile("sh.txt");
    if (outFile.is_open()) {
        for(const int &num : numbers) {
            outFile << num << "\n";
        }
        outFile.close();
        std::cout << "File generated successfully.";
    } else {
        std::cerr << "Error: Could not open the file.\n";
    }

    return 0;
}

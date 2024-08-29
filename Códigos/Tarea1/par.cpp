#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>

void partly_shuffle(std::vector<int>& vec, int n, double shuffle_ratio) {
    int shuffle_count = n * shuffle_ratio; // Number of elements to shuffle
    int start_idx = rand() % (n - shuffle_count); // Random start index for shuffling

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(vec.begin() + start_idx, vec.begin() + start_idx + shuffle_count, g);
}

int main() {
    int n = 1000; // number of elements
    double shuffle_ratio = 0.4; // from 0.0 to 1.0

    

    std::vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        numbers[i] = i + 1;
    }

    partly_shuffle(numbers, n, shuffle_ratio);

    std::ofstream outfile("par.txt");
    if (outfile.is_open()) {
        for (const int& num : numbers) {
            outfile << num << std::endl;
        }
        outfile.close();
        std::cout << "File generated successfully." << std::endl;
    } else {
        std::cerr << "Error opening file for writing!" << std::endl;
    }

    return 0;
}

#include <iostream>
#include <fstream>
#include <vector>

int main() {
    int n = 1000;

    std::vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        numbers[i] = i + 1;
    }

    std::ofstream outfile("or.txt");
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

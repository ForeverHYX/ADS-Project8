#include <iostream>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <vector>
#include "include/SkipList.hpp"

// Test insert operation
void testInsert(SkipList& skipList, int numElements, std::ofstream& outputFile) {
    for (int t = 0; t < 10; ++t) {
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < numElements; ++i) {
            skipList.insert(rand() % (numElements * 10));
        }
        auto end = std::chrono::high_resolution_clock::now();
        outputFile << "Insert," << numElements << "," << t + 1 << "," << std::chrono::duration<double, std::milli>(end - start).count() / numElements << std::endl;
    }
}

// Test search operation
void testSearch(SkipList& skipList, int numElements, std::ofstream& outputFile) {
    for (int t = 0; t < 10; ++t) {
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < numElements; ++i) {
            skipList.search(rand() % (numElements * 10));
        }
        auto end = std::chrono::high_resolution_clock::now();
        outputFile << "Search," << numElements << "," << t + 1 << "," << std::chrono::duration<double, std::milli>(end - start).count() / numElements << std::endl;
    }
}

// Test delete operation
void testDelete(SkipList& skipList, int numElements, std::ofstream& outputFile) {
    for (int t = 0; t < 10; ++t) {
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < numElements; ++i) {
            skipList.deleteValue(rand() % (numElements * 10));
        }
        auto end = std::chrono::high_resolution_clock::now();
        outputFile << "Delete," << numElements << "," << t + 1 << "," << std::chrono::duration<double, std::milli>(end - start).count() / numElements << std::endl;
    }
}

// Run tests for different sizes
void runTests(const std::vector<int>& testSizes, const std::string& outputFileName) {
    std::ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening output file!" << std::endl;
        return;
    }

    outputFile << "Operation,Size,TestNumber,Time(ms)" << std::endl;

    for (int size : testSizes) {
        std::cout << "\nRunning tests for " << size << " elements:" << std::endl;
        SkipList skipList;

        // Run operations
        testInsert(skipList, size, outputFile);
        testSearch(skipList, size, outputFile);
        testDelete(skipList, size, outputFile);
    }

    outputFile.close();
}

int main() {
    std::vector<int> testSizes = {1000, 5000, 10000, 50000, 100000, 500000, 1000000};
    std::string outputFileName = "skiplist_performance.csv";

    runTests(testSizes, outputFileName);
    std::cout << "Testing completed. Results saved to " << outputFileName << std::endl;

    return 0;
}

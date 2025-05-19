#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include "file_utils.h"

const int NUM_THREADS = 4;

int main() {
    std::string inputFile = "input.txt";

    // Read entire input file
    std::ifstream in(inputFile, std::ios::binary);
    if (!in) {
        std::cerr << "Failed to open input file: " << inputFile << std::endl;
        return 1;
    }

    std::vector<char> buffer((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    in.close();

    size_t totalSize = buffer.size();
    size_t chunkSize = (totalSize + NUM_THREADS - 1) / NUM_THREADS;

    std::vector<std::thread> threads;
    for (int i = 0; i < NUM_THREADS; ++i) {
        size_t start = i * chunkSize;
        size_t end = std::min(start + chunkSize, totalSize);
        if (start >= end) break;

        std::string chunkFile = "chunk_" + std::to_string(i) + ".bin";
        std::ofstream chunkOut(chunkFile, std::ios::binary);
        chunkOut.write(&buffer[start], end - start);
        chunkOut.close();

        threads.emplace_back([chunkFile, i]() {
            std::string compressedFile = "compressed_chunk_" + std::to_string(i) + ".rle";
            compressRLE(chunkFile, compressedFile);
        });
    }

    for (auto& t : threads) t.join();

    std::cout << "Multithreaded compression completed.\n";
    return 0;
}

#include <iostream>
#include <thread>
#include <vector>
#include "file_utils.h"

const int NUM_THREADS = 4;

int main() {
    std::vector<std::thread> threads;

    for (int i = 0; i < NUM_THREADS; ++i) {
        threads.emplace_back([i]() {
            std::string compressedFile = "compressed_chunk_" + std::to_string(i) + ".rle";
            std::string decompressedFile = "decompressed_chunk_" + std::to_string(i) + ".bin";

            if (decompressRLE(compressedFile, decompressedFile)) {
                std::cout << "Decompressed chunk " << i << " successfully.\n";
            } else {
                std::cerr << "Failed to decompress chunk " << i << ".\n";
            }
        });
    }

    for (auto& t : threads) t.join();

    std::cout << "Multithreaded decompression completed.\n";
    return 0;
}

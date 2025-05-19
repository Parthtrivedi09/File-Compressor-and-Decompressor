#include <iostream>
#include <fstream>
#include <vector>

const int NUM_THREADS = 4;

int main() {
    std::string outputFile = "final_decompressed.txt";
    std::ofstream out(outputFile, std::ios::binary);
    if (!out) {
        std::cerr << "Failed to open final output file.\n";
        return 1;
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        std::string chunkFile = "decompressed_chunk_" + std::to_string(i) + ".bin";
        std::ifstream in(chunkFile, std::ios::binary);
        if (!in) {
            std::cerr << "Failed to open chunk file: " << chunkFile << "\n";
            continue;
        }

        out << in.rdbuf();
        in.close();
    }

    out.close();
    std::cout << "Merged chunks into: " << outputFile << "\n";
    return 0;
}

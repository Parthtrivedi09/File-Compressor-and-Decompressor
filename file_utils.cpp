#include "file_utils.h"
#include <fstream>
#include <iostream>
#include <cstdint>

bool compressRLE(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream in(inputFile, std::ios::binary);
    if (!in) {
        std::cerr << "Failed to open file: " << inputFile << std::endl;
        return false;
    }

    std::ofstream out(outputFile, std::ios::binary);
    if (!out) {
        std::cerr << "Failed to open file: " << outputFile << std::endl;
        return false;
    }

    char current, next;
    uint8_t count = 0;

    if (!in.get(current)) return false;

    count = 1;
    while (in.get(next)) {
        if (next == current && count < 255) {
            ++count;
        } else {
            out.write(&current, 1);
            out.write(reinterpret_cast<char*>(&count), 1);
            current = next;
            count = 1;
        }
    }

    out.write(&current, 1);
    out.write(reinterpret_cast<char*>(&count), 1);

    in.close();
    out.close();
    return true;
}

bool decompressRLE(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream in(inputFile, std::ios::binary);
    if (!in) {
        std::cerr << "Failed to open file: " << inputFile << std::endl;
        return false;
    }

    std::ofstream out(outputFile, std::ios::binary);
    if (!out) {
        std::cerr << "Failed to open output file: " << outputFile << std::endl;
        return false;
    }

    char value;
    uint8_t count;

    while (in.read(&value, 1) && in.read(reinterpret_cast<char*>(&count), 1)) {
        for (int i = 0; i < count; ++i) {
            out.write(&value, 1);
        }
    }

    in.close();
    out.close();
    return true;
}

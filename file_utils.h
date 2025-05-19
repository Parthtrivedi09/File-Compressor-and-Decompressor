#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>

bool compressRLE(const std::string& inputFile, const std::string& outputFile);
bool decompressRLE(const std::string& inputFile, const std::string& outputFile);

#endif

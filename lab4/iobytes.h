#ifndef IOBYTES_H
#define IOBYTES_H

#include <iostream>
#include <vector>

std::vector<unsigned int> readBytes(const std::string filename);
void writeBytes(const std::string filename, const std::vector<unsigned int> &data);

#endif // IOBYTES_H

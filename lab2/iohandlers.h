#ifndef IOHANDLERS_H
#define IOHANDLERS_H

#include <iostream>

std::string getConsoleStr();
std::string getFileStr();

void writeToFile(std::string filename, std::string cipherString);
std::string readFromFile(std::string filename);

#endif // IOHANDLERS_H

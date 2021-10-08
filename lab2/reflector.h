#ifndef REFLECTOR_H
#define REFLECTOR_H

#include <string>
#include <fstream>

const static int SIZE = 95;

class Reflector
{
public:
    Reflector(bool decoder = false);
    int encode(int symb);

    void loadReflector();
    void saveReflector();

private:
    int buff[SIZE];
    std::string filename = "reflector";
};

#endif // REFLECTOR_H

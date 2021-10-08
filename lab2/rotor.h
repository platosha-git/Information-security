#ifndef ROTOR_H
#define ROTOR_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <random>

const static int SIZER = 95;

class Rotor
{
public:
    Rotor(std::string fileRotor, bool decoder = false);

    int encode(int symb);
    int reverse(int symb);

    int getNumShifts();
    void shift();

    void loadRotor();
    void saveRotor();

private:
    int buff[SIZER];
    int numShifts;
    std::string filename;
};

#endif // ROTOR_H

#include <random>
#include "rotor.h"

using namespace std;

Rotor::Rotor(std::string fileRotor, bool decoder) :
    numShifts(0), filename(fileRotor)
{
    if (decoder) {
        loadRotor();
    }
    else {
        for (int i = 0; i < SIZER; i++) {
            buff[i] = i;
        }

        srand(time(NULL));
        for (int i = 0; i < SIZER; i++) {
            swap(buff[i], buff[rand() % SIZER]);
        }
    }

    saveRotor();
}

int Rotor::encode(int symb)
{
    int idx = -1;
    for (int i = 0; i < SIZER; i++) {
        if (buff[i] == symb) {
            idx = i;
            break;
        }
    }

    return idx;
}

int Rotor::reverse(int symb)
{
    if (symb >= 0 && symb < SIZER)
        return buff[symb];
    return -1;
}

int Rotor::getNumShifts()
{
    return numShifts;
}

void Rotor::shift()
{
    numShifts = (numShifts + 1) % SIZER;
    rotate(buff, buff + 1, buff + SIZER);
}

void Rotor::saveRotor()
{
    ofstream out;
    out.open(filename);
    if (out.is_open()) {
        for (int i = 0; i < SIZER; i++) {
            out << buff[i] << " ";
        }
    }
    out.close();
}

void Rotor::loadRotor()
{
    ifstream in;
    in.open(filename);
    if (in.is_open()) {
        for (int i = 0; i < SIZER; i++) {
            in >> buff[i];
        }
    }
    in.close();
}

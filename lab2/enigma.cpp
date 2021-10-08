#include "enigma.h"

using namespace std;

Enigma::Enigma(EnigmaType type, int _numRotors) :
    numRotors(_numRotors)
{
    if (type == encoder) {
        for (int i = 0; i < numRotors; i++) {
            string fileRotor = "rotor" + to_string(i);
            rotors.emplace_back(fileRotor);
        }
        reflector = new Reflector();
    }
    else {
        for (int i = 0; i < numRotors; i++) {
            string fileRotor = "rotor" + to_string(i);
            rotors.emplace_back(fileRotor, true);
        }
        reflector = new Reflector(true);
    }
}

Enigma::~Enigma()
{
    delete reflector;
}

string Enigma::encrypt(std::string str)
{
    int len = str.length();
    string encodeStr = "";
    for (int i = 0; i < len; i++) {
        int symb = str[i] - 32;

        int encodeSymb = encryptSymb(symb);
        encodeStr += static_cast<unsigned char>(encodeSymb + 32);

        rotorsShift();
    }

    return encodeStr;
}

int Enigma::encryptSymb(int symb)
{
    for (int i = 0; i < numRotors; i++) {
        symb = rotors[i].encode(symb);
    }

    symb = reflector->encode(symb);

    for (int i = numRotors - 1; i >= 0; i--) {
        symb = rotors[i].reverse(symb);
    }

    return symb;
}

void Enigma::rotorsShift()
{
    for (int i = 0; i < numRotors; i++) {
        if (rotors[i].getNumShifts() > 0) {
            rotors[i].shift();
            break;
        }

        if (i == numRotors - 1) {
            rotors[0].shift();
            break;
        }

        if (rotors[i + 1].getNumShifts() == 0) {
            rotors[i].shift();
            break;
        }
    }
}

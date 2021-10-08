#ifndef ENIGMA_H
#define ENIGMA_H

#include "rotor.h"
#include "reflector.h"

enum EnigmaType
{
    encoder,
    decoder
};

class Enigma
{
public:
    explicit Enigma(EnigmaType type, int _numRotors);
    ~Enigma();

    std::string encrypt(std::string str);

    int encryptSymb(int symb);
    void rotorsShift();

private:
    int numRotors;
    Reflector *reflector;
    std::vector<Rotor> rotors;
};

#endif // ENIGMA_H

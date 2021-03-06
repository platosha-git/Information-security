#ifndef RSAGENERATOR_H
#define RSAGENERATOR_H

#include <utility>
#include <vector>
#include <random>

struct Keys
{
    std::vector<unsigned int> PublicKey;
    std::vector<unsigned int> PrivateKey;
};

class RSAGenerator
{
public:
    Keys getKeys();

private:
    std::vector<unsigned int> getRandomPrimes();
    unsigned int generateE(unsigned int euler);
    unsigned int generateD(unsigned int e, unsigned int phi);
};

std::vector<unsigned int> getTable();
unsigned int gcf(unsigned int a, unsigned int b);
std::vector<unsigned int> gcfx(unsigned int a, unsigned int b);

#endif // RSAGENERATOR_H

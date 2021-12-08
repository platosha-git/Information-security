#include <vector>
#include "rsa.h"

using namespace std;

unsigned int RSA::binpow(unsigned int a, unsigned int n, unsigned int m)
{
    unsigned int res = 1;
    while (n) {
        if (n & 1) {
            res *= a;
            res %= m;
        }
        a *= (a % m);
        a %= m;
        n >>= 1;
    }
    return res % m;
}

void RSA::initPublicKey(vector<unsigned int> publicKey)
{
    e = publicKey[0];
    n = publicKey[1];
}

void RSA::initPrivateKey(vector<unsigned int> privateKey)
{
    d = privateKey[0];
    n = privateKey[1];
}

unsigned int RSA::encode(unsigned char symbol)
{
    unsigned int enSymbol = binpow(symbol, e, n);
    return enSymbol;
}

unsigned char RSA::decode(unsigned int symbol)
{
    unsigned int deSymbol = binpow(symbol, d, n);
    return static_cast<unsigned char>(deSymbol);
}

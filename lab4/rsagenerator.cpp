#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "rsagenerator.h"

using namespace std;

const string tableName = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab4/primes";
const int numRows = 100;
const int numColumns = 12;

Keys RSAGenerator::getKeys()
{
    vector<unsigned int> primes = getRandomPrimes();
    unsigned int p = primes[0], q = primes[1];

    unsigned int n = p * q;
    unsigned int euler = (p - 1) * (q - 1);

    unsigned int e = generateE(euler);
    unsigned int d = generateD(e, euler);

    Keys keys;
    keys.PublicKey = {e, n};
    keys.PrivateKey = {d, n};

    return keys;
}

vector<unsigned int> RSAGenerator::getRandomPrimes()
{
    srand(time(0));

    vector<unsigned int> table = getTable();

    vector<unsigned int> res;
    for (int i = 0; i < 2; i++) {
        int k = rand() % numRows, l = rand() % numColumns;
        unsigned int number = table[numColumns * k + l];
        res.push_back(number);
    }

    return res;
}

unsigned int RSAGenerator::generateE(unsigned int euler)
{
    unsigned int e = 5;
    for (e = 5; e < euler; e++) {
        if (greatestCommonFactor(e, euler) == 1) {
            break;
        }
    }

    return e;
}

//Мультипликативно обратное по модулю
unsigned int RSAGenerator::generateD(unsigned int e, unsigned int euler)
{
    vector<unsigned int> res = gcfx(e, euler);
    unsigned int d = (res[1] % euler);
    return d;
}

vector<unsigned int> getTable()
{
    string line = "", number = "";
    vector<unsigned int> table;

    ifstream in(tableName);
    if (in.is_open()) {
        while (getline(in, line)) {
            stringstream strStream(line);
            while (getline(strStream, number, '\t')) {
                table.push_back(atoi(number.c_str()));
            }
        }
    }
    in.close();

    return table;
}

//Наибольший общий делитель
unsigned int greatestCommonFactor(unsigned int a, unsigned int b)
{
    while (b > 0) {
        a %= b;
        swap(a, b);
    }

    return a;
}

//Расширенный алгоритм Евклида
vector<unsigned int> gcfx(unsigned int a, unsigned int b)
{
    if (a == 0) {
        return {b, 0, 1};
    }

    vector<unsigned int> res = gcfx(b % a, a);
    unsigned int x = res[2] - (b / a) * res[1];
    unsigned int y = res[1];

    return {res[0], x, y};
}

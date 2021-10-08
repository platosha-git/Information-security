#include "reflector.h"
#include <iostream>

using namespace std;

Reflector::Reflector(bool decoder)
{
    if (decoder) {
        loadReflector();
    }
    else {
        fill(buff, buff + SIZE, -1);

        srand(time(NULL));
        for (int i = 0; i < SIZE; i++) {
            if (buff[i] == -1) {
                while (true) {
                    int idx = (i + 1 + random()) % SIZE;

                    if (buff[idx] != -1) {
                        continue;
                    }

                    buff[idx] = i;
                    buff[i] = idx;
                    break;
                }
            }
        }
    }
    saveReflector();
}

int Reflector::encode(int symb)
{
    int idx = -1;
    for (int i = 0; i < SIZE; i++) {
        if (buff[i] == symb) {
            idx = i;
            break;
        }
    }

    return idx;
}

void Reflector::saveReflector()
{
    ofstream out;
    out.open(filename);
    if (out.is_open()) {
        for (int i = 0; i < SIZE; i++) {
            out << buff[i] << " ";
        }
    }
    out.close();
}

void Reflector::loadReflector()
{
    ifstream in;
    in.open(filename);
    if (in.is_open()) {
        for (int i = 0; i < SIZE; i++) {
            in >> buff[i];
        }
    }
    in.close();
}

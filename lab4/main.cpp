#include <iostream>
#include <fstream>
#include <sstream>

#include "rsagenerator.h"
#include "rsa.h"

using namespace std;

const string publicFilename = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab4/public.key";
const string privateFilename = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab4/private.key";

const string inputFilename = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab4/input";
const string encodeFilename = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab4/encode";
const string decodeFilename = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab4/decode";

void menu()
{
    cout << "Genereate keys......1" << endl;
    cout << "Encode message......2" << endl;
    cout << "Decode message......3" << endl;
    cout << "Exit................4" << endl;
}

void writeKey(const vector<unsigned int> key, const string filename)
{
    ofstream out(filename);
    if (out.is_open()) {
        out << key[0] << " " << key[1];
        out.close();
    }

    cout << key[0] << " " << key[1] << endl;
    cout << "Key was written to the file!\n\n";
}

vector<uint8_t> read_bytes(const char *filename) {
    ifstream fin(filename);
    fin.seekg(0, ios::end);
    size_t len = fin.tellg();
    auto *bytes = new char[len];
    fin.seekg(0, ios::beg);
    fin.read(bytes, len);
    fin.close();
    vector<uint8_t> ret(len);
    for (int i = 0; i < len; i++)
        ret[i] = (uint8_t) bytes[i];
    delete[] bytes;
    return ret;
}

void write_bytes(const char *filename, const vector<uint8_t> &data) {
    ofstream fout(filename);
    char *buf = new char[data.size()];
    for (int i = 0; i < data.size(); i++)
        buf[i] = (char) data[i];
    fout.write(buf, data.size());
    fout.close();
}

int main()
{
    int choose = 0;
    while (choose != 4) {
        menu();
        cin >> choose;

        switch(choose) {
        case 1:
        {
            RSAGenerator generator;
            Keys keys = generator.getKeys();
            writeKey(keys.PublicKey, publicFilename);
            writeKey(keys.PrivateKey, privateFilename);
            break;
        }
        case 2:
        {
            uint64_t e = 7, m = 5;
            auto in = read_bytes(inputFilename.c_str());
            write_bytes(encodeFilename.c_str(), process_bytes(in, {e, m}, true));
            cout << "Done." << endl;

            break;
        }
        case 3:
        {
            uint64_t e = 7, m = 5;
            auto in = read_bytes(encodeFilename.c_str());
            write_bytes(decodeFilename.c_str(), process_bytes(in, {e, m}, false));
            cout << "Done." << endl;
            break;
        }
        default:
            break;
        }
    }

    return 0;
}

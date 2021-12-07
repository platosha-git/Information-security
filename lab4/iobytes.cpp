#include <fstream>
#include "iobytes.h"

using namespace std;

vector<unsigned int> readBytes(const string filename)
{
    ifstream fin(filename);
    fin.seekg(0, ios::end);
    int len = fin.tellg();

    auto *bytes = new char[len];
    fin.seekg(0, ios::beg);
    fin.read(bytes, len);
    fin.close();

    vector<unsigned int> ret(len);
    for (int i = 0; i < len; i++) {
        ret[i] = (unsigned int) bytes[i];
    }
    delete[] bytes;

    return ret;
}

void writeBytes(const string filename, const vector<unsigned int> &data)
{
    ofstream fout(filename);

    char *buf = new char[data.size()];
    for (size_t i = 0; i < data.size(); i++) {
        buf[i] = (char) data[i];
    }
    fout.write(buf, data.size());

    fout.close();

    cout << "Bytes were written to the file!" << endl << endl;
}

#include "rsa.h"

using namespace std;

unsigned int RSA::binpow(unsigned int a, unsigned int n, unsigned int mod)
{
    unsigned int res = 1;
    while (n) {
        if (n & 1) {
            res *= a;
            res %= mod;
        }
        a *= (a % mod);
        a %= mod;
        n >>= 1;
    }
    return res % mod;
}

vector<unsigned int> RSA::encode(const vector<unsigned int> &data, vector<unsigned int> key)
{
    vector<unsigned int> resizedData = resize(data, 8, getChunkSize(key) - 1);
    vector<unsigned int> enData(resizedData.size());
    for (size_t i = 0; i < resizedData.size(); i++) {
        enData[i] = binpow(resizedData[i], key[0], key[1]);
    }

    vector<unsigned int> result64 = resize(enData, getChunkSize(key), 8);
    vector<unsigned int> result(result64.size());
    for (size_t i = 0; i < result64.size(); i++) {
        result[i] = (unsigned int) result64[i];
    }

    return result;
}

vector<unsigned int> RSA::decode(const vector<unsigned int> &data, vector<unsigned int> key)
{
    vector<unsigned int> resized_data = resize(data, 8, getChunkSize(key));
    vector<unsigned int> encrypted_data(resized_data.size());
    for (size_t i = 0; i < resized_data.size(); i++) {
        encrypted_data[i] = binpow(resized_data[i], key[0], key[1]);
    }

    vector<unsigned int> result_64 = resize(encrypted_data, getChunkSize(key) - 1, 8);
    vector<unsigned int> result(result_64.size());
    for (size_t i = 0; i < result_64.size(); i++) {
        result[i] = (unsigned int) result_64[i];
    }

    return result;
}

unsigned int RSA::getChunkSize(vector<unsigned int> key) {
    return 32 - __builtin_clz(key[1]);
}

vector<unsigned int> resize(const vector<unsigned int> &data, unsigned int size, unsigned int newSize) {
    vector<unsigned int> res;
    unsigned int done = 0;
    unsigned int cur = 0;
    for (unsigned int byte: data)
        for (unsigned int i = 0; i < size; i++) {
            cur = (cur << 1U) + (((unsigned int) byte & (1U << (unsigned int) (size - 1 - i))) != 0);
            done++;
            if (done == newSize) {
                done = 0;
                res.push_back(cur);
                cur = 0;
            }
        }

    //Дополнение нулями
    if (done != 0)
        res.push_back(cur << (unsigned int) (newSize - done));
    return res;
}

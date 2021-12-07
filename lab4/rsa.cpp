#include "rsa.h"

using namespace std;

vector<unsigned int> process_bytes(const vector<unsigned int> &data, key k, bool encrypt) {
    vector<uint64_t> data_64(data.size());
    for (int i = 0; i < data.size(); i++)
        data_64[i] = (uint64_t) data[i];
    vector<uint64_t> resized_data = resize(data_64, 8, get_chunk_size(k) - encrypt); //Если мы шифруем, то размер блока K - 1, иначе K
    vector<uint64_t> encrypted_data(resized_data.size());
    for (int i = 0; i < resized_data.size(); i++)
        encrypted_data[i] = binpow(resized_data[i], k.e, k.m);
    vector<uint64_t> result_64 = resize(encrypted_data, get_chunk_size(k) - !encrypt, 8);
    vector<unsigned int> result(result_64.size());
    for (int i = 0; i < result_64.size(); i++)
        result[i] = (unsigned int) result_64[i];
    return result;
}

uint8_t get_chunk_size(key k) {
    return 32 - __builtin_clz(k.m);
}

uint64_t sqr(uint64_t x) {
    return x * x;
}

uint64_t binpow(uint64_t a, uint64_t e, uint64_t mod) {
    return e == 0 ? 1 : (e & 1U ? a * binpow(a, e - 1, mod) % mod : sqr(binpow(a, e / 2, mod)) % mod);
}

vector<uint64_t> resize(const vector<uint64_t> &data, uint8_t in_size, uint8_t out_size) {
    vector<uint64_t> res;
    uint8_t done = 0;
    uint64_t cur = 0;
    for (uint64_t byte: data)
        for (uint8_t i = 0; i < in_size; i++) {
            cur = (cur << 1U) + (((uint64_t) byte & (1U << (uint64_t) (in_size - 1 - i))) != 0);
            done++;
            if (done == out_size) {
                done = 0;
                res.push_back(cur);
                cur = 0;
            }
        }
    //Дополнение нулями
    if (done != 0)
        res.push_back(cur << (uint64_t) (out_size - done));
    return res;
}

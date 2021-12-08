#include <fstream>
#include <iostream>
#include "bitofile.h"
#include "bitifile.h"
#include "rsagenerator.h"
#include "rsa.h"

using namespace std;

const string publicFilename = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab41/public.key";
const string privateFilename = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab41/private.key";

const string inputFilename = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab41/input";
const string encodeFilename = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab41/encode";
const string decodeFilename = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab41/decode";


unsigned char bytes_per_int(unsigned int n) {
    auto bits_per_freq = std::ceil(std::log2(static_cast<double>(n)));
    auto bytes_per_freq = std::ceil(bits_per_freq / 8);
    return static_cast<unsigned char>(bytes_per_freq);
}

void menu()
{
    cout << "Genereate keys......1" << endl;
    cout << "Encode message......2" << endl;
    cout << "Decode message......3" << endl;
    cout << "Exit................4" << endl;
}

int main(void)
{
    srand(time(0));
    int choose = 0;
    while (choose != 4) {
        menu();
        cin >> choose;

        switch(choose) {
        case 1:
        {
            RSAKeyGenerator generator;
            auto keys = generator.generate_keys();
            std::ofstream file(publicFilename);
            file << keys.first.first << " " << keys.first.second;
            std::ofstream private_file(privateFilename);
            private_file << keys.second.first << " " << keys.second.second;
            cout << "ok" << endl;
            break;
        }
        case 2:
        {
            std::ifstream inp(inputFilename, std::fstream::binary);
            BitOFile otp(encodeFilename);
            std::ifstream key(publicFilename);
            unsigned int e, n;
            key >> e >> n;
            auto bytes = bytes_per_int(n);

            RSA rsa;
            rsa.set_open_key(e, n);
            while (!inp.eof()) {
                auto symbol = inp.get();
                if (symbol < 0) {
                    break;
                }
                auto encoded = rsa.encode(static_cast<unsigned char>(symbol));
                otp.write_number(encoded, bytes);
            }
            inp.close();
            otp.close();
            break;
        }
        case 3:
        {
            BitIFile inp(encodeFilename);
            std::ofstream otp(decodeFilename, std::fstream::binary);
            std::ifstream key(privateFilename);
            unsigned int d, n;
            key >> d >> n;
            auto bytes = bytes_per_int(n);

            RSA rsa;
            rsa.set_private_key(d, n);
            while (!inp.eof()) {
                auto symbol = inp.read_number(bytes);
                auto decoded = rsa.decode(symbol);
                otp.put(decoded);
            }

            inp.close();
            otp.close();
            break;
        }
        default:
            break;
        }
    }

    return 0;
}

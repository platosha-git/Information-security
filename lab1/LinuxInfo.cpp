#include <iostream>
#include "LinuxInfo.h"

using namespace std;

const static string inFile = "key.txt";
const static string outFile = "licenseKey.txt";

void getInformationCmd()
{
	system("dmidecode --type 1 | grep 'Serial Number' | awk '{print $3}' > key.txt");
	system("dmidecode --type 1 | grep 'UUID' | awk '{print $2}' >> key.txt");

	system("dmidecode --type 2 | grep 'Serial Number' | awk '{print $3}' >> key.txt");
	
	system("dmidecode --type 4 | grep 'ID' | cut -d' ' -f3- >> key.txt");
	system("lscpu | grep 'Семейство ЦПУ' | awk '{print $3}' >> key.txt");
	system("lscpu | grep 'Модель' | awk '{print $2}' >> key.txt");
}


string getOriginalKey()
{
	getInformationCmd();

	string line = "", keyLine = "";
	ifstream in(inFile);
    if (in.is_open()) {
        while (getline(in, line)) {
            keyLine += line;
        }
    }

    in.close();

    return keyLine;
}


size_t getHashKey()
{
	string originalKey = getOriginalKey();
	size_t hashKey = hash<string>{}(originalKey);
	system("rm -f key.txt");

	return hashKey;
}

void writeHashKey(size_t hashKey)
{
	ofstream out(outFile);
	if (out.is_open()) {
		out << hashKey << endl;
	}	
	out.close();
}
#ifndef LINUXINFO_H
#define LINUXINFO_H

#include <fstream>

struct Information
{
	struct System {
		std::string SerialNumber;
		std::string UUID;
	};

	struct BaseBoard {
		std::string SerialNumber;
	};

	struct Processor {
		std::string ID;
		int Family;
		int Model;
	};
};

void getInformationCmd();
std::string getOriginalKey();

size_t getHashKey();
void writeHashKey(size_t hashKey);

#endif
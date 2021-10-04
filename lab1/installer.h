#ifndef INSTALLER_H
#define INSTALLER_H

#include <fstream>
#include <string>

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

void install();

#endif
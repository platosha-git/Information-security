#include <iostream>
#include "LinuxInfo.h"

int main()
{
	size_t hashKey = getHashKey();
	writeHashKey(hashKey);

	return 0;
}
#include <iostream>
#include <stdlib.h>
#include <string>
#include "KGenerator.h"

void log(std::string&& str, bool nextLine = true)
{
	if (nextLine)
		std::cout << str << std::endl;
	else
		std::cout << str;
}

void main(int argn, char *argv[])
{
	if (argn != 3) {
		log("param: [width] [height]");
		return;
	}

	int width = atoi(argv[1]);
	int height = atoi(argv[2]);
	printf("size : %dx%d\n", width, height);
	KGenerator kGenerator(width, height);
	return;
}
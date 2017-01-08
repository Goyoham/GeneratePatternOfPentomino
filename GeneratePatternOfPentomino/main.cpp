#include <iostream>
#include <stdlib.h>
#include <string>
#include "KGenerator.h"
#include "Utils.h"

void log(std::string&& str, bool nextLine = true)
{
	if (nextLine)
		std::cout << str << std::endl;
	else
		std::cout << str;
}

void main(int argn, char *argv[])
{
	if (argn == 3) {
		int width = atoi(argv[1]);
		int height = atoi(argv[2]);
		printf("size : %dx%d\n", width, height);
		KGenerator kGenerator(width, height);
	}
	else {
		{ KGenerator kGenerator(5, 3);  }//15
		{ KGenerator kGenerator(5, 4);  }//20
		{ KGenerator kGenerator(5, 5);  }//25
		{ KGenerator kGenerator(6, 5);  }//30
		{ KGenerator kGenerator(10, 3); }//30
		{ KGenerator kGenerator(7, 5);  }//35
		{ KGenerator kGenerator(8, 5);  }//40
		{ KGenerator kGenerator(10, 4); }//40
		{ KGenerator kGenerator(9, 5);  }//45
		{ KGenerator kGenerator(15, 3); }//45
		{ KGenerator kGenerator(10, 5); }//50
		{ KGenerator kGenerator(11, 5); }//55
		{ KGenerator kGenerator(10, 6); }//60
		{ KGenerator kGenerator(12, 5); }//60
		{ KGenerator kGenerator(15, 4); }//60
		{ KGenerator kGenerator(20, 3); }//60
	}
	std::cout << Utils::GetDateNow() << " end." << std::endl;
	getchar();
}
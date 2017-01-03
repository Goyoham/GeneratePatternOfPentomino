#pragma once
#include "KBoardData.h"

class KGenerator
{
public:
	KGenerator(int width_, int height_);

	void Run();
	void PutBlock(KBoardData& boardData_);

private:
	int width = 0;
	int height = 0;
};
#pragma once
#include <string>
#include "enum.h"
#include "KBoard.h"

struct KBlockState
{
	EBLOCK_TYPE blockType = eBlockType_Begin;
	bool flip = false;
	int rotate = 0;//0~3
};

struct KPosition
{
	int x = 0;
	int y = 0;
};

struct KBoardData
{
	KBoardData(int width_, int height_)
		: board(width_, height_)
	{}
	KBoard board;
	KBlockState state;
	KPosition offset;
	std::string blockList;
};
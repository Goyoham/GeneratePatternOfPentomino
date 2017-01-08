#pragma once
#include "pch.h"
#include "KBoard.h"

struct KBlockState
{
	EBLOCK_TYPE blockType = eBlockType_Begin;
	int flip = 0;
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
	{
#ifdef RUN_TYPE_2
		for (int i = 0; i < eBlockType_End; ++i) {
			ramainedBlocks.push_back(static_cast<EBLOCK_TYPE>(i));
		}
#endif //RUN_TYPE_2
	}
	KBoard board;
	KBlockState state;
	KPosition offset;
	std::string blockList;
	// type2
	std::vector<EBLOCK_TYPE> ramainedBlocks;
};
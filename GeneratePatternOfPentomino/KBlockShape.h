#pragma once
#include "pch.h"
#include "KBoardData.h"

typedef std::vector<std::vector<int>> KShape;
class KBlockShape
{
public:
	KBlockShape();
	KShape& GetShape(const KBlockState& state_)
	{
		return blockShapes[state_.flip][state_.rotate][state_.blockType];
	}
private:
	void SetShape(int flip_, int rotate_, EBLOCK_TYPE type_, const std::string&& str_);
	void MakeFlippedShape(const KShape& shape_, KShape& flippedShape_);
	void MakeRotatedShape(const KShape& shape_, KShape& rotatedShape_);
	void printShape(const KShape& shape_);

	KShape blockShapes[eFlip][eRotate][eBlockType_End];
};

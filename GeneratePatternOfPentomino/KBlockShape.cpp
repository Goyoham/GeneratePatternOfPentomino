#include "KBlockShape.h"

KBlockShape::KBlockShape()
{
	SetShape(0, 0, eBlockType_F, "011");
	SetShape(0, 0, eBlockType_F, "110");
	SetShape(0, 0, eBlockType_F, "010");

	SetShape(0, 0, eBlockType_I, "1");
	SetShape(0, 0, eBlockType_I, "1");
	SetShape(0, 0, eBlockType_I, "1");
	SetShape(0, 0, eBlockType_I, "1");
	SetShape(0, 0, eBlockType_I, "1");

	SetShape(0, 0, eBlockType_L, "10");
	SetShape(0, 0, eBlockType_L, "10");
	SetShape(0, 0, eBlockType_L, "10");
	SetShape(0, 0, eBlockType_L, "11");

	SetShape(0, 0, eBlockType_N, "01");
	SetShape(0, 0, eBlockType_N, "01");
	SetShape(0, 0, eBlockType_N, "11");
	SetShape(0, 0, eBlockType_N, "10");

	SetShape(0, 0, eBlockType_P, "11");
	SetShape(0, 0, eBlockType_P, "11");
	SetShape(0, 0, eBlockType_P, "10");

	SetShape(0, 0, eBlockType_T, "111");
	SetShape(0, 0, eBlockType_T, "010");
	SetShape(0, 0, eBlockType_T, "010");

	SetShape(0, 0, eBlockType_U, "101");
	SetShape(0, 0, eBlockType_U, "111");

	SetShape(0, 0, eBlockType_V, "001");
	SetShape(0, 0, eBlockType_V, "001");
	SetShape(0, 0, eBlockType_V, "111");

	SetShape(0, 0, eBlockType_W, "001");
	SetShape(0, 0, eBlockType_W, "011");
	SetShape(0, 0, eBlockType_W, "110");

	SetShape(0, 0, eBlockType_X, "010");
	SetShape(0, 0, eBlockType_X, "111");
	SetShape(0, 0, eBlockType_X, "010");

	SetShape(0, 0, eBlockType_Y, "01");
	SetShape(0, 0, eBlockType_Y, "11");
	SetShape(0, 0, eBlockType_Y, "01");
	SetShape(0, 0, eBlockType_Y, "01");

	SetShape(0, 0, eBlockType_Z, "110");
	SetShape(0, 0, eBlockType_Z, "010");
	SetShape(0, 0, eBlockType_Z, "011");

	for (int t = 0; t < eBlockType_End; ++t) {
		MakeFlippedShape(blockShapes[0][0][t], blockShapes[1][0][t]);
		for (int r = 0; r < eRotate - 1; ++r) {
			MakeRotatedShape(blockShapes[0][r][t], blockShapes[0][r + 1][t]);
			MakeFlippedShape(blockShapes[0][r + 1][t], blockShapes[1][r + 1][t]);
		}

		// print
		/*
		for (int r = 0; r < eRotate; ++r) {			
			std::cout << "<" << t << ">-----------------" << std::endl;
			printShape(blockShapes[0][r][t]);
			std::cout << "<" << t << ">flip -----------------" << std::endl;
			printShape(blockShapes[1][r][t]);
		}
		*/
	}
}

void KBlockShape::SetShape(int flip_, int rotate_, EBLOCK_TYPE type_, const std::string&& str_)
{
	std::vector<int> line;
	for (auto& ch : str_) {
		if (ch == '1')
			line.push_back(1);
		else
			line.push_back(0);
	}
	blockShapes[flip_][rotate_][type_].push_back(line);
}

void KBlockShape::MakeFlippedShape(const KShape& shape_, KShape& flippedShape_)
{
	for (auto& y : shape_) {
		std::vector<int> newY = y;
		std::reverse(newY.begin(), newY.end());
		flippedShape_.push_back(newY);
	}
}

void KBlockShape::MakeRotatedShape(const KShape& shape_, KShape& rotatedShape_)
{
	int sizeY = shape_.size();
	int sizeX = shape_[0].size();
	for (int x = 0; x < sizeX; ++x) {
		std::vector<int> newY;
		for (int y = 0; y < sizeY; ++y) {
			newY.push_back(shape_[sizeY-y-1][x]);
		}
		rotatedShape_.push_back(newY);
	}
}

void KBlockShape::printShape(const KShape& shape_)
{
	for (auto& y : shape_) {
		for (auto& x : y) {
			std::cout << x;
		}
		std::cout << std::endl;
	}
}
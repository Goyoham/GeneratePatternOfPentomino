#include "KGenerator.h"

KGenerator::KGenerator(int width_, int height_)
{
	this->width = width_;
	this->height = height_;

	Run();
}

void KGenerator::Run()
{
	KBoardData boardData(width, height);
	PutBlock(boardData);
}

/*
<이동순서>
1. (0,0)을 시작으로 X좌표이동
2. Y좌표 이동.
3. roate 4회
4. flip
5. 다음 블럭
*/
void KGenerator::PutBlock(KBoardData& boardData_)
{

}
#pragma once
#include <map>
#include <set>
#include <string>
#include "KBoardData.h"
#include "KBlockShape.h"

class KGenerator
{
public:
	KGenerator(int width_, int height_);

	void Run();
	void PutBlock(KBoardData& boardData_);
	bool InsertBlock(KBoardData& boardData_, const KShape& shape_, bool bCheckOnly_);
	void RegisterCompletedBoard(const KBoardData& boardData_);
	void GetSerializedBoards(const KBoardData& boardData_, std::vector<std::string>& serializedBoards_);
	void GetBoardSizeStr(const KBoardData& boardData_, std::string& strSize_);
	bool CheckImpossiblePlacement(const KBoardData& boardData_);

private:
	void _PrintBoard(const KBoardData& boardData_);
	void _PrintResult();
	void _WriteFile();

	KBlockShape blockShape;
	int width = 0;
	int height = 0;

	int iCount = 0;
	float elapsedTime = 0;
	std::string strSize;
	std::set<std::string> setBlockList;
	std::map<std::string, std::set<std::string>> checkDuplicatedBoardList;
	std::map<std::string, std::map<std::string, std::vector<std::string>>> verifiedBoards;
};
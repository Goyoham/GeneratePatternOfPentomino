
#include "KGenerator.h"


KGenerator::KGenerator(int width_, int height_)
{
	this->width = width_;
	this->height = height_;

	this->strSize += std::to_string(width_);
	this->strSize += "x";
	this->strSize += std::to_string(height_);

	std::cout << Utils::GetDateNow() << " " << strSize << " .." << std::endl;

	auto startTime = ::GetTickCount();
	Run();
	elapsedTime = (::GetTickCount() - startTime) / 1000.f;
	std::cout << " elapsedTime : " << elapsedTime << std::endl;

	//_PrintResult();
	_WriteFile();
	//getchar();
}

void KGenerator::Run()
{
	KBoardData boardData(width, height);
#ifdef RUN_TYPE_1
	std::cout << "RunType : 1" << std::endl;
	PutBlock_Type1(boardData);
#else //RUN_TYPE_1
	std::cout << "RunType : 2" << std::endl;
	PutBlock_Type2(boardData);
#endif //RUN_TYPE_1
}

/*
<이동순서>
1. (0,0)을 시작으로 X좌표이동
2. Y좌표 이동.
3. roate 4회
4. flip
5. 다음 블럭
*/
void KGenerator::PutBlock_Type1(KBoardData& boardData_)
{
	std::vector<KBoardData> recursiveList;
	int boardSizeX = boardData_.board.width;
	int boardSizeY = boardData_.board.height;
	while (boardData_.state.blockType < eBlockType_End)
	{
		auto& shape = blockShape.GetShape(boardData_.state);
		int shapeSizeX = shape[0].size();
		int shapeSizeY = shape.size();
		if (shapeSizeX + boardData_.offset.x > boardSizeX) {
			boardData_.offset.x = 0;
			boardData_.offset.y += 1;
			continue;
		}
		else if (shapeSizeY + boardData_.offset.y > boardSizeY) {
			boardData_.offset.x = 0;
			boardData_.offset.y = 0;
			boardData_.state.rotate += 1;

			if (boardData_.state.rotate >= eRotate || Utils::_IsNoRotateBlock(boardData_.state.blockType)) {
				boardData_.state.rotate = 0;

				if (Utils::_IsNoFlipBlock(boardData_.state.blockType))
					boardData_.state.flip = eFlip;
				else
					boardData_.state.flip += 1;
			}			

			if (boardData_.state.flip >= eFlip) {
				boardData_.state.flip = 0;
				boardData_.state.blockType = static_cast<EBLOCK_TYPE>(boardData_.state.blockType + 1);
			}
			continue;
		}

		if (InsertBlock_Type1(boardData_, shape, true)) {
			auto cloneBoardData = boardData_;
			cloneBoardData.offset.x += 1;
			recursiveList.push_back(cloneBoardData);

			InsertBlock_Type1(boardData_, shape, false);
			// 절대 불가능한 패턴 검사
			if (CheckImpossiblePlacement(boardData_) == false)
				break;

			boardData_.blockList += Utils::_GetStrType(boardData_.state.blockType);
			boardData_.state.blockType = static_cast<EBLOCK_TYPE>(boardData_.state.blockType + 1);
			boardData_.state.flip = 0;
			boardData_.state.rotate = 0;
			boardData_.offset.x = 0;
			boardData_.offset.y = 0;

			if (boardData_.board.IsCompletedBoard())
				break;			
		}
		else {
			boardData_.offset.x += 1;
		}			
	}

	if (boardData_.board.IsCompletedBoard()) {
		//_PrintBoard(boardData_);
		//setBlockList.insert(boardData_.blockList);
		RegisterCompletedBoard(boardData_);
	}

	// recursive
	for (auto& data : recursiveList) {
		PutBlock_Type1(data);
	}
}

void KGenerator::PutBlock_Type2(KBoardData& boardData_)
{
	std::vector<KBoardData> recursiveList;
	int boardSizeX = boardData_.board.width;
	int boardSizeY = boardData_.board.height;

	auto vitBlockType = boardData_.ramainedBlocks.begin();
	for (; vitBlockType != boardData_.ramainedBlocks.end(); ++vitBlockType) {
		if (*vitBlockType == boardData_.state.blockType)
			break;
	}

	bool bNoJem = false;
	while (vitBlockType != boardData_.ramainedBlocks.end())
	{
		bNoJem = false;
		boardData_.state.blockType = *vitBlockType;
		auto& shape = blockShape.GetShape(boardData_.state);
		int shapeSizeX = shape[0].size();
		int shapeSizeY = shape.size();
		if (shapeSizeX + boardData_.offset.x > boardSizeX) {
			boardData_.offset.x = 0;
			boardData_.offset.y += 1;
			continue;
		}
		else if (shapeSizeY + boardData_.offset.y > boardSizeY) {
			boardData_.offset.x = 0;
			boardData_.offset.y = 0;
			boardData_.state.rotate += 1;

			if (boardData_.state.rotate >= Utils::_GetMaxRotate(boardData_.state.blockType)) {
				boardData_.state.rotate = 0;

				if (Utils::_IsNoFlipBlock(boardData_.state.blockType))
					boardData_.state.flip = eFlip;
				else
					boardData_.state.flip += 1;
			}

			if (boardData_.state.flip >= eFlip) {
				boardData_.state.flip = 0;
				//boardData_.state.blockType = static_cast<EBLOCK_TYPE>(boardData_.state.blockType + 1);
				++vitBlockType;
			}
			continue;
		}

		if (InsertBlock_Type2(boardData_, shape, true)) {
			auto cloneBoardData = boardData_;
			cloneBoardData.offset.x += 1;
			recursiveList.push_back(cloneBoardData);
			
			InsertBlock_Type2(boardData_, shape, false);
			// 절대 불가능한 패턴 검사
			if (CheckImpossiblePlacement(boardData_) == false)
				break;

			// 일자가 5칸 끝에 있는 패턴은 버린다. (노잼)
			if (IsNoJemPattern(boardData_)) {
				bNoJem = true;
				break;
			}

			boardData_.blockList += Utils::_GetStrType(boardData_.state.blockType);
			//boardData_.state.blockType = static_cast<EBLOCK_TYPE>(boardData_.state.blockType + 1);
			boardData_.ramainedBlocks.erase(vitBlockType);
			vitBlockType = boardData_.ramainedBlocks.begin();
			boardData_.state.flip = 0;
			boardData_.state.rotate = 0;
			boardData_.offset.x = 0;
			boardData_.offset.y = 0;

			if (boardData_.board.IsCompletedBoard2())
				break;
		}
		else {
			boardData_.offset.x += 1;
		}
	}

	if (boardData_.board.IsCompletedBoard() && !bNoJem) {
		//_PrintBoard(boardData_);
		//setBlockList.insert(boardData_.blockList);
		std::sort(boardData_.blockList.begin(), boardData_.blockList.end());
		RegisterCompletedBoard(boardData_);
	}

	// recursive
	for (auto& data : recursiveList) {
		PutBlock_Type2(data);
	}
}

bool KGenerator::InsertBlock_Type1(KBoardData& boardData_, const KShape& shape_, bool bCheckOnly_)
{
	for (int y = 0; y < (int)shape_.size(); ++y) {
		for (int x = 0; x < (int)shape_[y].size(); ++x) {
			if (shape_[y][x] == 0)
				continue;
			if (boardData_.board.GetBoard(y + boardData_.offset.y, x + boardData_.offset.x) != -1)
				return false;
			if (bCheckOnly_)
				continue;
			boardData_.board.SetBoard(y + boardData_.offset.y, x + boardData_.offset.x, boardData_.state.blockType);
		}
	}
	return true;
}

bool KGenerator::InsertBlock_Type2(KBoardData& boardData_, const KShape& shape_, bool bCheckOnly_)
{
	bool bFillingNext = false;
	for (int y = 0; y < (int)shape_.size(); ++y) {
		for (int x = 0; x < (int)shape_[y].size(); ++x) {
			if (shape_[y][x] == 0)
				continue;
			if (boardData_.board.GetBoard(y + boardData_.offset.y, x + boardData_.offset.x) != -1)
				return false;

			if (boardData_.board.IsFillingNextIndex(y + boardData_.offset.y, x + boardData_.offset.x))
				bFillingNext = true;
			
			if (bCheckOnly_)
				continue;
			boardData_.board.SetBoard(y + boardData_.offset.y, x + boardData_.offset.x, boardData_.state.blockType);
		}
	}

	if (bFillingNext == false)
		return false;

	if (bCheckOnly_ == false) {
		boardData_.board.SetNextIndexToFill();
	}

	return true;
}

void KGenerator::RegisterCompletedBoard(const KBoardData& boardData_)
{
	std::vector<std::string> serializedBoards;
	GetSerializedBoards(boardData_, serializedBoards);

	{ // 중복 검사용
		auto mitSize = checkDuplicatedBoardList.find(strSize);
		if (mitSize == checkDuplicatedBoardList.end()) {
			mitSize = checkDuplicatedBoardList.emplace(strSize, std::set<std::string>()).first;
		}

		auto& setList = mitSize->second;
		// 중복 블럭 검사. 하나만 하면 됨.
		if (setList.find(serializedBoards[0]) != setList.end())
			return;

		for (auto& sBoard : serializedBoards) {
			setList.insert(sBoard);
		}
	}

	{ // 검증 결과 입력
		auto mitSize = verifiedBoards.find(strSize);
		if (mitSize == verifiedBoards.end()) {
			mitSize = verifiedBoards.emplace(strSize, std::map<std::string, std::vector<std::string>>()).first;
		}
		auto& mapBlcokList = mitSize->second;
		auto mitBlockList = mapBlcokList.find(boardData_.blockList);
		if (mitBlockList == mapBlcokList.end()) {
			mitBlockList = mapBlcokList.emplace(boardData_.blockList, std::vector<std::string>()).first;
		}
		auto& setList = mitBlockList->second;
		setList.push_back(serializedBoards[0]);
	}
}

void KGenerator::GetSerializedBoards(const KBoardData& boardData_, std::vector<std::string>& serializedBoards_)
{
	serializedBoards_.clear();
	serializedBoards_.resize(4);
	for (int y = 0; y < boardData_.board.height; ++y) {
		for (int x = 0; x < boardData_.board.width; ++x) {
			serializedBoards_[0] += Utils::_GetStrType(static_cast<EBLOCK_TYPE>(boardData_.board.GetBoard(y, x)));
			serializedBoards_[1] += Utils::_GetStrType(static_cast<EBLOCK_TYPE>(boardData_.board.GetBoard(y, width - x - 1)));
			serializedBoards_[2] += Utils::_GetStrType(static_cast<EBLOCK_TYPE>(boardData_.board.GetBoard(height - y - 1, x)));
			serializedBoards_[3] += Utils::_GetStrType(static_cast<EBLOCK_TYPE>(boardData_.board.GetBoard(height - y - 1, width - x - 1)));
		}
		if (y < boardData_.board.height - 1) {
			serializedBoards_[0] += "_";
			serializedBoards_[1] += "_";
			serializedBoards_[2] += "_";
			serializedBoards_[3] += "_";
		}
	}
}

void KGenerator::GetBoardSizeStr(const KBoardData& boardData_, std::string& strSize_)
{
	strSize_ += std::to_string(boardData_.board.width);
	strSize_ += "x";
	strSize_ += std::to_string(boardData_.board.height);
}


bool KGenerator::CheckImpossiblePlacement(const KBoardData& boardData_)
{
	static int dirX[] = {1, 0, -1, 0};
	static int dirY[] = {0, 1, 0, -1};
	static int dir = 4;

	KBoard cloneBoard = boardData_.board;
	int space = 0;
	std::function<void(int, int, KBoard&, int&)> _check 
		= [&_check](int y, int x, KBoard& cloneBoard, int& space)
	{
		for (int d = 0; d < dir; ++d) {
			int dx = 1 * x + dirX[d];
			int dy = 1 * y + dirY[d];
			if (dx < 0 || dy < 0 || dx >= cloneBoard.width || dy >= cloneBoard.height)
				continue;
			if (cloneBoard.GetBoard(dy,dx) != -1)
				continue;
			cloneBoard.SetBoard(dy, dx, 1);
			space += 1;
			_check(dy, dx, cloneBoard, space);
		}
	};

	for (int y = 0; y < cloneBoard.height; ++y) {
		for (int x = 0; x < cloneBoard.width; ++x) {
			if (cloneBoard.GetBoard(y, x) != -1)
				continue;
			space = 0;
			_check(y, x, cloneBoard, space);
			if (space % 5 != 0)
				return false;
		}
	}
	return true;
}

bool KGenerator::IsNoJemPattern(const KBoardData& boardData_)
{
	if (boardData_.state.blockType != EBLOCK_TYPE::eBlockType_I)
		return false;

	if (boardData_.board.height == 5 && boardData_.state.rotate == 0) {
		int xn = 0, xm = 0;
		for (int y = 0; y < boardData_.board.height; ++y) {
			if (boardData_.board.GetBoard(y, 0) == EBLOCK_TYPE::eBlockType_I)
				++xn;
			else if (boardData_.board.GetBoard(y, boardData_.board.width - 1) == EBLOCK_TYPE::eBlockType_I)
				++xm;
		}
		if (xn == 5 || xm == 5)
			return true;
	}

	if (boardData_.board.width == 5 && boardData_.state.rotate == 1) {
		int xn = 0, xm = 0;
		for (int x = 0; x < boardData_.board.width; ++x) {
			if (boardData_.board.GetBoard(0, x) == EBLOCK_TYPE::eBlockType_I)
				++xn;
			else if (boardData_.board.GetBoard(boardData_.board.height - 1, x) == EBLOCK_TYPE::eBlockType_I)
				++xm;
		}
		if (xn == 5 || xm == 5)
			return true;
	}
	return false;
}

void KGenerator::_PrintBoard(const KBoardData& boardData_)
{
	std::cout << ++iCount << " " << boardData_.blockList << std::endl;
	boardData_.board.Print();
	std::cout << std::endl;
}

void KGenerator::_PrintResult()
{
	int numSize = (int)verifiedBoards.size();
	int numBlockList = 0;
	int numPatterns = 0;
	for (auto& blockSize : verifiedBoards) {
		std::cout << ">>" << blockSize.first << std::endl;
		for (auto& blockList : blockSize.second) {
			std::cout << ">" << blockList.first << std::endl;
			++numBlockList;
			for (auto& patterns : blockList.second) {
				std::cout << patterns << std::endl;
				++numPatterns;
			}
		}
	}
	std::cout << "numSize : " << numSize << std::endl;
	std::cout << "numBlockList : " << numBlockList << std::endl;
	std::cout << "numPatterns : " << numPatterns << std::endl;
}

void KGenerator::_WriteFile()
{
	std::ofstream outFile(strSize + ".txt");

	int numSize = (int)verifiedBoards.size();
	int numBlockList = 0;
	int numPatterns = 0;
	for (auto& blockSize : verifiedBoards) {
		outFile << ">>" << blockSize.first << std::endl;
		for (auto& blockList : blockSize.second) {
			outFile << ">" << blockList.first << std::endl;
			++numBlockList;
			for (auto& patterns : blockList.second) {
				outFile << patterns << std::endl;
				++numPatterns;
			}
		}
	}
	outFile << std::endl;
	outFile << "numSize : " << numSize << std::endl;
	outFile << "numBlockList : " << numBlockList << std::endl;
	outFile << "numPatterns : " << numPatterns << std::endl;
	outFile << "elapsedTime : " << elapsedTime << std::endl;
	outFile.close();
}
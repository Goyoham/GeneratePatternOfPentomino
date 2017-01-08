#pragma once
#include "pch.h"

class KBoard
{
public:
	KBoard(int width_, int height_)
	{
		this->width = width_;
		this->height = height_;
		this->board.resize(this->width * this->height);
		std::fill(this->board.begin(), this->board.end(), -1);
	}

	int GetIndex(int y, int x) const
	{
		int index = y * width + x;
		if (index < 0 || index >= (int)board.size())
			return -1;
		return index;
	}

	void SetBoard(int y, int x, int n)
	{
		int index = GetIndex(y, x);
		if (index == -1)
			return;
		board[index] = n;
	}

	int GetBoard(int y, int x) const
	{
		int index = GetIndex(y, x);
		if (index == -1)
			return -1;
		return board[index];
	}

	void Print() const
	{
		for (int i = 0; i < (int)board.size(); ++i) {
			std::cout << Utils::_GetStrType(static_cast<EBLOCK_TYPE>(board[i])) << " ";
			if (i > 0 && (i + 1) % width == 0)
				std::cout << std::endl;
		}
	}

	bool IsCompletedBoard() const
	{
		for (auto n : board) {
			if (n == -1)
				return false;
		}
		return true;
	}

	bool IsCompletedBoard2() const
	{
		return nextIndexToFill == (int)board.size();
	}

	bool IsFillingNextIndex(int y, int x) const
	{
		return GetIndex(y, x) == nextIndexToFill;
	}

	void SetNextIndexToFill()
	{
		for (int i = 0; i < (int)board.size(); ++i) {
			if (board[i] == -1) {
				nextIndexToFill = i;
				return;
			}
		}
		nextIndexToFill = (int)board.size();
	}

	int width = 0;
	int height = 0;
	std::vector<int> board;
	// type2
	int nextIndexToFill = 0;
};
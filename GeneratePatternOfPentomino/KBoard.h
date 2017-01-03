#pragma once
#include <vector>

class KBoard
{
public:
	KBoard(int width_, int height_)
	{
		this->width = width_;
		this->height = height_;
		this->board.resize(this->width * this->height);
	}

	int GetIndex(int x, int y)
	{
		return y * width + x;
	}

	void SetBoard(int x, int y, int n)
	{
		board[GetIndex(x, y)] = n;
	}

	int GetBoard(int x, int y, int n)
	{
		return board[GetIndex(x, y)];
	}

	int width = 0;
	int height = 0;
	std::vector<int> board;
};
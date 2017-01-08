#pragma once
#include "pch.h"

namespace Utils
{
	std::string _GetStrType(EBLOCK_TYPE blockType);
	bool _IsNoRotateBlock(EBLOCK_TYPE blockType);
	int _GetMaxRotate(EBLOCK_TYPE blockType);
	bool _IsNoFlipBlock(EBLOCK_TYPE blockType);
	std::string GetDateNow();
}
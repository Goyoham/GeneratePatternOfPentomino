#pragma once
#include <string>
#include "enum.h"

namespace Utils
{
	std::string _GetStrType(EBLOCK_TYPE blockType);
	bool _IsNoRotateBlock(EBLOCK_TYPE blockType);
	bool _IsNoFlipBlock(EBLOCK_TYPE blockType);
}
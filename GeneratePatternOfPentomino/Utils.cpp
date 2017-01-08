#include "Utils.h"
#include <stdio.h>
#include <ctime>

std::string Utils::_GetStrType(EBLOCK_TYPE blockType)
{
	switch (blockType) {
	case eBlockType_F: return "F";
	case eBlockType_I: return "I";
	case eBlockType_L: return "L";
	case eBlockType_N: return "N";
	case eBlockType_P: return "P";
	case eBlockType_T: return "T";
	case eBlockType_U: return "U";
	case eBlockType_V: return "V";
	case eBlockType_W: return "W";
	case eBlockType_X: return "X";
	case eBlockType_Y: return "Y";
	case eBlockType_Z: return "Z";
	}

	return "-";
}

bool Utils::_IsNoRotateBlock(EBLOCK_TYPE blockType)
{
	switch (blockType) {
	case eBlockType_X: return true;
	}

	return false;
}

int Utils::_GetMaxRotate(EBLOCK_TYPE blockType)
{
	switch (blockType) {
	case eBlockType_X:
		return 1;
	case eBlockType_I:
	case eBlockType_Z:
		return 2;
	}
	return eRotate;
}

bool Utils::_IsNoFlipBlock(EBLOCK_TYPE blockType)
{
	switch (blockType) {
	case eBlockType_I: return true;
	case eBlockType_T: return true;
	case eBlockType_U: return true;
	case eBlockType_V: return true;
	case eBlockType_W: return true;
	case eBlockType_X: return true;
	}

	return false;
}

std::string Utils::GetDateNow()
{
	char buf[64];
	struct tm curr_tm;
	time_t curr_time = time(NULL);
	localtime_s(&curr_tm, &curr_time);
	sprintf_s(buf, "(%04d-%02d-%02d %02d:%02d:%02d)"
		, curr_tm.tm_year + 1900, curr_tm.tm_mon + 1, curr_tm.tm_mday
		, curr_tm.tm_hour, curr_tm.tm_min, curr_tm.tm_sec);
	return buf;
}
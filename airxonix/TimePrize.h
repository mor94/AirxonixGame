#pragma once
#include "Prize.h"
class TimePrize:public Prize
{
public:
	TimePrize();
private:
	static bool m_registerit;
};


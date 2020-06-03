#pragma once
#include "Prize.h"
class BoostPrize: public Prize
{
public:
	BoostPrize();
private:
	static bool m_registerit;
};


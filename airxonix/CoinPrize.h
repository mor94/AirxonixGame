#pragma once
#include "Prize.h"
class CoinPrize : public Prize
{
public:
	CoinPrize();
private:
	static bool m_registerit;
};


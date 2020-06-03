#pragma once
#include "Prize.h"
class PoisonPrize: public Prize
{
public:
	PoisonPrize();
private:
	static bool m_registerit;
};


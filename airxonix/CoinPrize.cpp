#include "CoinPrize.h"
#include"PrizeFactory.h"

//=================================================================================
//constractor
CoinPrize::CoinPrize()
	:Prize((Media::instance().getTexture(t_coinPrize))/*,Media::instance().getSound(t_scorePrizeSound)*/)
{
}
//=================================================================================
//register
bool CoinPrize::m_registerit = PrizeFactory::registerit(t_coinPrize,
	[]() -> std::unique_ptr<Prize> { return std::make_unique<CoinPrize>(); });
//=================================================================================

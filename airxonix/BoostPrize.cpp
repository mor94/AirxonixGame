#include "BoostPrize.h"
#include"PrizeFactory.h"

//=================================================================================
//constructor
BoostPrize::BoostPrize()
	:Prize((Media::instance().getTexture(t_boostPrize))/*, Media::instance().getSound(t_frozenPrizeSound)*/)
{
}
//=================================================================================
//register
bool BoostPrize::m_registerit = PrizeFactory::registerit(t_boostPrize,
	[]() -> std::unique_ptr<Prize> { return std::make_unique<BoostPrize>(); });
//=================================================================================

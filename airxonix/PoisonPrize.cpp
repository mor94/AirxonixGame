#include "PoisonPrize.h"
#include"PrizeFactory.h"

//=================================================================================
//constractor
PoisonPrize::PoisonPrize()
	:Prize((Media::instance().getTexture(t_poisionPrize))/*,Media::instance().getSound(t_poisionPrizeSound)*/)
{
}

//=================================================================================
//register
bool PoisonPrize::m_registerit = PrizeFactory::registerit(t_poisionPrize,
	[]() -> std::unique_ptr<Prize> { return std::make_unique<PoisonPrize>(); });
//=================================================================================
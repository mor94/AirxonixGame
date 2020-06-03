#include "LifePrize.h"
#include"PrizeFactory.h"

//=================================================================================
//constractor
LifePrize::LifePrize()
	:Prize((Media::instance().getTexture(t_lifePrize)))
{
	
}
//=================================================================================
//register
bool LifePrize::m_registerit = PrizeFactory::registerit(t_lifePrize,
	[]() -> std::unique_ptr<Prize> { return std::make_unique<LifePrize>(); });
//=================================================================================
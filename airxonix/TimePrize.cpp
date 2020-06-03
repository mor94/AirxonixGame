#include "TimePrize.h"
#include"PrizeFactory.h"

//=================================================================================
//constructor
TimePrize::TimePrize()
	:Prize(Media::instance().getTexture(t_timePrize)/*, Media::instance().getSound(t_timePrizeSound)*/)
{
}
//=================================================================================
//register
bool TimePrize::m_registerit = PrizeFactory::registerit(t_timePrize,
	[]() -> std::unique_ptr<Prize> { return std::make_unique<TimePrize>(); });
//=================================================================================

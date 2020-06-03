#include "PrizeFactory.h"


//=================================================================
//this function return uniqe ptr of a new prize
std::unique_ptr<Prize> PrizeFactory::create(myEnum name) {
	auto it = getMap().find(name);
	if (it == getMap().end())
		return nullptr;
	return it->second();
}
//=================================================================
//insert the object to the map
bool PrizeFactory::registerit(myEnum name, std::unique_ptr<Prize>(*f)()) {
	getMap().emplace(name, f);
	return true;
}
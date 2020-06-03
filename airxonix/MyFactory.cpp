#include "MyFactory.h"


//=================================================================================
//constructor
MyFactory::MyFactory()
{
}
//=================================================================
//this function return uniqe ptr of a new enemy
std::unique_ptr<Enemy> MyFactory::create(myEnum name)
{
	auto it = Media::getMap().find(name);
	if (it == Media::getMap().end())
		return nullptr;
	return it->second();
}
//=================================================================
//insert the object to the map
bool MyFactory::registerit(myEnum name, std::unique_ptr<Enemy>(*f)())
{
	Media::getMap().emplace(name, f);
	return true;
}
//=======================================================================================

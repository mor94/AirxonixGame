#pragma once
#include "Enemy.h"
#include <map>
#include <time.h>

class MyFactory
{
public:
	MyFactory();
	static std::unique_ptr<Enemy> create(myEnum name);
	static bool registerit(myEnum name, std::unique_ptr<Enemy>(*)());
};


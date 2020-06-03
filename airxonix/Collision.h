#pragma once

#include "Object.h"

#include <iostream>
#include <typeinfo>
#include "Game.h"
// Sample struct for exception throwing
struct UnknownCollision
{
	UnknownCollision(Object&  a, Object& b) : first(a), second(b)
	{
		std::cout << "Unkown collision of " << typeid(a).name() << " and "
			<< typeid(b).name() << std::endl;
	}
	Object & first;
	Object & second;
};

void processCollision(Object & object1, Object & object2, Game & g);


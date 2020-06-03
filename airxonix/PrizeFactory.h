#pragma once
#include <map>
#include <memory>
#include "Prize.h"
typedef std::map<myEnum , std::unique_ptr<Prize>(*)()> mymap;

class PrizeFactory
{
public:
	static std::unique_ptr<Prize> create(myEnum name);
	static bool registerit(myEnum name, std::unique_ptr<Prize>(*)());
private:
	static mymap& getMap()
	{
		static mymap m_map;
		return m_map;
	}
};




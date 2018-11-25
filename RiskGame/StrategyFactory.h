#pragma once

#include "stdafx.h"
#include "Strategy.h"

class StrategyFactory {

public:
	static Strategy* createStrategy(std::string strategy);
};

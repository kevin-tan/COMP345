#include "stdafx.h"
#include "StrategyFactory.h"
#include "Aggressive.h"
#include "Benevolent.h"
#include "Cheater.h"
#include "Random.h"

Strategy* StrategyFactory::createStrategy(std::string strategy) {
	if (strategy.compare("Aggressive") == 0) {
		return new Aggressive();
	}
	if (strategy.compare("Benevolent") == 0) {
		return new Benevolent();
	}
	if (strategy.compare("Cheater") == 0) {
		return new Cheater();
	}
	if (strategy.compare("Random") == 0) {
		return new Random();
	}
	return nullptr;
}

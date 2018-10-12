#pragma once

#include "DiceRollingFacility.h"

class PlayerAbstract {
protected:
	std::string name;
	DiceRollingFacility dice_rolling_facility;
	//HandOfCards
public:
	PlayerAbstract() = default;

	// Defining pure virtual functions (i.e. Concrete classes must define the methods)
	virtual void reinforce() = 0;
	virtual void attack() = 0;
	virtual void fortify() = 0;

	virtual std::string getName() = 0;
};

#pragma once

#include "Map.h"
#include "DiceRollingFacility.h"
#include "Hand.h"

class Player
{
	std::vector<Vertex> countries;
	DiceRollingFacility dice_rolling_facility;
	Hand hand;

public:
	Player();

	// Override method
	void reinforce();
	void attack();
	void fortify();

	std::vector<Vertex> getCountries();
	DiceRollingFacility& getDiceRollingFacility();
	Hand& getHand();
	
	void add_country(Vertex& country, Map& map);
};


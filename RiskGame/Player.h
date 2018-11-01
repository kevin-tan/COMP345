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

	std::vector<Vertex> get_countries();
	DiceRollingFacility* get_dice_rolling_facility();
	Hand* get_hand();
	
	void add_country(Vertex& country, Map& map);
};


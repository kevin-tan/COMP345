#pragma once

#include "Map.h"
#include "DiceRollingFacility.h"
#include "Hand.h"

class Player
{
	std::vector<Vertex> countries;
	DiceRollingFacility dice_rolling_facility;
	Hand hand;
	std::string name;

public:
	Player();
	Player(std::string name);

	// Override method
	void reinforce();
	void attack(Map& map);
	void fortify();

	vector<Vertex> get_countries() const;
	DiceRollingFacility* get_dice_rolling_facility();
	Hand* get_hand();
	std::string get_name() { return name; }
	
	void add_country(Vertex& country, Map& map);
};


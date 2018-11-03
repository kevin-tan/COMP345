#pragma once

#include "Map.h"
#include "DiceRollingFacility.h"
#include "Hand.h"

using std::string;
using std::vector;

class Player
{
public:
	Player();
	Player(string name);

	// Override method
	void reinforce();
	void attack();
	void fortify();

	vector<Vertex> get_countries() const;
	DiceRollingFacility* get_dice_rolling_facility();
	Hand* get_hand();
	string get_name();
	
	void add_country(Vertex& country, Map& map);

private:
	std::vector<Vertex> countries;
	DiceRollingFacility dice_rolling_facility;
	Hand hand;
	string name;
};


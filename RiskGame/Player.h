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

	// Override method
	void reinforce(Map&, Deck&);
	void attack();
	void fortify();

	vector<Vertex> get_countries() const;
	DiceRollingFacility* get_dice_rolling_facility();
	Hand* get_hand();
	
	void add_country(Vertex& country, Map& map);

private:
	std::vector<Vertex> countries;
	DiceRollingFacility dice_rolling_facility;
	Hand hand;
	
	int armies_from_continents(Map& map);
	int choose_country_to_add_army(Map& map, int total_army);
	int display_countries_and_armies(Map& map);
};


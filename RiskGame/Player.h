#pragma once

#include "Map.h"
#include "DiceRollingFacility.h"
#include "Hand.h"
#include "boost/format.hpp"

using std::string;
using std::vector;

class Player
{
public:
	Player();
	Player(string name);

	// Override method
	void reinforce(Map& map, Deck& deck);
	void attack();
	void fortify();

	vector<Vertex> get_countries() const;
	DiceRollingFacility* get_dice_rolling_facility();
	Hand* get_hand();
	string get_name() const;
	
	void add_country(Vertex& country, Map& map);
	int display_countries_and_armies(Map& map);
	void clear_countries_temp();

private:
	std::vector<Vertex> countries;
	DiceRollingFacility dice_rolling_facility;
	Hand hand;
	
	int armies_from_continents(Map& map);
	int choose_country_to_add_army(Map& map, int total_army);
	
	string name;
};


#pragma once

#include "Map.h"
#include "DiceRollingFacility.h"
#include "Hand.h"
#include "boost/format.hpp"

class Player
{
public:
	Player();
	Player(std::string name);

	// Override method
	void reinforce(Map& map, Deck& deck);
	void attack(Map& map);
	void fortify();

	void part3_reinforce();
	void part3_attack();
	void part3_fortify();

	vector<Vertex> get_countries() const;
	DiceRollingFacility* get_dice_rolling_facility();
	Hand* get_hand();
	std::string get_name() const;
	
	void add_country(Vertex& country, Map& map);
	int display_countries_and_armies(Map& map);
	void clear_countries_temp();

private:
	std::vector<Vertex> countries;
	DiceRollingFacility dice_rolling_facility;
	Hand hand;
	std::string name;
	
	int armies_from_continents(Map& map);
	int choose_country_to_add_army(Map& map, int total_army);
	void remove_country(Vertex& country, Map& map);
};


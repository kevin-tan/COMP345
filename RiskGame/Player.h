#pragma once

#include "Map.h"
#include "DiceRollingFacility.h"
#include "Hand.h"
#include "boost/format.hpp"

class Game;

class Player{
public:
	Player();
	Player(std::string name);

	// Override method
	void reinforce(Game* game);
	void attack(Game* game);
	void fortify(Game* game);

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
	int choose_country_to_add_army(Game* game, int total_army, std::string* phase_state);
	void remove_country(Vertex& country, Map& map);
};


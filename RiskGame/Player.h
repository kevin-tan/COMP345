#pragma once

#include "Map.h"
#include "DiceRollingFacility.h"
#include "Hand.h"
#include "boost/format.hpp"
#include "Strategy.h"

class Game;

class Player {
public:
	Player();
	Player(std::string name, Strategy* strategy);

	~Player();

	// Override method
	void reinforce(Game* game);
	void attack(Game* game);
	void fortify(Game* game);

	vector<Vertex> get_countries() const;
	DiceRollingFacility* get_dice_rolling_facility();
	Hand* get_hand();
	std::string get_name() const;
	void set_strategy(Strategy* strategy);

	void add_country(Vertex& country, Map& map);
	void clear_countries_temp();
	void remove_country(Vertex& country, Map& map);
	int armies_from_continents(Map* map);
	bool is_human();

private:
	std::vector<Vertex> countries;
	DiceRollingFacility* dice_rolling_facility;
	Hand* hand;
	std::string name;
	Strategy* strategy;
};
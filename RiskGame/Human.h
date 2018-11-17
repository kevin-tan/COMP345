#pragma once

#include "Strategy.h"

class Map;

class Human : public Strategy {
public:	
	void execute_reinforce(Game* game, Player* player) override;
	void execute_attack(Game* game, Player* player) override;
	void execute_fortify(Game* game, Player* player) override;

private:
	int display_countries_and_armies(Map* map, Player* player);
	int choose_country_to_add_army(Game* game, int total_army, std::string* phase_state, Player* player);
};

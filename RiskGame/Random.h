#pragma once
#include "Strategy.h"
#include "Game.h"

class Map;

class Random : public Strategy {
public:
	void execute_reinforce(Game* game, Player* player) override;
	void execute_attack(Game* game, Player* player) override;
	void execute_fortify(Game* game, Player* player) override;
	std::string get_strategy_name() override;
private:
	bool owns_all_adjacencies(Game* game, Player* player, Vertex country);
};

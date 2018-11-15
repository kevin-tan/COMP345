#pragma once
#include "Strategy.h"

class PlayerStrategy {
private:
	Strategy* strategy;
public:
	PlayerStrategy();
	PlayerStrategy(Strategy* init_strategy);

	void set_strategy(Strategy* strategy);
	Strategy* get_strategy();

	void execute_reinforcement_strategy(Game* game, Player* player);
	void execute_attack_strategy(Game* game, Player* player);
	void execute_fortify_strategy(Game* game, Player* player);
};

#include "stdafx.h"

#include "PlayerStrategy.h"

PlayerStrategy::PlayerStrategy() {}

PlayerStrategy::PlayerStrategy(Strategy* init_strategy) {
	this->strategy = init_strategy;
}

void PlayerStrategy::set_strategy(Strategy* strategy) {
	this->strategy = strategy;
}

Strategy* PlayerStrategy::get_strategy() {
	return strategy;
}

void PlayerStrategy::execute_reinforcement_strategy(Game* game, Player* player) {
	this->strategy->execute_reinforce(game, player);
}

void PlayerStrategy::execute_attack_strategy(Game* game, Player* player) {
	this->strategy->execute_attack(game, player);
}

void PlayerStrategy::execute_fortify_strategy(Game* game, Player* player) {
	this->strategy->execute_fortify(game, player);
}

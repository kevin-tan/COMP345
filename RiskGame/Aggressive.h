#pragma once
#include "Strategy.h"
#include "Game.h"

class Map;

class Aggressive : public Strategy {
public:
	void execute_reinforce(Game* game, Player* player) override;
	void execute_attack(Game* game, Player* player) override;
	void execute_fortify(Game* game, Player* player) override;

private:
	Vertex strongest_country(Game* game, vector<Vertex> countries);
};
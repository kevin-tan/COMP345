#pragma once

class Game;
class Player;

class Strategy {
public:
	virtual void execute_reinforce(Game* game, Player* player) = 0;
	virtual void execute_attack(Game* game, Player* player) = 0 ;
	virtual void execute_fortify(Game* game, Player* player) = 0;
	virtual std::string get_strategy_name() = 0;

	virtual ~Strategy() = default;
protected:
	Strategy();
};

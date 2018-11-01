#pragma once

#include "Player.h"
#include "Deck.h"

class Game
{
public:
	void init_game_players();
	void init_game_map();
	void init_game_deck();

	std::vector<Player> get_game_players();
	Map* get_game_map();
	Deck* get_game_deck();

private:
	std::vector<Player> game_players;
	Map game_map;
	Deck game_deck;
};

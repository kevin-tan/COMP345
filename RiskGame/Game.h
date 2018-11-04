#pragma once

#include "Player.h"
#include "Deck.h"

class Game
{
public:
	void init_game_players();
	void init_game_map();
	void init_game_deck();

	void init_startup_phase();

	void init_main_game_loop();

	std::vector<Player*> get_game_players() const;
	Map* get_game_map();
	Deck* get_game_deck();

private:
	std::vector<Player*> game_players;
	Map game_map;
	Deck game_deck;

	//Helper functions
	void shuffle_players();
	void distribute_countries();
	void distribute_armies();
	int get_number_of_armies();
	int get_country_armies(int player_i, int selection);
	Player* check_win_condition();
	void player0_win();
};

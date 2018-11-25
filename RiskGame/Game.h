#pragma once

#include "Player.h"
#include "Deck.h"
#include "Subject.h"

class Game : public ISubject {
public:
	Game();
	Game(vector<Player*>& players, std::string map_string);
	~Game();

	void init_game_players();
	void init_game_map();
	void init_game_deck();
	void init_startup_phase();
	void init_main_game_loop();

	std::string init_main_game_loop(int max_turns);


	std::vector<Player*> get_game_players() const;
	Map* get_game_map();
	Deck* get_game_deck();

	bool& get_running() { return running; }
	bool check_win_condition(Player* player);
	bool check_player_eliminated(Player* player);

private:
	std::vector<Player*> game_players;
	Map game_map;
	Deck game_deck;
	bool running;

	//Helper functions
	void shuffle_players();
	void distribute_countries();
	void distribute_armies();
	void place_initial_armies(vector<int>& remaining_armies);
	bool armies_remain(vector<int>& remaining_armies);
	int get_number_of_armies();
	void player0_win();
};
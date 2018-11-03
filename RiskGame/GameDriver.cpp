#include "stdafx.h"
#include "Game.h";

using std::cout;
using std::endl;

int main() {
	Game game;

	game.init_game_map();
	game.init_game_deck();
	game.init_game_players();

	//TODO Need to provide verification that a connected graph map was loaded (i think?)

	cout << "Number of players created: " << game.get_game_players().size() << endl;

	cout << "Deck size: " << game.get_game_deck()->get_deck_size() << endl;

	for (int i = 0; i < game.get_game_players().size(); i++) {
		cout << game.get_game_players()[i].get_name() << endl;
	}

	cout << "SHUFFLE:" << endl;
	
	for (int i = 0; i < game.get_game_players().size(); i++) {
		cout << game.get_game_players()[i].get_name() << endl;
	}

	game.init_startup_phase();

	cout << "COUNTRIES:" << endl;
	
	Graph& g = game.get_game_map()->get_graph();
	for (Vertex v : game.get_game_map()->get_countries()) {
		cout << "Player " << g[v].player->get_name() << " owns country " << g[v].country << " has " << g[v].army_size << " army unit(s)." << endl;

	}

	return 0;
}
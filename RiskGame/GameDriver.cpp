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

	return 0;
}
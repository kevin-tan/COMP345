   #include "stdafx.h"
#include "Game.h";

using std::cout;
using std::endl;
using std::cin;
//
//int main() {
//	Game game;
//
//	game.init_game_map();
//	game.init_game_deck();
//	game.init_game_players();
//
//	cout << "Number of players created: " << game.get_game_players().size() << endl;
//	cout << "Deck size: " << game.get_game_deck()->get_deck_size() << endl;
//
//	cout << "\nPlayers created: " << endl;
//	for (int i = 0; i < game.get_game_players().size(); i++) {
//		cout << "Player " << game.get_game_players()[i]->get_name() << endl;
//	}
//	cout << endl;
//
//	game.init_startup_phase();
//
//	cout << "Shuffled order of players: " << endl;
//
//	for (int i = 0; i < game.get_game_players().size(); i++) {
//		cout << "Player " << game.get_game_players()[i]->get_name() << endl;
//	}
//
//	cout << "\nAll countries have been assigned to one and only one player: " << endl;
//
//	Graph& g = game.get_game_map()->get_graph();
//	int counter = 1;
//	for (Vertex v : game.get_game_map()->get_countries()) {
//		cout << counter++ << ". " << g[v].country << " is owned solely by player " << g[v].player->get_name() << " where " << g[v].army_size << " army units are placed." << endl;
//	}
//
//	int mainloop;
//	cout << "\nProceed to main game loop?" << endl;
//	cin >> mainloop;
//
//	game.init_main_game_loop();
//
//	return 0;
//}
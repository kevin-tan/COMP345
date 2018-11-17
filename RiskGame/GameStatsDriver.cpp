#include "stdafx.h"
//#include <cstdlib>
//#include "MapLoader.h"
//#include "GameStatsViewer.h" //I HAVE CHANGED THIS/////////////////////////////////////////////////////////////////////////////////////////////
//
//using namespace std;
//
//void country_conquered(Game& game, Graph& g, Map* map);
//void eliminate_player(Game& game, Graph& g, Map* map);
//void print_info(Game& game, Graph& g, Map* map);
//void distribute_countries(Game& game, Map* map, vector<Player*> players);
//void attack_loop(Game& game, Graph& g, Map* map);
//
//// I  CAN NOT HAVE ARRAY OF OBSERVERS IN SUBJECT AS A POINTER 
//// I HAD TO REWRITE FUNCTIONALITY OF ATTACH METHOD IN SUBJECT
//int main() {
//	// Game
//	Game game;
//	game.init_game_map();
//	game.init_game_players();
//	game.init_game_deck();
//
//	// Game Stats Observer
////	GameStatsViewer* stats = new GameStatsViewer(game.get_game_map());
//
//	int choice = 0;
//	do {
//		cout << "\n[1] => Country has been conquered by a player\n";
//		cout << "[2] => Remove player and celebratory message\n";
//		cout << "[0] => Exit\n";
//
//		cout << "Enter your choise: ";
//		do {
//			cin >> choice;
//			if (choice < 0 || choice > 2)
//				cout << "Choice is not valid (0-2)\n ";
//		} while (choice < 0 || choice > 2);
//
//		switch (choice) {
//		case 1: country_conquered(game, game.get_game_map()->get_graph(), game.get_game_map()); break;
//		case 2: eliminate_player(game, game.get_game_map()->get_graph(), game.get_game_map()); break;
//		default: break;
//		}
//
//	} while (choice != 0);
//
//
//	return 0;
//}
//// Showcase a situation when player is eliminated
//void eliminate_player(Game& game, Graph& g, Map* map) {
//
//	// Assign one country to every player
//	vector<Player*> players = game.get_game_players();
//	for (int i = 0; i < players.size(); ++i) {
//		players[i]->add_country(map->get_countries()[i], *map);
//	}
//	// Assign the rest of the countries to player0
//	for (Vertex v : map->get_countries()) {
//		if (g[v].player == nullptr)
//			players[0]->add_country(v, *map);
//	}
//
//	// Assgin 1 unit to each country on the map
//	for (Vertex v : map->get_countries()) {
//		map->add_armies(v, 1);
//	}
//	// Add 1000 units to the player 0, so he can always win
//	map->add_armies(game.get_game_players()[0]->get_countries()[0], 1000);
//
//	print_info(game, g, map);
//	// GAME STATS VIEW ///////////////////////////////////////////////////////
//	map->notify_all();
//
//	// Main loop conquering process
//	// Attack phase
//	attack_loop(game, g, map);
//}
//
//// Showcase stats when country is being conquered.
//void country_conquered(Game& game, Graph& g, Map* map) {
//	distribute_countries(game, game.get_game_map(), game.get_game_players());
//	vector<Player*> players = game.get_game_players();
//	int num_of_players = game.get_game_players().size();
//	// Assgin 1 unit to each country on the map
//	for (Vertex v : map->get_countries()) {
//		map->add_armies(v, 1);
//	}
//	// Add 1000 units to the player 0, so he can always win
//	map->add_armies(game.get_game_players()[0]->get_countries()[0], 1000);
//	
//	print_info(game, g, map);
//
//	// GAME STATS VIEW ///////////////////////////////////////////////////////
//	map->notify_all();
//
//	// Main loop conquering process
//	attack_loop(game, g, map);
//}
//
//// Print countries that players own and number of armies on those countries
//void print_info(Game& game, Graph& g, Map* map) {
//	vector<Player*> players = game.get_game_players();
//	for (int i = 0; i < players.size(); i++) {
//		int size = 0;
//		for (Vertex v : players[i]->get_countries()) {
//			size += g[v].army_size;
//		}
//		cout << players[i]->get_name() << " has " << size << " total number of armies." << endl;
//	}
//
//	for (Vertex v : map->get_countries()) {
//		if (map->get_graph()[v].player == nullptr) {
//			cout << "Player is not set for country " << g[v].country << endl;
//		}
//		else {
//			cout << "Player " << g[v].player->get_name() << " owns country " << g[v].country << " has " << g[v].army_size <<
//				" size." << endl;
//		}
//	}
//
//	cout << endl;
//}
//// distribute countries randomly
//void distribute_countries(Game& game, Map* map, vector<Player*> players) {
//	int num_of_players = game.get_game_players().size();
//	for (int i = 0; i < map->get_countries().size(); i++) {
//		players[i % num_of_players]->add_country(map->get_countries()[i], *map);
//	}
//}
//
//// attack loop
//void attack_loop(Game& game, Graph& g, Map* map) {
//	vector<Player*> players = game.get_game_players();
//	int num_of_players = game.get_game_players().size();
//	// Attack phase
//	bool game_loop = true;
//	int turn = 0;
//	while (game_loop) {
//		// Print current player
//		cout << "Turn: " << turn << endl;
//		cout << "Player " << players[turn % num_of_players]->get_name() << " turn to play." << endl;;
//
//		// Player's attack phase choice
//		int attack_choice;
//		printf("Do you want to (0) attack or (1) skip your attack phase: ");
//		cin >> attack_choice;
//		while (attack_choice != 0 && attack_choice != 1) {
//			cout << "Please choose either (0) attack or (1) to skip the attack phase: ";
//			cin >> attack_choice;
//		}
//
//		// Attack
//		if (attack_choice == 0) {
//			char r = 'y';
//			do {
//				players[turn % num_of_players]->attack(&game);
//				cout << "Do you want to attack again? y/n: ";
//				cin >> r;
//			} while (r == 'y');
//			cout << "Stopping attack phase for player " << players[turn % num_of_players]->get_name() << endl;
//		}
//		else {
//			cout << "Skipping attack phase..." << endl;
//		}
//
//		cout << endl;
//		// GAME STATS VIEW ///////////////////////////////////////////////////////
//		map->notify_all();
//		// Increment turn for next player
//		turn++;
//	}
//}

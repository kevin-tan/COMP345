   #include "stdafx.h"
// #include <cstdlib>
// #include <time.h>
// #include "DiceRollingFacility.h"
// #include "MapLoader.h"
// #include "Player.h"
// #include "Hand.h"
// #include "Deck.h"
//
// using namespace std;
//
// void test(int num_of_players, Player* players[], Graph& g, Map& map) {
// 	for (int i = 0; i < num_of_players; i++) {
// 		int size = 0;
// 		for (Vertex v : players[i]->get_countries()) {
// 			size += g[v].army_size;
// 		}
// 		cout << players[i]->get_name() << " has " << size << " total number of armies." << endl;
// 	}
//
// 	for (Vertex v : map.get_countries()) {
// 		if (map.get_graph()[v].player == nullptr) {
// 			cout << "Player is not set for country " << g[v].country << endl;
// 		} else {
// 			cout << "Player " << g[v].player->get_name() << " owns country " << g[v].country << " has " << g[v].army_size <<
// 				" size." << endl;
// 		}
// 	}
//
// 	cout << endl;
// }
//
// int main() {
// 	// Map
// 	Map map = read_map_file("Maps/World.map");
// 	map.randomize();
// 	Graph& g = map.get_graph();
//
// 	// Players
// 	Player player_0("Kevin");
// 	Player player_1("Sagar");
// 	Player player_2("Neqqash");
// 	Player player_3("Yaroslav");
//
// 	Player* players[] = { &player_0, &player_1, &player_2, &player_3 };
// 	int num_of_players = 4;
//
// 	for (int i = 0; i < map.get_countries().size(); i++) {
// 		players[i % num_of_players]->add_country(map.get_countries()[i], map);
// 	}
//
// 	for (int i = 0; i < num_of_players; i++) {
// 		int armies = 30;
// 		while (armies > 0) {
// 			for (Vertex v : players[i]->get_countries()) {
// 				if (armies > 0) {
// 					g[v].army_size++;
// 					armies--;
// 				}
// 			}
// 		}
// 	}
//
// 	test(num_of_players, players, g, map);
//
// 	bool game_loop = true;
// 	int turn = 0;
// 	while (game_loop) {
// 		// Print current player
// 		cout << "Turn: " << turn << endl;
// 		cout << "Player " << players[turn % num_of_players]->get_name() << " turn to play." << endl;;
//
// 		// Player's attack phase choice
// 		int attack_choice;
// 		printf("Do you want to (0) attack or (1) skip your attack phase: ");
// 		cin >> attack_choice;
// 		while (attack_choice != 0 && attack_choice != 1) {
// 			cout << "Please choose either (0) attack or (1) to skip the attack phase: ";
// 			cin >> attack_choice;
// 		}
//
// 		// Attack
// 		if (attack_choice == 0) {
// 			char r = 'y';
// 			do {
// 				players[turn % num_of_players]->attack(map);
// 				cout << "Do you want to attack again? y/n: ";
// 				cin >> r;
// 			} while (r == 'y');
// 			cout << "Stopping attack phase for player " << players[turn % num_of_players]->get_name() << endl;
// 		} else {
// 			cout << "Skipping attack phase..." << endl;
// 		}
//
// 		cout << endl;
//
// 		// Increment turn for next player
// 		turn++;
// 	}
//
// 	int x = 0;
// 	cin >> x;
//
// 	return 0;
// }

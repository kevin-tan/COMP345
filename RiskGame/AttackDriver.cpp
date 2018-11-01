#include "stdafx.h"
#include <cstdlib>
#include <time.h>
#include "DiceRollingFacility.h"
#include "MapLoader.h"
#include "Player.h"
#include "Hand.h"
#include "Deck.h"

using namespace std;

void mapDriver() {
	int next;
	int choice;

	cout << "Would you like to enter your own file (1) or proceed with pre-made test cases (2)?" << endl;
	cin >> choice;

	if (choice == 1) {
		//Enter your own map
		string given_map_file;
		cout << "Enter map file: " << endl;
		cin >> given_map_file;
		try {
			Map given_map = read_map_file(given_map_file);
		} catch (exception e) {
			cout << e.what() << endl;
		}
	} else if (choice == 2) {
		//Invalid map (territory belonging to two continents)
		string territory_two_continents_map_file = "TerritoryTwoContinents.map";
		cout << "Running invalid test case #1 (Territory belongs to two continents)" << "\nOpening " <<
			territory_two_continents_map_file << " ..." << endl;
		try {
			Map territory_two_continents = read_map_file(territory_two_continents_map_file);
		} catch (exception e) {
			cout << e.what() << endl;
		}
		cout << "Move to next case: " << endl;
		cin >> next;
		cout << "\n-------------------------------------------\n";

		//Map file cannot be read (invalid format/does not exist)
		string map_file_dne = "DoesNotExist.map";
		cout << "Running invalid test case #2 (Map file cannot be read/does not exist)" << "\nOpening " << map_file_dne
			<<
			" ..." << endl;
		try {
			Map dne_map = read_map_file(map_file_dne);
		} catch (exception e) {
			cout << e.what() << endl;
		}
		cout << "Move to next case: " << endl;
		cin >> next;
		cout << "\n-------------------------------------------\n";

		//Map file continents section cannot be read
		string invalid_continents_map_file = "InvalidContinents.map";
		cout << "Running invalid test case #3 (Continents section cannot be parsed)" << "\nOpening " <<
			invalid_continents_map_file <<
			" ..." << endl;
		try {
			Map invalid_continents = read_map_file(invalid_continents_map_file);
		} catch (exception e) {
			cout << e.what() << endl;
		}
		cout << "Move to next case: " << endl;
		cin >> next;
		cout << "\n-------------------------------------------\n";

		//Map file territories section cannot be read
		string invalid_territories_map_file = "InvalidTerritories.map";
		cout << "Running invalid test case #4 (Territories section cannot be parsed/Unconnected territory)" <<
			"\nOpening "
			<< invalid_territories_map_file <<
			" ..." << endl;
		try {
			Map invalid_territories = read_map_file(invalid_territories_map_file);
		} catch (exception e) {
			cout << e.what() << endl;
		}
		cout << "Move to next case: " << endl;
		cin >> next;
		cout << "\n-------------------------------------------\n";

		//Valid map file
		string valid_map_file = "World.map";
		cout << "Running valid test case" << "\nOpening " << valid_map_file << " ..." << endl;
		try {
			Map valid_map = read_map_file(valid_map_file);
			for (string c : valid_map.get_continents()) {
				cout << c << endl;
			}
		} catch (exception e) {
			cout << e.what() << endl;
		}
	}

	cout << endl;
}

void test(int num_of_players, Player* players[], Graph& g, Map& map) {
	for (int i = 0; i < num_of_players; i++) {
		int size = 0;
		for (Vertex v : players[i]->get_countries()) {
			size += g[v].army_size;
		}
		cout << players[i]->get_name() << " has " << size << " total number of armies." << endl;
	}

	for (Vertex v : map.get_countries()) {
		if (map.get_graph()[v].player == nullptr) {
			cout << "Player is not set for country " << g[v].country << endl;
		} else {
			cout << "Player " << g[v].player->get_name() << " owns country " << g[v].country << " has " << g[v].army_size <<
				" size." << endl;
		}
	}

	cout << endl;
}

int main() {
	// Map
	Map map = read_map_file("World.map");
	map.randomize();
	Graph& g = map.get_graph();

	// Players
	Player player_0("Kevin");
	Player player_1("Sagar");
	Player player_2("Neqqash");
	Player player_3("Yaroslav");

	Player* players[] = { &player_0, &player_1, &player_2, &player_3 };
	int num_of_players = 4;

	for (int i = 0; i < map.get_countries().size(); i++) {
		players[i % num_of_players]->add_country(map.get_countries()[i], map);
	}

	for (int i = 0; i < num_of_players; i++) {
		int armies = 30;
		while (armies > 0) {
			for (Vertex v : players[i]->get_countries()) {
				if (armies > 0) {
					g[v].army_size++;
					armies--;
				}
			}
		}
	}

	test(num_of_players, players, g, map);

	bool game_loop = true;
	int turn = 0;
	while (game_loop) {
		// Print current player
		cout << "Turn: " << turn << endl;
		cout << "Player " << players[turn % num_of_players]->get_name() << " turn to play." << endl;;

		// Player's attack phase choice
		int attack_choice;
		printf("Do you want to (0) attack or (1) skip your attack phase: ");
		cin >> attack_choice;
		while (attack_choice != 0 && attack_choice != 1) {
			cout << "Please choose either (0) attack or (1) to skip the attack phase: ";
			cin >> attack_choice;
		}

		// Attack
		if (attack_choice == 0) {
			char r = 'y';
			do {
				players[turn % num_of_players]->attack(map);
				cout << "Do you want to attack again? y/n: ";
				cin >> r;
			} while (r == 'y');
			cout << "Stopping attack phase for player " << players[turn % num_of_players]->get_name() << endl;
		} else {
			cout << "Skipping attack phase..." << endl;
		}

		cout << endl;
		// Increment turn for next player
		turn++;
	}

	int x = 0;
	cin >> x;

	return 0;
}

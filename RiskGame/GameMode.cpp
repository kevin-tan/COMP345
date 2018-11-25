#include "stdafx.h"
#include "Game.h"
#include "GameMode.h"
#include <filesystem>
#include "Human.h"
#include "Benevolent.h"
#include "Aggressive.h"

GameMode::GameMode() {
}

GameMode::~GameMode() {
}

static int get_input(int min, int max, std::string message) {
	int input = -1;
	while (input < min || input > max) {
		std::cout << message;
		std::cin >> input;
	}

	return input;
}

void GameMode::init_game_mode() {
	using namespace std;

	// Select game mode
	int game_mode = get_input(0, 1, "Select game mode:\n (0) Single mode\n (1) Tournament mode\nSelection: ");
	if (game_mode == 0) {
		// Single mode, playing sequence as normal
		Game game;
		game.init_game_map();
		game.init_game_deck();
		game.init_game_players();
		game.init_startup_phase();
		game.init_main_game_loop();
	} else {
		// Tournament mode

		// Set up map selections
		vector<std::string> map_files;
		for (const auto p : std::experimental::filesystem::directory_iterator("Maps")) {
			map_files.push_back(p.path().string());
		}

		int map_size = get_input(1, 5, "Select number of maps to be played (1-5): ");
		vector<std::string> map_selection;
		for (int i = 0; i < map_size; i++) {
			cout << "Select a map file from the list below (found in /Maps): " << endl;
			for (int i = 0; i < map_files.size(); i++) {
				cout << "[" << i << "] " << map_files[i] << endl;
			}
			map_selection.push_back(map_files[get_input(0, map_files.size() - 1, "Select a map file from the list below (0-" + std::to_string((map_files.size() - 1)) + "): ")]);
		}

		// Player size selection with player strategy
		int player_size = get_input(2, 4, "Select number of players to be played (2-4): ");

		int strategy = 0;
		vector<Player*> players;
		cout << "Strategy options\n[0] Random player\n[1] Aggressive computer player\n[2] Benevolent computer player\n[3] Cheater" << endl;
		for (int i = 0; i < player_size; i++) {
			cout << "\nPlayer " << i << " strategy option: " << endl;
			cin >> strategy;
			while (strategy < 0 || strategy > 2) {
				cout << "Invalid option. Please re-enter an option number from the list above: " << endl;
			}

			if (strategy == 0) strategy = rand() % 3 + 1;

			Player* p;
			switch (strategy) {
			case 1:
				p = new Player(to_string(i), new Aggressive());
				players.push_back(p);
				break;
			case 2:
				p = new Player(to_string(i), new Benevolent());
				players.push_back(p);
				break;
			case 3:
				p = new Player(to_string(i), new Benevolent()); // Cheater
				players.push_back(p);
				break;
			}
		}

		// Game size selection
		int game_size = get_input(1, 5, "Select number of games to be played (1-5): ");

		// Max turn selection
		int max_turns = get_input(3, 50, "Select number of turns for game to be considered draw (3-50): ");

		// Set up the games per map
		for (int i = 0; i < map_selection.size(); i++) {
			for (int i = 0; i < game_size; i++) {

			}
		}


		cout << "M : " << endl;
		cout << "P : ";
		for (int i = 0; i < players.size(); i++) {
			cout << typeid(players[i]).name() << " ";
		}
		cout << "G : " << game_size << endl;
		cout << "D : " << max_turns << endl;


	}
}

#include "stdafx.h"
#include "Game.h"
#include "GameMode.h"
#include <filesystem>
#include "Human.h"
#include "Benevolent.h"
#include "Aggressive.h"
#include "Cheater.h"
#include "StrategyFactory.h"

using std::experimental::filesystem::directory_iterator;

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
		for (const auto p : directory_iterator("Maps")) {
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
		vector<std::string> player_strategy;
		cout << "Strategy options\n[0] Random player\n[1] Aggressive computer player\n[2] Benevolent computer player\n[3] Cheater" << endl;
		for (int i = 0; i < player_size; i++) {
			cout << "\nPlayer " << i << " strategy option: ";
			cin >> strategy;
			while (strategy < 0 || strategy > 3) {
				cout << "Invalid option. Please re-enter an option number from the list above: " << endl;
				cin >> strategy;
			}

			if (strategy == 0) strategy = rand() % 3 + 1; // Replace with Random()

			Player* p;
			switch (strategy) {
			case 1:
				player_strategy.push_back("Aggressive");
				break;
			case 2:
				player_strategy.push_back("Benevolent");
				break;
			case 3:
				player_strategy.push_back("Cheater");
				break;
			}
		}

		// Game size selection
		int game_size = get_input(1, 5, "Select number of games to be played (1-5): ");

		// Max turn selection
		int max_turns = get_input(3, 50, "Select number of turns for game to be considered draw (3-50): ");

		string results;
		for (int i = 0; i < game_size; i++) {
			results.append("\tGame " + std::to_string((i+1)));
		}
		
		// Set up the games per map
		for (int i = 0; i < map_selection.size(); i++) {
			results.append("\nMap " + std::to_string((i + 1)));
			for (int j = 0; j < game_size; j++) {
				vector<Player*> p;
				for (int z = 0; z < player_size; z++) {
					p.push_back(new Player(std::to_string(z), StrategyFactory::createStrategy(player_strategy[z])));
				}
				Game game(p, map_selection[i]);
				game.init_game_deck();
				game.init_startup_phase();
				results.append("\t" + game.init_main_game_loop(max_turns));
			}
		}

		cout << "M : ";
		for (int i = 0; i < map_size; i++) {
			cout << map_selection[i] << " ";
		}
		cout << endl;
		cout << "P : ";
		for (int i = 0; i < player_strategy.size(); i++) {
			cout << player_strategy[i] << " ";
		}
		cout << endl;
		cout << "G : " << game_size << endl;
		cout << "D : " << max_turns << endl;

		cout << results;
	}
}

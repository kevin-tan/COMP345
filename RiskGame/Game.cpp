#include "stdafx.h"
#include <filesystem>
#include "MapLoader.h"
#include "Game.h"

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::exception;
using std::filesystem::directory_iterator;

void Game::init_game_players() {
	cout << "Enter number of players (2-6 players)" << endl;

	int number_of_players = 0;
	cin >> number_of_players;
	while (number_of_players < 2 || number_of_players > 6) {
		cout << "Please re-enter a valid number of players (2-6 players)" << endl;
		cin >> number_of_players;
	}

	for (int i = 0; i < number_of_players; i++) {
		game_players.push_back(Player());
	}

}

void Game::init_game_map() {
	vector<string> map_files;

	//Reads files in directory
	for (const auto p : directory_iterator("Maps")) {
		map_files.push_back(p.path().string());
	}

	//Allows the user to select a map from the /Maps directory
	//Loops until a valid map is selected
	while (true) {
		try {
			cout << "Select a map file from the list below (found in /Maps): " << endl;
			for (int i = 0; i < map_files.size(); i++) {
				cout << "[" << i << "] " << map_files[i] << endl;
			}

			int index;
			cin >> index;
			if (index < 0 || index >= map_files.size()) {
				throw exception(("Invalid index " + std::to_string(index) + ". Please enter a valid index from the list.").c_str());
			}

			Map map = read_map_file(map_files[index]);
			game_map = map;
			break;
		}
		catch (exception e) {
			cout << e.what() << "\nPlease select another map.\n" << endl;
		}
	}
}

void Game::init_game_deck() {
	Deck deck(game_map.get_countries().size());
	game_deck = deck;
}

std::vector<Player> Game::get_game_players() {
	return game_players;
}

Map* Game::get_game_map() {
	return &game_map;
}

Deck* Game::get_game_deck() {
	return &game_deck;
}

#include "stdafx.h"
#include <filesystem>
#include <algorithm>
#include <random>
#include <chrono>
#include "MapLoader.h"
#include "Game.h"

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::exception;
using std::default_random_engine;
using std::shuffle;
using std::begin;
using std::end;
using std::filesystem::directory_iterator;
using std::chrono::system_clock;

void Game::init_game_players() {
	cout << "Enter number of players (2-6 players)" << endl;

	int number_of_players = 0;
	cin >> number_of_players;
	while (number_of_players < 2 || number_of_players > 6) {
		cout << "Please re-enter a valid number of players (2-6 players)" << endl;
		cin >> number_of_players;
	}

	for (int i = 0; i < number_of_players; i++) {
		game_players.push_back(Player(std::to_string(i)));
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

void Game::init_startup_phase() {
	shuffle_players();

	distribute_countries();

	distribute_armies();
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

void Game::shuffle_players() {
	unsigned seed = system_clock::now().time_since_epoch().count();
	auto rng = default_random_engine(seed);
	shuffle(begin(game_players), end(game_players), rng);
}

void Game::distribute_countries() {
	unsigned seed = system_clock::now().time_since_epoch().count();
	auto rng = default_random_engine(seed);
	shuffle(begin(game_map.get_countries()), end(game_map.get_countries()), rng);

	for (int i = 0; i < game_map.get_countries().size(); i++) {
		game_players[i%game_players.size()].add_country(game_map.get_countries()[i], game_map);
	}
}

void Game::distribute_armies() {
	for (int i = 0; i < get_number_of_armies(); i++) {
		for (int j = 0; j < game_players.size(); j++) {
			cout << "Player " + game_players[j].get_name() << "'s turn to place an army unit.\nSelect an option from the list below: " << endl;
			int option_number = 0;
			for (Vertex v : game_players[j].get_countries()) {
				cout << "[" << option_number++ << "] " << game_map.get_graph()[v].country << "(" << game_map.get_graph()[v].army_size << " army unit(s))" << endl;
			}

			int selection;
			cin >> selection;
			game_map.add_army(game_players[j].get_countries()[selection]);
		}
	}
}

int Game::get_number_of_armies() {
	switch (game_players.size()) {
	case 2:
		return 10;
	case 3:
		return 35;
	case 4:
		return 30;
	case 5:
		return 25;
	case 6:
		return 20;
	}
}

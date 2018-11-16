#include "stdafx.h"
#include <filesystem>
#include <algorithm>
#include <random>
#include <chrono>
#include "MapLoader.h"
#include "Game.h"
#include "PhaseObserver.h"
#include "Human.h"
#include "Benevolent.h"
#include "Aggressive.h"

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
using std::to_string;
using std::experimental::filesystem::directory_iterator;
using std::chrono::system_clock;

Game::Game() {
	// Init phase viewer
	this->ISubject::add_listener(new PhaseObserver(this));
}

Game::~Game() = default;

void Game::init_game_players() {
	//Gets number of players and initializes player objects.
	cout << "Enter number of players (2-6 players)" << endl;

	int number_of_players = 0;
	cin >> number_of_players;
	while (number_of_players < 2 || number_of_players > 6) {
		cout << "Please re-enter a valid number of players (2-6 players)" << endl;
		cin >> number_of_players;
	}

	cout << "Strategy options\n[0] Human player\n[1] Aggressive computer player\n[2] Benevolent computer player" << endl;

	int strategy;

	for (int i = 0; i < number_of_players; i++) {
		cout << "\nPlayer "<< i << " strategy option: " << endl;
		cin >> strategy;
		while (strategy < 0 || strategy > 2) {
			cout << "Invalid option. Please re-enter an option number from the list above: " << endl;
		}

		Player* p;
		switch (strategy) {
		case 0:
			p = new Player(to_string(i), new Human());
			game_players.push_back(p);
			break;
		case 1:
			p = new Player(to_string(i), new Aggressive());
			game_players.push_back(p);
			break;
		case 2:
			p = new Player(to_string(i), new Benevolent());
			game_players.push_back(p);
			break;
		}
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
				throw exception(("Invalid index " + to_string(index) + ". Please enter a valid index from the list.").c_str());
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
	//Initializes game deck with number of countries from loaded map
	Deck deck(game_map.get_countries().size());
	game_deck = deck;
}

void Game::init_startup_phase() {
	shuffle_players();
	distribute_countries();
	distribute_armies();
}

void Game::init_main_game_loop() {
	int change_strategy;
	while (true) {
		for (Player* player : game_players) {
			player->reinforce(this);
			player->attack(this);
			player->fortify(this);
			
			cout << "Would you like to change a player's strategy? (Press 1)" << endl;
			cin >> change_strategy;

			string input_name = "";
			if(change_strategy == 1) {
				cout << "Enter player name: " << endl;
				cin >> input_name;
				while(std::stoi(input_name) < 0 || std::stoi(input_name) >= game_players.size()) {
					cout << "Invalid name. Re-enter player name: " << endl;
					cin >> input_name;
				}

				int strategy;
				cout << "Strategy options\n[0] Human player\n[1] Aggressive computer player\n[2] Benevolent computer player" << endl;
				cout << "\nPlayer " << input_name << " strategy option: " << endl;
				cin >> strategy;
				while (strategy < 0 || strategy > 2) {
					cout << "Invalid option. Please re-enter an option number from the list above: " << endl;
				}

				//TODO Something very broken happens with what I did in set_strategy and this heap allocation... but pretty sure everything else is good
				for(Player* p : game_players) {
					if(p->get_name() == input_name) {
						switch (strategy) {
						case 0:
							p->get_player_strategy().set_strategy(new Human());
							break;
						case 1:
							p->get_player_strategy().set_strategy(new Aggressive());
							break;
						case 2:
							p->get_player_strategy().set_strategy(new Benevolent());
							break;
						}
					}
				}
			} 
		}
	}
}

std::vector<Player*> Game::get_game_players() const {
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
		game_players[i%game_players.size()]->add_country(game_map.get_countries()[i], game_map);
	}
}

void Game::distribute_armies() {
	//Conducts round robin placement of armies
	//Initially places 1 army on each of player's owned territories
	vector<int> remaining_armies(game_players.size(), get_number_of_armies());
	cout << "-------------------------\nPlacing initial armies...\n-------------------------\n" << endl;
	place_initial_armies(remaining_armies);

	cout << "--------------------------------------------\nProceeding to round-robin army placement...\n--------------------------------------------\n" << endl;
	while (armies_remain(remaining_armies)) {
		for (int i = 0; i < game_players.size(); i++) {
			if (remaining_armies[i] != 0) {
				cout << "Player " + game_players[i]->get_name() << "'s turn to place army units on one of their territories.\nSelect an option from the list below: " << endl;
				cout << remaining_armies[i] << " army units remain..." << endl;
				int option_number = 0;
				for (Vertex v : game_players[i]->get_countries()) {
					cout << "[" << option_number++ << "] " << game_map.get_graph()[v].country << "(" << game_map.get_graph()[v].army_size << " army unit(s))" << endl;
				}

				int selection;
				cin >> selection;
				while (selection < 0 || selection >= game_players[i]->get_countries().size()) {
					cout << "Invalid selection. Please enter a valid selection (0-" << game_players[i]->get_countries().size() - 1 << "):" << endl;
					cin >> selection;
				}

				cout << "How many units would you like to place?" << endl;
				int army_selection;
				cin >> army_selection;
				while (army_selection < 1 || army_selection > remaining_armies[i]) {
					cout << "Invalid number of units. Input must be between 1-" << remaining_armies[i] << endl;
					cin >> army_selection;
				}

				game_map.add_armies(game_players[i]->get_countries()[selection], army_selection);
				remaining_armies[i] -= army_selection;
			}
		}
	}
}

void Game::place_initial_armies(vector<int>& remaining_armies) {
	for (int i = 0; i < game_players.size(); i++) {
		for (Vertex v : game_players[i]->get_countries()) {
			game_map.add_armies(v, 1);
			remaining_armies[i]--;
		}
	}
}

bool Game::armies_remain(vector<int>& remaining_armies) {
	for (int i : remaining_armies) {
		if (i != 0) { return true; }
	}
	return false;
}

int Game::get_number_of_armies() {
	switch (game_players.size()) {
	case 2:
		return 40;
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

bool Game::check_win_condition(Player* player) {
	return player->get_countries().size() == game_map.get_countries().size();
}

void Game::player0_win() {
	for (int i = 0; i < game_players.size(); i++) {
		game_players[i]->clear_countries_temp();
	}

	for (int i = 0; i < game_map.get_countries().size(); i++) {
		game_players[0]->add_country(game_map.get_countries()[i], game_map);
	}
}

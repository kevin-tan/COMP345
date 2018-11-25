#include "stdafx.h"

#include "Benevolent.h"

using std::string;

void Benevolent::execute_reinforce(Game* game, Player* player) {
	Map* map = game->get_game_map();

	// Initialize phase
	string phase_state = "Player " + player->get_name() + ": reinforce phase.\n";
	game->set_state(&phase_state);
	game->notify_all();

	int total_army, country_armies, continent_armies, exchange_armies = 0;

	// Countries bonus
	if (player->get_countries().size() / 3 <= 3)
		country_armies = 3;
	else
		country_armies = player->get_countries().size() / 3;

	// Continent bonus
	continent_armies = player->armies_from_continents(map);

	// Get part of reinforcement from the card exchange
	if (player->get_hand()->get_hand_size() >= 5) {
		while (player->get_hand()->get_hand_size() >= 5)
			exchange_armies += player->get_hand()->exchange(game->get_game_deck());
		phase_state.append("Phase " + player->get_name() + " has more than 5 cards, auto-exchanging for armies.\nPlayer " + player->get_name() + " received " + std::to_string(exchange_armies) + " number of armies.\n");
		game->notify_all();
	}
	while (player->get_hand()->can_exchange()) {
		exchange_armies += player->get_hand()->exchange(game->get_game_deck());
		phase_state.append("Phase " + player->get_name() + " chose to exchange cards more cards.\nPlayer " + player->get_name() + " received " + std::to_string(exchange_armies) + " number of armies.\n");
		game->notify_all();
	}
	total_army = country_armies + continent_armies + exchange_armies;

	while (total_army != 0) {
		vector<Vertex> weak_countries = weakest_countries(game, player);
		for (Vertex v : weak_countries) {
			if (total_army != 0) {
				phase_state.append("Player " + player->get_name() + " chose country " + map->get_graph()[v].country + " to add armies to.\n");
				phase_state.append("Player " + player->get_name() + " has " + std::to_string(total_army) + " army unit(s) to place.\n");

				map->add_armies(v, 1);
				total_army--;
				phase_state.append("Player " + player->get_name() + " reinforced country " + map->get_graph()[v].country + " with 1 army.\n");
				game->notify_all();
			} else {
				break;
			}
		}
	}

	phase_state.append("Player " + player->get_name() + " reinforcement phase terminating.\n");
	game->notify_all();
}

void Benevolent::execute_attack(Game* game, Player* player) {
	// Initialize phase
	string phase_state = "Player " + player->get_name() + ": attack phase.\n";
	game->set_state(&phase_state);

	phase_state.append("Player " + player->get_name() + " chose to skip attack phase.\n");
	phase_state.append("Player " + player->get_name() + " attack phase terminating.\n");
	game->notify_all();
}

void Benevolent::execute_fortify(Game* game, Player* player) {
	// Initialize phase
	string phase_state = "Player " + player->get_name() + ": fortify phase.\n";
	game->set_state(&phase_state);

	vector<Vertex> weak_countries = weakest_countries(game, player);

	bool success = false;
	for (Vertex weak_country : weak_countries) {
		for (Vertex adjacency : game->get_game_map()->get_adjacent_countries(weak_country)) {
			auto adj_country = game->get_game_map()->get_graph()[adjacency];
			auto weak = game->get_game_map()->get_graph()[weak_country];
			if (adj_country.player == player && adj_country.army_size - weak.army_size > 1) {
				phase_state.append("Player " + player->get_name() + " chose country " + adj_country.country + " to move armies from!\n");
				phase_state.append("Player " + player->get_name() + " chose country " + weak.country + " to move armies to!\n");

				int total_armies = adj_country.army_size + weak.army_size;
				int weak_country_armies = total_armies / 2;
				int adjacency_armies = total_armies - weak_country_armies;
				int move_armies = adj_country.army_size - adjacency_armies;

				int& weak_army = weak.army_size;
				int& adj_army = adj_country.army_size;

				weak_army = weak_country_armies;
				adj_army = adjacency_armies;

				phase_state.append("Player " + player->get_name() + " chose to move " + std::to_string(move_armies) + " from country " + adj_country.country + "!\n");
				phase_state.append("Country " + adj_country.country + " now has " + std::to_string(adjacency_armies) + " armies!\nCountry " + weak.country + " now has " + std::to_string(weak_country_armies) + " armies!\n");
				game->notify_all();
				game->get_game_map()->notify_all();

				success = true;
				break;
			}
		}
		if (success) break;
	}

	if (!success) {
		phase_state.append("Player " + player->get_name() + " skipped fortifying phase.\n");
	}

	phase_state.append("Player " + player->get_name() + " fortify phase terminating.\n");
	game->notify_all();
}

std::string Benevolent::get_strategy_name() {
	return "Benevolent";
}

vector<Vertex> Benevolent::weakest_countries(Game* game, Player* player) {
	// Populates vector with player's weakest countries
	int least_armies = 1000;
	for (Vertex v : player->get_countries()) {
		if (game->get_game_map()->get_graph()[v].army_size < least_armies) {
			least_armies = game->get_game_map()->get_graph()[v].army_size;
		}
	}

	vector<Vertex> weakest_countries;
	for (Vertex v : player->get_countries()) {
		if (game->get_game_map()->get_graph()[v].army_size == least_armies) {
			weakest_countries.push_back(v);
		}
	}

	return weakest_countries;
}

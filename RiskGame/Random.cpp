#include "stdafx.h"
#include "Random.h"
#include <chrono>
#include <random>

using std::default_random_engine;
using std::shuffle;
using std::begin;
using std::end;
using std::string;
using std::chrono::system_clock;

void Random::execute_reinforce(Game* game, Player* player) {
	Map* map = game->get_game_map();

	// Initialize phase
	string phase_state = "Player " + player->get_name() + ": reinforce phase.\n";
	game->set_state(&phase_state);

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
		phase_state.append("Player " + player->get_name() + " has more than 5 cards, auto-exchanging for armies.\nPlayer " + player->get_name() + " received " + std::to_string(exchange_armies) + " number of armies.\n");
		game->notify_all();
	}
	while (player->get_hand()->can_exchange()) {
		exchange_armies += player->get_hand()->exchange(game->get_game_deck());
		phase_state.append("Player " + player->get_name() + " chose to exchange their cards.\nPlayer " + player->get_name() + " received " + std::to_string(exchange_armies) + " number of armies.\n");
		game->notify_all();
	}
	total_army = country_armies + continent_armies + exchange_armies;

	// Pick random
	srand(time(0));
	int rand_country_index = rand() % player->get_countries().size();

	Vertex rand_country = player->get_countries()[rand_country_index];

	phase_state.append("Player " + player->get_name() + " chose country " + map->get_graph()[rand_country].country + " to add armies to.\n");
	phase_state.append("Player " + player->get_name() + " has " + std::to_string(total_army) + " army unit(s) to place.\n");

	map->add_armies(rand_country, total_army);

	phase_state.append("Player " + player->get_name() + " reinforced country " + map->get_graph()[rand_country].country + " with " + std::to_string(total_army) + " army unit(s). Country " + map->get_graph()[rand_country].country + " now has " + std::to_string(map->get_graph()[rand_country].army_size) + " army unit(s)\n");
	game->notify_all();


	phase_state.append("Player " + player->get_name() + " reinforcement phase terminating.\n");
	game->notify_all();
}

//Reinforces random a random country, attacks a random number of times a random country, and fortifies a random country
void Random::execute_attack(Game* game, Player* player) {
	// Way I'd go about it:
	// Shuffle the vector of countries
	// For each it
	// Pick a random target (who cares)
	// Calc. number of attacks possible and random gen.
	// Do until # of attacks is reached or conquered or lost
	// End for each
	// Done wrecking all its forces. (likely gonna be one or two anyway...)
	
	// Initialize phase
	string phase_state = "Player " + player->get_name() + ": attack phase.\n";
	game->set_state(&phase_state);

	phase_state.append("Player " + player->get_name() + " chose to skip attack phase.\n");
	phase_state.append("Player " + player->get_name() + " attack phase terminating.\n");
	game->notify_all();
}

void Random::execute_fortify(Game* game, Player* player) {
	// Initialize phase
	string phase_state = "Player " + player->get_name() + ": fortify phase.\n";
	game->set_state(&phase_state);

	unsigned seed = system_clock::now().time_since_epoch().count();
	auto rng = default_random_engine(seed);
	vector<Vertex> player_countries = player->get_countries();
	shuffle(begin(player_countries), end(player_countries), rng);

	int most_armies = 1;
	Vertex strongest_source = NULL;
	Vertex fortify_target = NULL;
	for (Vertex target : player_countries) {
		for (Vertex source : game->get_game_map()->get_adjacent_countries(target)) {
			auto country = game->get_game_map()->get_graph()[source];
			if (country.army_size > most_armies && abs(country.army_size - game->get_game_map()->get_graph()[target].army_size) > 1) {
				fortify_target = target;
				strongest_source = source;
				most_armies = country.army_size;
			}
		}
		if (most_armies > 1) break;
	}

	if (strongest_source == NULL) {
		phase_state.append("Player " + player->get_name() + " skipped fortifying phase.\n");
	}
	else {
		auto& source_node = game->get_game_map()->get_graph()[strongest_source];
		auto& target_node = game->get_game_map()->get_graph()[fortify_target];

		phase_state.append("Player " + player->get_name() + " chose country " + source_node.country + " to move armies from!\n");
		phase_state.append("Player " + player->get_name() + " chose country " + target_node.country + " to move armies to!\n");
		
		int total_armies = source_node.army_size + target_node.army_size;
		int target_armies = total_armies / 2;
		int source_armies = total_armies - target_armies;
		int move_armies = abs(source_node.army_size - source_armies);

		int& target_army = target_node.army_size;
		int& source_army = source_node.army_size;

		target_army = target_armies;
		source_army = source_armies;

		phase_state.append("Player " + player->get_name() + " chose to move " + std::to_string(move_armies) + " from country " + source_node.country + "!\n");
		phase_state.append("Country " + target_node.country + " now has " + std::to_string(target_node.army_size) + " armies!\nCountry " + source_node.country + " now has " + std::to_string(source_node.army_size) + " armies!\n");
		game->notify_all();
	}

	phase_state.append("Player " + player->get_name() + " fortify phase terminating.\n");
	game->notify_all();
}

std::string Random::get_strategy_name() {
	return "Random";
}

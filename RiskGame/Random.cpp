#include "stdafx.h"
#include "Random.h"

using std::string;

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

	while(total_army != 0) {
		int rand_country_index = rand() % player->get_countries().size();
		int rand_armies = (rand() % total_army) + 1;
		total_army -= rand_armies;

		Vertex rand_country = player->get_countries()[rand_country_index];

		phase_state.append("Player " + player->get_name() + " chose country " + map->get_graph()[rand_country].country + " to add armies to.\n");
		phase_state.append("Player " + player->get_name() + " has " + std::to_string(total_army) + " army unit(s) to place.\n");

		map->add_armies(rand_country, total_army);

		phase_state.append("Player " + player->get_name() + " reinforced country " + map->get_graph()[rand_country].country + " with " + std::to_string(rand_armies) + " army unit(s). Country " + map->get_graph()[rand_country].country + " now has " + std::to_string(map->get_graph()[rand_country].army_size) + " army unit(s)\n");
		game->notify_all();
	}

	phase_state.append("Player " + player->get_name() + " reinforcement phase terminating.\n");
	game->notify_all();
}

void Random::execute_attack(Game* game, Player* player) {
	std::cout << "Hi from attack" << std::endl;
}

void Random::execute_fortify(Game* game, Player* player) {
	std::cout << "Hi from fortify" << std::endl;
}

std::string Random::get_strategy_name() {
	return "Random";
}

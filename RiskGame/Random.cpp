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
using std::cout;
using std::cin;

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

void Random::execute_attack(Game* game, Player* player) {
	// Initialize phase
	string phase_state = "Player " + player->get_name() + ": attack phase.\n";
	game->set_state(&phase_state);

	phase_state.append("Player " + player->get_name() + " chose to attack.\n");

	for (Vertex attack_source : player->get_countries()) {
		// For all attack sources, find valid attack sources (army size is more than 1)
		auto& source = game->get_game_map()->get_graph()[attack_source];
		if (source.army_size >= 1) {
			// Pick random attack target
			srand(time(0));
			int rand_country_index = rand() % game->get_game_map()->get_adjacent_countries(attack_source).size();
			Vertex rand_target = game->get_game_map()->get_adjacent_countries(attack_source)[rand_country_index];
			auto& target = game->get_game_map()->get_graph()[rand_target];

			if (target.player != player) {
				// Pick random number of times to attack assuming 1 attack dice is rolled
				int number_of_attacks = rand() % source.army_size;

				// If RNG picks 0, no attack
				if (number_of_attacks != 0) {
					phase_state.append("Player " + player->get_name() + " chose " + source.country + " to attack from.\n");
					phase_state.append("Player " + player->get_name() + " chose " + target.country + " to attack.\n");
				
					// Attack for random number of attacks, STOP if source army runs out, or target army is conquered
					while (number_of_attacks > 0 && source.army_size > 1 && target.player != source.player) {
						// Pick random number of dice to roll
						int a_max_dice = source.army_size - 1 >= 3 ? 3 : source.army_size - 1;
						int a_rand_dice = (rand() % a_max_dice) + 1;
						phase_state.append("Attacking Player " + player->get_name() + " chose " + std::to_string(a_rand_dice) + " dice to roll.\n");

						vector<int> attack_rolls = player->get_dice_rolling_facility()->rollDice(a_rand_dice);
						vector<int> defend_rolls;

						if (target.player->is_human()) {
							// Defender rolling chosen number dice for attack per army (army size)
							game->notify_all();
							int d_max_dice = target.army_size >= 2 ? 2 : target.army_size;
							int d_num_roll = 0;
							Player* p = target.player;
							cout << "Player " << p->get_name() << ", choose number of dice to roll to defend (1-" << d_max_dice << "): ";
							cin >> d_num_roll;
							while (d_num_roll <= 0 || d_num_roll > d_max_dice) {
								cout << "Player " << p->get_name() << ", choose number of dice to roll to defend (1-" << d_max_dice << ") only: ";
								cin >> d_num_roll;
							}

							phase_state.append("Defending Player " + p->get_name() + " chose " + std::to_string(d_num_roll) + " dice to roll.\n");
							game->notify_all();

							defend_rolls = player->get_dice_rolling_facility()->rollDice(d_num_roll);
						}
						else {
							int d_max_dice = target.army_size >= 2 ? 2 : target.army_size;
							phase_state.append("Defending Player " + target.player->get_name() + " chose " + std::to_string(d_max_dice) + " dice to roll.\n");

							defend_rolls = player->get_dice_rolling_facility()->rollDice(d_max_dice);
						}

						// Eliminating army phase
						int max_army = attack_rolls.size() > defend_rolls.size() ? attack_rolls.size() : defend_rolls.size();
						int d_index = 0, a_index = 0;
						bool elimination_phase = true;
						while (elimination_phase) {
							// Ref to army size of attacker and defender
							int& atk_army_size = source.army_size;
							int& def_army_size = target.army_size;
							const int atk_army_size_before = atk_army_size;

							if (d_index < defend_rolls.size() && a_index < attack_rolls.size()) {
								if (defend_rolls[d_index] > attack_rolls[a_index]) {
									phase_state.append("Defender Player " + target.player->get_name() + " beat the attacker " + player->get_name() + " with a roll of " + std::to_string(defend_rolls[d_index]) + " vs " + std::to_string(attack_rolls[a_index]) + "!\n");
									phase_state.append("Attacking Player " + player->get_name() + " has lost an army!\n");

									atk_army_size--;
									phase_state.append("Country " + source.country + " now has " + std::to_string(atk_army_size) + " armies!\n");
									phase_state.append("Country " + target.country + " now has " + std::to_string(def_army_size) + " armies!\n");
								}
								else if (defend_rolls[d_index] == attack_rolls[a_index]) {
									phase_state.append("Defender Player " + target.player->get_name() + " matched the attacker " + player->get_name() + " with a roll of " + std::to_string(attack_rolls[a_index]) + "!\n");
									phase_state.append("Attacking Player " + player->get_name() + " has lost an army!\n");

									atk_army_size--;
									phase_state.append("Country " + source.country + " now has " + std::to_string(atk_army_size) + " armies!\n");
									phase_state.append("Country " + target.country + " now has " + std::to_string(def_army_size) + " armies!\n");
								}
								else {
									phase_state.append("Defender Player " + target.player->get_name() + " lost to the attacker " + player->get_name() + " with a roll of " + std::to_string(defend_rolls[d_index]) + " vs " + std::to_string(attack_rolls[a_index]) + "!\n");
									phase_state.append("Defender Player " + target.player->get_name() + " has lost an army!\n");

									def_army_size--;
									phase_state.append("Country " + source.country + " now has " + std::to_string(atk_army_size) + " armies!\n");
									phase_state.append("Country " + target.country + " now has " + std::to_string(def_army_size) + " armies!\n");
								}
								d_index++;
								a_index++;
							}
							else {
								if (def_army_size == 0) {
									phase_state.append("Attacking Player " + player->get_name() + " successfully took over country " + target.country + " from Player " + target.player->get_name() + "!\nPlayer " + player->get_name() + " now owns country " + target.country + "\n");

									atk_army_size--;
									def_army_size = 1;

									Player* defeated_player = target.player;
									std::string name = defeated_player->get_name();

									target.player->remove_country(rand_target, *game->get_game_map());
									player->add_country(rand_target, *game->get_game_map());
									phase_state.append("Player " + player->get_name() + " moved 1 army unit(s) from country " + source.country + " to " + target.country + "!\n");
									phase_state.append("Country " + source.country + " now has " + std::to_string(atk_army_size) + " armies!\n");
									phase_state.append("Country " + target.country + " now has " + std::to_string(def_army_size) + " armies!\n");

									if (game->check_player_eliminated(defeated_player)) {
										phase_state.append("Player " + name + " has been eliminated. They have been removed from the game.");
									}

									if (game->check_win_condition(player)) {
										game->notify_all();
										game->get_game_map()->notify_all();
										game->get_running() = false;
										return;
									}
								}
								elimination_phase = false;
							}
							game->notify_all();
							game->get_game_map()->notify_all();
						}
						number_of_attacks--;
					}
				}
			}
		}
	}
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

#include "stdafx.h"
#include "Aggressive.h"

using std::string;
using std::cout;
using std::endl;
using std::cin;

void Aggressive::execute_reinforce(Game* game, Player* player) {
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

	Vertex strongest = strongest_country(game, player->get_countries());

	phase_state.append("Player " + player->get_name() + " chose country " + map->get_graph()[strongest].country + " to add armies to.\n");
	phase_state.append("Player " + player->get_name() + " has " + std::to_string(total_army) + " army unit(s) to place.\n");

	map->add_armies(strongest, total_army);

	phase_state.append("Player " + player->get_name() + " reinforced country " + map->get_graph()[strongest].country + " with " + std::to_string(total_army) + " army unit(s).\n");
	phase_state.append("Player " + player->get_name() + " reinforcement phase terminating.\n");
	game->notify_all();
}

void Aggressive::execute_attack(Game* game, Player* player) {
	// Initialize phase
	string phase_state = "Player " + player->get_name() + ": attack phase.\n";
	game->set_state(&phase_state);

	phase_state.append("Player " + player->get_name() + " chose to attack.\n");

	Vertex attack_source = strongest_country(game, player->get_countries());
	auto source = game->get_game_map()->get_graph()[attack_source];

	phase_state.append("Player " + player->get_name() + " chose " + source.country + " to attack from.\n");

	for (Vertex v : game->get_game_map()->get_adjacent_countries(attack_source)) {
		auto target = game->get_game_map()->get_graph()[v];
		if (target.player != player) {
			// Aggressive player attacks as much as possible
			//TODO FIX
			while (source.army_size > 1 && game->get_game_map()->get_graph()[v].player != player) {
				phase_state.append("Player " + player->get_name() + " chose " + target.country + " to attack.\n");

				int a_max_dice = source.army_size - 1 >= 3 ? 3 : source.army_size - 1;
				phase_state.append("Attacking Player " + player->get_name() + " chose " + std::to_string(a_max_dice) + " dice to roll.\n");

				vector<int> attack_rolls = player->get_dice_rolling_facility()->rollDice(a_max_dice);

				// Defend
				vector<int> defend_rolls;

				if (target.player->is_human()) {
					// Defender rolling chosen number dice for attack per army (army size)
					const int number_of_defends = target.army_size;
					int d_max_dice = number_of_defends >= 2 ? 2 : number_of_defends;
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
						}
						else if (defend_rolls[d_index] == attack_rolls[a_index]) {
							phase_state.append("Defender Player " + target.player->get_name() + " matched the attacker " + player->get_name() + " with a roll of " + std::to_string(attack_rolls[a_index]) + "!\n");
							phase_state.append("Attacking Player " + player->get_name() + " has lost an army!\n");
							// Other player dice will not matter, exit elimination phase
							atk_army_size--;
							elimination_phase = false;
						}
						else {
							phase_state.append("Defender Player " + target.player->get_name() + " lost to the attacker " + player->get_name() + " with a roll of " + std::to_string(defend_rolls[d_index]) + " vs " + std::to_string(attack_rolls[a_index]) + "!\n");
							phase_state.append("Defender Player " + target.player->get_name() + " has lost an army!\n");
							def_army_size--;
						}
						d_index++;
						a_index++;
					}
					else {
						if (def_army_size == 0) {
							phase_state.append("Attacking Player " + player->get_name() + " successfully took over country " + target.country + " from Player " + target.player->get_name() + "!\nPlayer " + player->get_name() + " now owns country " + target.country + "\n");

							atk_army_size--;
							def_army_size = 1;

							target.player->remove_country(v, *game->get_game_map());
							player->add_country(v, *game->get_game_map());
							phase_state.append("Player " + player->get_name() + " moved 1 army unit(s) from country " + source.country + " to " + target.country + "!\n");
							phase_state.append("Country " + source.country + " now has " + std::to_string(atk_army_size) + " armies!\n");
							phase_state.append("Country " + target.country + " now has " + std::to_string(def_army_size) + " armies!\n");
						}
						elimination_phase = false;
					}
					game->notify_all();
				}
			}

		}
	}
	phase_state.append("Player " + player->get_name() + " attack phase terminating.\n");
	game->notify_all();
}

void Aggressive::execute_fortify(Game* game, Player* player) {
	//TODO tougher than i thought
	//TODO possibly just look at every territory+adjacenecy and find most optimal combination ... that shouldn't be as complicated

	// Initialize phase
	// string phase_state = "Player " + player->get_name() + ": fortify phase.\n";
	// game->set_state(&phase_state);
	//
	// Vertex target = strongest_country(game, player->get_countries());
	// Vertex source = strongest_country(game, game->get_game_map()->get_adjacent_countries(target));
	//
	// while(game->get_game_map()->get_graph()[source].army_size == 1) {
	// 	for(Vertex adjacency : game->get_game_map()->get_adjacent_countries(target)) {
	// 		if()
	// 	}
	// }

}

Vertex Aggressive::strongest_country(Game* game, vector<Vertex> countries) {
	int most_armies = 0;
	Vertex strongest;
	for (Vertex v : countries) {
		auto country = game->get_game_map()->get_graph()[v];
		if (country.army_size > most_armies) {
			strongest = v;
			most_armies = country.army_size;
		}
	}

	return strongest;
}

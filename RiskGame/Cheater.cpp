#include "stdafx.h"
#include "Cheater.h"

using std::string;

void Cheater::execute_reinforce(Game * game, Player * player) {
	Map* map = game->get_game_map();
	game->get_game_map()->notify_all();
	// Initialize phase
	string phase_state = "Player " + player->get_name() + ": reinforce phase.\n";
	game->set_state(&phase_state);

	// Double countries
	for (Vertex v : player->get_countries()) {
		map->add_armies(v, map->get_graph()[v].army_size);
	}
	phase_state.append("Player " + player->get_name() + " have doubled number of armies on all its countries \n");
	phase_state.append("Player " + player->get_name() + " reinforcement phase terminating.\n");
	game->notify_all();
	game->get_game_map()->notify_all();
}

void Cheater::execute_attack(Game* game, Player* player) {
	// Initialize phase
	string phase_state = "Player " + player->get_name() + ": attack phase.\n";
	game->set_state(&phase_state);
	phase_state.append("Player " +player->get_name() + " has conquered: ");
	vector<Vertex> initial_countries = player->get_countries();
	vector<Vertex>::iterator it;
	// Conquer all the neighbors of all its countries
	for (Vertex v : initial_countries) {
		for (Vertex adjacent : game->get_game_map()->get_adjacent_countries(v)) {

			// Conquer if country is not owned already
			vector<Vertex> temp = player->get_countries();
			it = find(temp.begin(), temp.end(), adjacent);
			if (it == temp.end()) {
				game->get_game_map()->get_graph()[adjacent].player->remove_country(adjacent, *(game->get_game_map()));
				player->add_country(adjacent, *(game->get_game_map()));
				phase_state.append(game->get_game_map()->get_graph()[adjacent].country + ", ");
			}
		}
	}
	phase_state.at(phase_state.length() - 2) = '.';
	phase_state.append("\nPlayer " + player->get_name() + " has conquered all neighboring countries.\n");
	phase_state.append("Player " + player->get_name() + " attack phase terminating.\n");
	game->notify_all();
	game->get_game_map()->notify_all();

}

void Cheater::execute_fortify(Game * game, Player * player){
	// Initialize phase
	string phase_state = "Player " + player->get_name() + ": fortify phase.\n";
	game->set_state(&phase_state);
	phase_state.append("Player " + player->get_name() + " has fortified: ");
	for (Vertex v : player->get_countries()) {
		for (Vertex adjacent : game->get_game_map()->get_adjacent_countries(v)) {

			// Double armies if at least one adjacent belongs to the other player
			if (game->get_game_map()->get_graph()[adjacent].player->get_name().compare(player->get_name()) != 0){
				game->get_game_map()->add_armies(v, game->get_game_map()->get_graph()[v].army_size);
				phase_state.append(game->get_game_map()->get_graph()[v].country + ", ");
				break;
			}
		}
	}
	phase_state.at(phase_state.length() - 2) = '.';
	phase_state.append("\nPlayer " + player->get_name() + " fortify phase terminating.\n");
	game->notify_all();
	game->get_game_map()->notify_all();
}

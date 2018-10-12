#include "stdafx.h"
#include "MapLoader.h"
#include "Player.h"

int main() {
	Map map = read_map_file("World.map");

	Player player("Bob");

	Vertex x = map.find_country_vertex("Alaska");
	player.add_country(x, map);
	x = map.find_country_vertex("Ontario");
	player.add_country(x, map);
	x = map.find_country_vertex("Quebec");
	player.add_country(x, map);

	for(Vertex v : player.getCountries()) {
		std::cout << map.get_graph()[v].country << " is owned by " << map.get_graph()[v].player->getName() << std::endl;
	}

	int c = 0;
	std::cin >> c;
	return 0;
}

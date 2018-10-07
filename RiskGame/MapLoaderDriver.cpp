#include "stdafx.h"
#include "MapLoader.h"

int main() {
	Map map = read_map_file("World.map");

	map.print_all_edges(map.get_graph());
	map.get_all_vertices(map.get_graph());
	std::cout << "Continents: ";
	for(auto continent: map.get_continents())
	{
		std::cout << continent << " ";
	}
	std::cout << std::endl;
	return 0;
}
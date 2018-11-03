#include "stdafx.h"
#include "Map.h"

Graph& Map::generate_map(std::vector<std::string> map_info) {
	using namespace boost;
	using namespace std;

	graph = Graph();
	for (string info : map_info) {
		// Country with the out-edges
		Vertex main_vertex;
		stringstream ss(info);
		string token;

		// i == 0 is country name for node, i == 1 is continent for node
		int i = 0;
		bool vertexFound = true;
		while (getline(ss, token, DELIM)) {
			if (i == 0) {
				main_vertex = find_country_vertex(token);
				if (main_vertex == NULL_VERTEX) {
					vertexFound = false;
					main_vertex = add_vertex(graph);
					graph[main_vertex].country = token;
				}
				i++;
			} else if (i == 1) {
				if (graph[main_vertex].continent.empty()) {
					graph[main_vertex].continent = token;
				} else {
					if (vertexFound) {
						throw std::exception(("\nFailed to create map.\nCountry: " + graph[main_vertex].country +
							" already exist with continent " +
							graph[main_vertex].continent).c_str());
					}
				}
				i++;
			} else {
				// Find a vertext to see if it exists already
				Vertex v = find_country_vertex(token);
				if (v == NULL_VERTEX) {
					// Create new vertex
					v = add_vertex(graph);
					graph[v].country = token;
				}
				add_edge(main_vertex, v, graph);
			}
		}
	}

	cout << "Map sucessfully created." << endl;
	return graph;
}

Graph& Map::get_graph() {
	return graph;
}

std::unordered_set<std::string> Map::get_continents() const {
	return continents;
}

std::vector<Vertex> Map::get_adjacent_countries(const Vertex& vertex) const {
	std::vector<Vertex> adj_nodes = std::vector<Vertex>();
	for (auto i = boost::adjacent_vertices(vertex, graph); i.first != i.second; ++i.first) {
		adj_nodes.push_back(*i.first);
	}
	return adj_nodes;
}

Vertex Map::find_country_vertex(std::string const country) {
	for (auto i = vertices(graph); i.first != i.second; ++i.first) {
		if (graph[*i.first].country.compare(country) == 0)
			return *i.first;
	}
	return NULL_VERTEX;
}

Vertex& Map::add_territory(const std::string territory) {
	Vertex node = find_country_vertex(territory);
	if (node == NULL_VERTEX) {
		node = boost::add_vertex(graph);
		graph[node].country = territory;
	}
	return node;
}

void Map::add_continents(const std::string continent) {
	continents.insert(continent);
}

void Map::add_continent_to_territory(Vertex& territory, const std::string continent) {
	if (graph[territory].continent.empty()) {
		if (continents.count(continent)) {
			graph[territory].continent = continent;
		} else {
			throw std::exception(
				("Continent \'" + continent + "\' does not exist in the [Continents] header. Cannot create graph").
				c_str());
		}
	} else {
		throw std::exception(
			("Territory \'" + graph[territory].country + "\' exists with a continent already (" + graph[territory].
				continent + "). Cannot create graph.").c_str());
	}
}

void Map::add_adjacency(Vertex& territory, const std::string adj_territory) {
	Vertex adj_node = find_country_vertex(adj_territory);
	if (adj_node == NULL_VERTEX) {
		adj_node = boost::add_vertex(graph);
		graph[adj_node].country = adj_territory;
	}
	auto edge = boost::add_edge(territory, adj_node, graph);
}

void Map::traverse_edges(const Vertex& vertex) const {
	// Adjacent nodes to current vertex
	std::vector<Vertex> adj_nodes = get_adjacent_countries(vertex);
	Vertex current = vertex;
	while (true) {
		int country = 0;
		std::cout << "You are at " << graph[current].country << std::endl;
		std::cout << "Enter the number of the country you want to traverse to: " << std::endl;
		for (int i = 0; i < adj_nodes.size(); i++) {
			printf("[%d] %s \n", i, graph[adj_nodes[i]].country.c_str());
		}
		std::cin >> country;
		current = adj_nodes[country];
		adj_nodes = get_adjacent_countries(current);
	}
}

void Map::print_subgraph_continent(const Graph& graph, std::string const continent) const {
	using namespace std;
	cout << "Printing subgraph for continent " << continent << endl;
	auto pairs = edges(graph);
	for (auto i = pairs.first; i != pairs.second; ++i) {
		if (graph[source(*i, graph)].continent.compare(continent) == 0) {
			cout << "Edge : Country=" << graph[source(*i, graph)].country <<
				" & Continent=" << graph[source(*i, graph)].continent << " --> Country=" << graph[target(*i, graph)].
				country <<
				" & Continent=" << graph[target(*i, graph)].continent << endl;
		}
	}
}

void Map::print_all_edges(const Graph& graph) const {
	using namespace std;

	// Index map to get the index of the current vertex in the vector set
	IndexMap index = get(boost::vertex_index, graph);

	auto pairs = edges(graph);
	for (auto i = pairs.first; i != pairs.second; ++i) {
		cout << "Edge : index=" << index[source(*i, graph)] << " Country=" << graph[source(*i, graph)].country <<
			" & Continent=" << graph[source(*i, graph)].continent << " --> index=" << index[target(*i, graph)] <<
			" Country="
			<< graph[target(*i, graph)].country << " & Continent=" << graph[target(*i, graph)].continent << endl;
	}
	cout << endl;
}

void Map::print_all_vertices(const Graph& graph) const {
	IndexMap index = get(boost::vertex_index, graph);
	for (auto pair = vertices(graph); pair.first != pair.second; ++pair.first) {
		std::cout << index[*pair.first] << " : " << graph[*pair.first].country << " with continent " << graph[*pair.
			first].continent << " and adjacencies: ";
		std::vector<Vertex> v_adj = get_adjacent_countries(*pair.first);
		for (int i = 0; i < v_adj.size(); i++) {
			std::cout << graph[v_adj[i]].country;
			if (i < v_adj.size() - 1)
				std::cout << ", ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}


void Map::set_country_owner(Player* player, Vertex& vertex) {
	graph[vertex].player = player;
}
	// Get list of countries that belong to one continent
std::vector<std::string> Map::get_countries_in_continent(const Graph& graph, std::string const continent) const {
	using namespace std;
	set<string> temp;
	vector<string> lst;
	auto pairs = edges(graph);
	for (auto i = pairs.first; i != pairs.second; ++i) {
		if (graph[source(*i, graph)].continent.compare(continent) == 0) {
			temp.insert(graph[source(*i, graph)].country);
		}
	}
	for (string s : temp)
		lst.push_back(s);
	return lst;
}
	// Add army to the country
void Map::add_army_to_country(Graph& graph, std::string country, int army) {
		Vertex temp = find_country_vertex(country);
		if (graph[temp].army_size < 0)
			graph[temp].army_size = army;
		else
			graph[temp].army_size += army;
}


#include "stdafx.h"
#include "Map.h"
#include <random>

Map::Map()
{
	this->graph = Graph();
	this->continents = std::unordered_set<std::string>();
	this->countries = std::vector<Vertex>();
}

std::unordered_set<std::string> Map::get_continents() const
{
	return continents;
}

std::vector<Vertex> Map::get_adjacent_countries(const Vertex& vertex) const
{
	std::vector<Vertex> adj_nodes = std::vector<Vertex>();
	for (auto i = boost::adjacent_vertices(vertex, graph); i.first != i.second; ++i.first)
	{
		adj_nodes.push_back(*i.first);
	}
	return adj_nodes;
}

Vertex Map::find_country_vertex(std::string const country)
{
	for (auto i = vertices(graph); i.first != i.second; ++i.first)
	{
		if (graph[*i.first].country.compare(country) == 0)
			return *i.first;
	}
	return NULL_VERTEX;
}

Vertex& Map::add_territory(const std::string territory)
{
	Vertex node = find_country_vertex(territory);
	if (node == NULL_VERTEX)
	{
		node = boost::add_vertex(graph);
		graph[node].country = territory;
		countries.push_back(node);
	}
	return node;
}

void Map::add_continents(const std::string continent)
{
	continents.insert(continent);
}

void Map::add_continent_to_territory(Vertex& territory, const std::string continent)
{
	if (graph[territory].continent.empty())
	{
		if (continents.count(continent))
		{
			graph[territory].continent = continent;
		}
		else
		{
			throw std::exception(
				("Continent \'" + continent + "\' does not exist in the [Continents] header. Cannot create graph").
				c_str());
		}
	}
	else
	{
		throw std::exception(
			("Territory \'" + graph[territory].country + "\' exists with a continent already (" + graph[territory].
				continent + "). Cannot create graph.").c_str());
	}
}

void Map::add_adjacency(Vertex& territory, const std::string adj_territory)
{
	Vertex adj_node = find_country_vertex(adj_territory);
	if (adj_node == NULL_VERTEX)
	{
		adj_node = boost::add_vertex(graph);
		graph[adj_node].country = adj_territory;
		countries.push_back(adj_node);
	}
	auto edge = boost::add_edge(territory, adj_node, graph);
}

void Map::traverse_edges(const Vertex& vertex) const
{
	// Adjacent nodes to current vertex
	std::vector<Vertex> adj_nodes = get_adjacent_countries(vertex);
	Vertex current = vertex;
	while (true)
	{
		int country = 0;
		std::cout << "You are at " << graph[current].country << std::endl;
		std::cout << "Enter the number of the country you want to traverse to: " << std::endl;
		for (int i = 0; i < adj_nodes.size(); i++)
		{
			printf("[%d] %s \n", i, graph[adj_nodes[i]].country.c_str());
		}
		std::cin >> country;
		current = adj_nodes[country];
		adj_nodes = get_adjacent_countries(current);
	}
}

void Map::randomize()
{
	std::shuffle(std::begin(countries), std::end(countries), std::default_random_engine{});
}


void Map::set_country_owner(Player* player, Vertex& vertex) {
	graph[vertex].player = player;
}

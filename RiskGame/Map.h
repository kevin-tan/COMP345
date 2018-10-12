#pragma once

#include "PlayerAbstract.h"
#include <vector>
#include <sstream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/named_function_params.hpp>

// Defining properties for Graph provided by Boost
struct VertexProperty {
	// Vertex info
	std::string continent;
	std::string country;

	// Player info
	PlayerAbstract* player;
	int army_size;
};

// Define the type of Graph and its properties we want
typedef boost::adjacency_list<boost::vecS, boost::vecS,
	boost::directedS,
	VertexProperty,
	boost::no_property> Graph;
// Type aliasing with Vertex for vertex_descriptor
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
// Type aliasing for the Vertex IndexMap
typedef boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;
typedef boost::graph_traits<Graph>::adjacency_iterator AdjacencyIterator;

class Map
{
	const char DELIM = ',';
	const signed int NULL_VERTEX = -1;
	Graph graph;
	std::unordered_set<std::string> continents;
	// Helper method to find the node

public:
	Map() = default;
	Graph get_graph();

	// Return the list of continents for this map
	std::unordered_set<std::string> get_continents() const;
	// Print all the connected nodes with edges in given continent
	void print_subgraph_continent(const Graph& graph, std::string continent) const;
	// Print all edges in the graph
	void print_all_edges(const Graph& graph) const;
	// Print all the node in the graph
	void print_all_vertices(const Graph& graph) const;

	// Add territory node
	Vertex add_territory(const std::string territory);
	// Add continent to the territory node
	void add_continent_to_territory(Vertex& territory, const std::string continent);
	// Add adjency territory node to the territory node
	void add_adjacency(Vertex& territory, const std::string adj_territory);
	// Add continent to the set of continents for this map
	void add_continents(const std::string continent);

	// Get the node for country
	Vertex find_country_vertex(std::string country);
	// Get adjencency node for vertex
	std::vector<Vertex> get_adjacent_countries(const Vertex& vertex) const;
	void traverse_edges(const Vertex& vertex) const;
	// Set player that currently owns country
	void set_country_owner(PlayerAbstract* player, Vertex& vertex);

	// Temporary for driver
	Graph generate_map(std::vector<std::string>);
};

#pragma once

#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/named_function_params.hpp>
#include <sstream>

// Defining properties for Graph provided by Boost

struct VertexProperty
{
	// Node info
	std::string continent;
	std::string country;

	// Player info
	std::string player; //Player type should replace string
	int army_size;
};

// Define the type of Graph and its properties we want
typedef boost::adjacency_list<boost::vecS, boost::vecS,
	boost::directedS,
	VertexProperty,
	boost::no_property> Graph;
// Type aliasing with Vertex for vertex_descriptor
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;

class Map
{
	Graph graph;
	const char DELIM = ',';
	const signed int NULL_VERTEX = -1;
	Vertex find_country_vertex(std::string country);

public:
	Map();
	void printAllEdges();
	void getAllVertices();
	Graph get_generated_map() const;
	bool generate_map(std::vector<std::string>); // Temporary
	// bool generateMap(std::string fileName); // Generating map with the file
};

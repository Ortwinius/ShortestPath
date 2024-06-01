#pragma once
#include <string>
#include <vector>

// connection to station
struct Connection
{
	std::string destination;
	std::string line;
	int time;
};

// one station has n connections to other stations
struct Station
{
	std::string name;
	std::vector<Connection> connections;
};
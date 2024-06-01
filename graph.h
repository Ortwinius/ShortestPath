#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <set>
#include "structs.h"

// data structure
class Graph
{
public:
	Graph() = default;
	~Graph() = default;

	void readGraph(const std::string& filename);
	void printPath(const std::vector<std::string>& path, int totalCost) const;

	void addConnection(const std::string& from, const std::string& to, const std::string& line, int time);
	std::vector<std::string> findPath(const std::string& start, const std::string& end, int& totalCost);
private:
	std::unordered_map<std::string, Station> stations; // hash map of name-station pairs
};
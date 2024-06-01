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

// data structure
class Graph 
{
public:
	Graph() {}
	~Graph() {}

	void addConnection(const std::string& from, const std::string& to, const std::string& line, int time) {
		// if the from-station doesnt exist yet add it to map
		if (stations.find(from) == stations.end()) {
			stations[from] = { from, {} };
		}
		// if the to-station doesnt exist add it to map
		if (stations.find(to) == stations.end()) {
			stations[to] = { to, {} };
		}
		// add connection from x to y with destination, line and time ("cost")
		std::cout << "+ connection: " << from << "->" << to << std::endl;
		stations[from].connections.push_back({ to, line, time });
	}

	void readGraph(const std::string& filename) {
		std::ifstream file(filename);
		std::string line;
		// read file line by line
		while (getline(file, line)) {
			std::stringstream ss(line);
			std::string lineName, stationName;
			int time;

			getline(ss, lineName, ':'); //extract linename (before ':')

			std::string previousStation;
			// extract quoted stationName and time
			while (ss >> std::quoted(stationName) >> time) {
				// if there is a previous station add a connection to it
				if (!previousStation.empty()) {
					addConnection(previousStation, stationName, lineName, time);
				}
				previousStation = stationName;
			}
		}
	}

	// dijkstras algorithm O(n^2)
	std::vector<std::string> findPath(const std::string& start, const std::string& end, int& totalCost)
	{
		return {};
	}

	// Prints out found path -> refactor
	void printPath(const std::vector<std::string>& path, int totalCost) const {
		std::cout << "Path: ";
		std::string prevStation = "";
		std::string prevLine = "";
		for (const std::string& station : path) {
			if (!prevStation.empty()) {
				for (const Connection& conn : stations.at(prevStation).connections) {
					if (conn.destination == station) {
						if (conn.line != prevLine) {
							std::cout << " (Change to " << conn.line << ") ";
						}
						std::cout << " -> ";
						prevLine = conn.line;
						break;
					}
				}
			}
			std::cout << station;
			prevStation = station;
		}
		std::cout << "\nTotal cost: " << totalCost << std::endl;
	}
private:
	std::unordered_map<std::string, Station> stations; // hash map of name-station pairs

};

// Usage: find_path <filename> <start> <end> 
int main(int argc, char* argv[])
{
    if (argc != 4)
    {
		std::cout << "Usage: find_path <filename> <start> <end>\n";
		return 1;
	}
	std::cout << "filename: " << argv[1] << std::endl;
	std::cout << "start: " << argv[2] << std::endl;
	std::cout << "end: " << argv[3] << std::endl;

	std::string filename = argv[1];
	std::string start = argv[2];
	std::string end = argv[3];

	Graph graph;
	graph.readGraph(filename);

	int totalCost = 0;
	std::vector<std::string> path = graph.findPath(start, end, totalCost);
	graph.printPath(path, totalCost);

	return 0;
}
#include "graph.h"

void Graph::addConnection(const std::string& from, const std::string& to, const std::string& line, int time)
{
	// Add the 'from' station if it doesn't exist
	if (stations.find(from) == stations.end()) {
		stations[from] = { from, {} };
	}
	// Add the 'to' station if it doesn't exist
	if (stations.find(to) == stations.end()) {
		stations[to] = { to, {} };
	}
	// Add the connections undirected (from->to and to->from)
	// std::cout << "+ connection: " << from << "->" << to << std::endl;
	stations[from].connections.push_back({ to, line, time });
	stations[to].connections.push_back({ from, line, time });
}

// dijkstras algorithm O(n^2)
std::vector<std::string> Graph::findPath(const std::string& start, const std::string& end, int& totalCost)
{
	std::unordered_map<std::string, int> timeDistances;
	std::unordered_map<std::string, std::string> previousStations;
	// priority queue sorting after smallest timeDistance 
	std::priority_queue <std::pair<int, std::string>,
		std::vector<std::pair<int, std::string>>,
			std::greater<std::pair<int, std::string>>> pq;

	// check if stations is uninitialized?
	if (stations.empty()) return {};

	// set distance to every station to "infinity" to mark it as "not visited yet"
	for (const auto& pair : stations)
	{
		timeDistances[pair.first] = std::numeric_limits<int>::max();
	}

	// set distance of start node to 0 and add it to pq
	timeDistances[start] = 0;
	pq.push({ 0, start });

	// set of visited stations
	std::set<std::string> visited;
	
	while (!pq.empty())
	{
		//destructure currCost and currName from top element
		auto [currCost, currName] = pq.top();
		pq.pop();

		//if current station is the end station break
		if (currName == end) break;
		// if currName in visited skip
		else if (visited.contains(currName)) continue;

		// station hasn't been visited yet -> add it to visited set
		visited.insert(currName);

		// for every connection of the current station -> update distances
		for (const auto& conn : stations.at(currName).connections)
		{
			int newDist = timeDistances[currName] + conn.time;

			if (newDist < timeDistances[conn.destination])
			{
				timeDistances[conn.destination] = newDist; // update dist of neighbour station
				previousStations[conn.destination] = currName; // update previous station
				pq.push({ newDist, conn.destination }); // add updated dist to pq
			}
		}
	}

	std::vector<std::string> path;

	for (std::string at = end; !at.empty(); at = previousStations[at]) {
		path.push_back(at);
	}
	reverse(path.begin(), path.end());
	totalCost = timeDistances[end];
	return path;
}

void Graph::readGraph(const std::string& filename)
{
	std::ifstream file(filename);
	std::string line;

	if (!file.is_open())
	{
		std::cerr << "Error: Unable to open file " << filename << std::endl;
		return;
	}
	// read file line by line
	while (getline(file, line)) {
		std::istringstream ss(line);

		std::string line, stationTo;
		int time;

		getline(ss, line, ':'); //extract linename (before ':')

		std::string stationFrom;

		ss >> std::ws; // for skipping whitespaces

		if (!(ss >> std::quoted(stationFrom)))
		{
			std::cout << "Found no starting station";
			return;
		}
		
		while (ss >> time >> std::quoted(stationTo))
		{
			addConnection(stationFrom, stationTo, line, time);
			stationFrom = stationTo;
		}
	}
}

void Graph::printPath(const std::vector<std::string>& path, int totalCost) const
{
	std::cout << "Path: ";
	std::string prevStation = "";
	std::string prevLine = "";
	// for all stations in the path print them and 
	// check if another line has to be switched to
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
	std::cout << std::endl << "Total time (cost): " << totalCost << std::endl;
}

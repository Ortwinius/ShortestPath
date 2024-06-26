#include <iostream>
#include <vector>
#include "graph.h"

// Usage: find_path <filename> <start> <end> 
int main(int argc, const char* argv[])
{
	if (argc != 4)
	    {
		std::cout << "Usage: find_path <filename> <start> <end>\n";
		return 1;
	}

	std::string filename = argv[1];
	std::string start = argv[2];
	std::string end = argv[3];

	std::cout << "From: " << start << std::endl;
	std::cout << "To: " << end << std::endl;

	Graph graph;
	graph.readGraph(filename);

	int totalCost = 0;
	std::vector<std::string> path = graph.findPath(start, end, totalCost);

	// print path if it has been found
	if (path.size() == 1 && start != end)
	{
		std::cout << "Couldn't find a path from " << start << " to " << end << "." << std::endl;
	}
	else
	{
		graph.printPath(path, totalCost);
	}

	return 0;
}
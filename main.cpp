#include <iostream>
#include <vector>
#include "graph.h"

// Usage: find_path <filename> <start> <end> 
int main(int argc, char* argv[])
{
    if (argc != 4)
    {
		std::cout << "Usage: find_path <filename> <start> <end>\n";
		return 1;
	}

	//std::cout << "filename: " << argv[1] << std::endl;
	std::cout << "start: " << argv[2] << std::endl;
	std::cout << "end: " << argv[3] << std::endl;

	std::string filename = argv[1]; 
	std::string start = "Altes Landgut";
	std::string end = "Gersthof";

	Graph graph;
	graph.readGraph(filename);

	int totalCost = 0;
	std::vector<std::string> path = graph.findPath(start, end, totalCost);

	// print path if it has been found
	if (path.size() == 1 && start != end && path[0] == end)
	{
		std::cout << "Couldn't find a path from " << start << " to " << end << "." << std::endl;
	}
	else
	{
		graph.printPath(path, totalCost);
	}

	return 0;
}
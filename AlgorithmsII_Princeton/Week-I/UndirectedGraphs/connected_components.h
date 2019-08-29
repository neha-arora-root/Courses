#ifndef CONNECTED_COMPONENTS_H
#define CONNECTED_COMPONENTS_H

#include "graph.h"

namespace graph {

class ConnectedComponents : public Graph {

public:
	// Creates empty graph.
	ConnectedComponents() : Graph() {}

	// Creates graph with input vertices and no edges.
	ConnectedComponents(const std::vector<Node>& vertices) : Graph(vertices) {}

	// Creates graph with vertices and edges corresponding to input edges.
	ConnectedComponents(const std::vector<Edge>& edges) : Graph(edges) {}

	// Finds connected components in graph by assigning the same marker_id to elements of same component and returns the id->marker map.
	std::unordered_map<std::string, int> GetConnectedComponents();

	// Prints connected components by assigning each vertex their respective component.
	void PrintConnectedComponents(const std::unordered_map<std::string, int>& marker) const;

private:
	// Utility method for assigning marker id to each node in the graph.
	void DFSForConnectedComponents(const std::string& node_id, int marker_id, std::unordered_map<std::string, int> *marker);

};

}  // namespace graph

#endif /* CONNECTED_COMPONENTS_H */
#ifndef TOPOLOGICAL_SORT_H_
#define TOPOLOGICAL_SORT_H_

#include "directed_graph.h"

namespace directed_graph{
	class TopologicalSort : public DirectedGraph {
	private:
		std::unordered_set<std::string> processing_nodes_;
		std::unordered_map<std::string, std::vector<std::string>> reverse_adjacency_map_;

		// Util method for checking if a cycle exists in the graph.
		bool IsCyclic(const std::string& node_id);

		// Revert all the edges in the graph.
		void CreateReverseAdjacencyMap();

		// Util method for obtaining topologically sorted list of dependencies.
		bool TopologicallySorted(const std::string& node_id, std::vector<std::string>* order);

	public:
		TopologicalSort() : DirectedGraph() {}

		TopologicalSort(const std::vector<Node> vertices) : DirectedGraph(vertices) {}

		TopologicalSort(const std::vector<Edge> edges) : DirectedGraph(edges) {}

		// Check if a cycle exists in the graph.
		bool IsCyclic();

		// Give topologically sorted list of dependencies.
		std::vector<std::string> TopologicallySorted();

		// Print the order obtained in input of path of nodes.
		void PrintOrder(const std::vector<std::string>& path_nodes) const;
	};

}  // namespace directed_graph

#endif /* TOPOLOGICAL_SORT_H_ */
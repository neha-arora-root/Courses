#include "connected_components.h"

namespace graph {

void ConnectedComponents::DFSForConnectedComponents(const std::string& node_id, int marker_id, std::unordered_map<std::string, int> *marker) {
	visited_.insert(node_id);
	marker->insert({node_id, marker_id});
	for (const auto& neighbor_id : adjacency_map_[node_id]) {
		if (!visited(neighbor_id)) {
			DFSForConnectedComponents(neighbor_id, marker_id, marker);
		}
	}
}

std::unordered_map<std::string, int> ConnectedComponents::GetConnectedComponents() {
	visited_.clear();
	std::unordered_map<std::string, int> marker;
	int marker_id = 0;
	for (const auto& vertex : vertices_) {
		const auto& node_id = vertex.first;
		if (!visited(node_id)) {
			DFSForConnectedComponents(node_id, marker_id, &marker);
			marker_id++;
		}
	}
	return marker;
}

void ConnectedComponents::PrintConnectedComponents(const std::unordered_map<std::string, int>& marker) const {
	for (const auto& node : marker) {
		std::cout << node.first << ": " << node.second << std::endl;
	}
}

}  // namespace graph
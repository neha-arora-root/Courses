#include "topological_sort.h"

namespace directed_graph {

	bool TopologicalSort::IsCyclic(const std::string& node_id) {
		visited_.insert(node_id);
		processing_nodes_.insert(node_id);
		for (const auto& neighbor_id : adjacency_map_[node_id]) {
			if (processing_nodes_.find(neighbor_id) != processing_nodes_.end()) {
				return true;
			}
			if (visited_.find(neighbor_id) != visited_.end()) {
				continue;
			}
			if (IsCyclic(neighbor_id)) {
				return true;
			}
		}
		processing_nodes_.erase(node_id);
		return false;
	}

	bool TopologicalSort::IsCyclic() {
		visited_.clear();
		processing_nodes_.clear();
		for (const auto& node : vertices_) {
			const std::string& node_id = node.first;
			if (visited_.find(node_id) != visited_.end()) {
				continue;
			}
			if (IsCyclic(node_id)) {
				return true;
			}
		}
		return false;
	}

	void TopologicalSort::CreateReverseAdjacencyMap() {
		reverse_adjacency_map_.clear();
		for (const auto& vertex_edges : adjacency_map_) {
			const auto& node_id = vertex_edges.first;
			for (const auto& neighbor_id : vertex_edges.second) {
				reverse_adjacency_map_[neighbor_id].push_back(node_id);
			}
		}
	}

	bool TopologicalSort::TopologicallySorted(const std::string& node_id, std::vector<std::string>* order) {
		visited_.insert(node_id);
		processing_nodes_.insert(node_id);
		for (const auto& neighbor_id : reverse_adjacency_map_[node_id]) {
			if (processing_nodes_.find(neighbor_id) != processing_nodes_.end()) {
				return false;
			}
			if (visited_.find(neighbor_id) != visited_.end()) {
				continue;
			}
			if (!TopologicallySorted(neighbor_id, order)) {
				return false;
			}
		}
		processing_nodes_.erase(node_id);
		order->push_back(node_id);
		return true;
	}

	std::vector<std::string> TopologicalSort::TopologicallySorted() {
		visited_.clear();
		processing_nodes_.clear();
		std::vector<std::string> order;
		CreateReverseAdjacencyMap();
		for (const auto& vertex : vertices_) {
			const auto& node_id = vertex.first;
			if (visited_.find(node_id) != visited_.end()) {
				continue;
			}
			if (!TopologicallySorted(node_id, &order)) {
				return {};
			}
		}
		return order;
	}

	void TopologicalSort::PrintOrder(const std::vector<std::string>& path_nodes) const {
		std::string path = "";
		if (path_nodes.size() == 0) {
			std::cout << "No nodes in the path." << std::endl;
			return;
		}

		path = path_nodes[0];

		for (int i = 1; i < path_nodes.size(); i++) {
			const std::string& node = path_nodes[i];
			path += ", " + node;
		}
		std::cout << path << std::endl;
	}
	
}  // namespace directed_graph
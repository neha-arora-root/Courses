#include "../node.h"
#include "../edge.h"
#include "graph.h"

#include <stack>
#include <queue>

namespace graph {

Graph::Graph(const std::vector<Node>& vertices) {
	V_ = E_ = 0;
	for (const auto& vertex : vertices) {
		AddVertex(vertex);
	}
}

Graph::Graph(const std::vector<Edge>& edges) {
	V_ = E_ = 0;
	for (const auto& edge : edges) {
		AddEdge(edge);
	}
}

bool Graph::AddVertex(const Node& node) {
    if (!vertices_.insert({node.Id(), node}).second) {
        std::cout << "Node with id " << node.Id() << " already exists" << std::endl;
        return false;
    }
    V_++;
    return true;
}

void Graph::AddEdge(const Edge& edge) {
    if (vertices_.find(edge.from()) == vertices_.end()) {
        vertices_[edge.from()] = Node(edge.from());
        V_++;
    }
    if (vertices_.find(edge.to()) == vertices_.end()) {
        vertices_[edge.to()] = Node(edge.to());
        V_++;
    }
    adjacency_map_[edge.from()].push_back(edge.to());
    adjacency_map_[edge.to()].push_back(edge.from());
    edges_[edge.from()].insert({edge.to(), edge});
    edges_[edge.to()].insert({edge.from(), edge});
    E_++;
}

bool Graph::visited(const std::string& node_id) {
	return visited_.find(node_id) != visited_.end();
}

void Graph::DFSUtil(const std::string& node_id) {
	visited_.insert(node_id);
	for (const auto& neighbor_id : adjacency_map_[node_id]) {
		if (!visited(neighbor_id)) {
			path_to_[neighbor_id] = node_id;
			DFSUtil(neighbor_id);
		}
	}
}

void Graph::DFS(const std::string& node_id) {
	visited_.clear();
	path_to_.clear();
	path_to_[node_id] = node_id;
	DFSUtil(node_id);
}

void Graph::DFSIterative(const std::string& node_id) {
	visited_.clear();
	path_to_.clear();
	std::stack<std::string> nodes_stack;
	nodes_stack.push(node_id);
	std::string prev = node_id;
	while (!nodes_stack.empty()) {
		const auto& curr_node_id = nodes_stack.top();
		nodes_stack.pop();
		if (visited(curr_node_id)) {
			continue;
		}
		path_to_[curr_node_id] = prev;;
		visited_.insert(curr_node_id);
		int remaining_neighbors = 0;
		for (int i = adjacency_map_[curr_node_id].size() - 1; i >= 0; i--) {
			const std::string& neighbor_id = adjacency_map_[curr_node_id][i];
			if (!visited(neighbor_id)) {
				nodes_stack.push(neighbor_id);
				remaining_neighbors++;
			}
		}
		if (remaining_neighbors > 0) {
			prev = curr_node_id;
		}
	}
}

void Graph::BFS(const std::string& node_id) {
	path_to_.clear();
	std::queue<std::string> nodes_queue;
	path_to_[node_id] = node_id;
	nodes_queue.push(node_id);
	while (!nodes_queue.empty()) {
		const auto& curr_node_id = nodes_queue.front();
		nodes_queue.pop();
		visited_.insert(curr_node_id);
		for (const auto& neighbor_id : adjacency_map_[curr_node_id]) {
			if (visited(neighbor_id)) {
				continue;
			}
			path_to_[neighbor_id] = curr_node_id;
			nodes_queue.push(neighbor_id);
		}
	}
}

bool Graph::DoesPathExist(const std::string& node_to) {
	return visited(node_to);
}

bool Graph::DoesPathExist(const std::string& node_from, const std::string& node_to) {
	DFS(node_to);
    return DoesPathExist(node_from);
}

std::vector<std::string> Graph::GetPath(const std::string& node_to) {
    std::vector<std::string> path;
    if (!DoesPathExist(node_to)) {
    	return path;
    }
    std::string iter_node = node_to;
    while (iter_node != path_to_[iter_node]) {
        path.insert(path.begin(), iter_node);
        iter_node = path_to_[iter_node];
    }
    path.insert(path.begin(), iter_node);
    return path;
}

std::vector<std::string> Graph::GetPath(const std::string& node_from, const std::string& node_to) {
    DFS(node_from);
    return GetPath(node_to);
}

void Graph::PrintPath(const std::vector<std::string>& path_nodes) const {
    std::string path = "";
    if (path_nodes.size() == 0) {
      std::cout << "No nodes in the path." << std::endl;
      return;
    }

    path = path_nodes[0];

    for (int i = 1; i < path_nodes.size(); i++) {
      const std::string& node = path_nodes[i];
      path += " -> " + node;
    }
    std::cout << path << std::endl;
}

}  // namespace graph
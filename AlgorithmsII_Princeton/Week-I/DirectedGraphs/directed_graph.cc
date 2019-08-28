#include "directed_graph.h"
#include <queue>

namespace directed_graph {

DirectedGraph::DirectedGraph(const std::vector<Node> vertices) {
  V_ = E_ = 0;
  for (const Node& vertex : vertices) {
    AddVertex(vertex);
  }
}

DirectedGraph::DirectedGraph(const std::vector<Edge> edges) {
  V_ = E_ = 0;
  for (const auto& edge : edges) {
    AddEdge(edge);
  }
}

bool DirectedGraph::AddVertex(const Node& node) {
  if (!vertices_.insert({node.Id(), node}).second) {
    std::cout << "Node with id " << node.Id() << " already exists" << std::endl;
    return false;
  }
  V_++;
  return true;
}

void DirectedGraph::AddEdge(const Edge& edge) {
  if (vertices_.find(edge.from()) == vertices_.end()) {
    vertices_[edge.from()] = Node(edge.from());
    V_++;
  }
  if (vertices_.find(edge.to()) == vertices_.end()) {
    vertices_[edge.to()] = Node(edge.to());
    V_++;
  }
  adjacency_map_[edge.from()].push_back(edge.to());
  edges_[edge.from()].insert({edge.to(), edge});
  E_++;
}

void DirectedGraph::DFSUtil(const std::string& node_id) {
  if (visited_.find(node_id) != visited_.end()) return;
  visited_.insert(node_id);
  for (const auto& neighbor_id : adjacency_map_[node_id]) {
    if (visited_.find(neighbor_id) != visited_.end()) continue;
    path_to_[neighbor_id] = node_id;
    DFSUtil(neighbor_id);
  }
}

void DirectedGraph::DFS(const std::string& node_id) {
  visited_.clear();
  path_to_.clear();
  path_to_[node_id] = node_id;
  DFSUtil(node_id);
}

void DirectedGraph::BFS(const std::string& node_id) {
  visited_.clear();
  path_to_.clear();
  
  std::queue<std::string> nodes_queue;
  nodes_queue.push(node_id);
  visited_.insert(node_id);
  path_to_[node_id] = node_id;

  while (!nodes_queue.empty()) {
    const std::string curr_node_id = nodes_queue.front();
    nodes_queue.pop();
    for (const std::string& neighbor_id : adjacency_map_[curr_node_id]) {
      if (visited_.find(neighbor_id) != visited_.end()) continue;
      visited_.insert(neighbor_id);
      path_to_[neighbor_id] = curr_node_id;
      nodes_queue.push(neighbor_id);
    }
  }
}

bool DirectedGraph::DoesPathExist(const std::string& node_to) {
  return visited_.find(node_to) != visited_.end();
}

bool DirectedGraph::DoesPathExist(const std::string& node_from, const std::string& node_to) {
  DFS(node_to);
  return DoesPathExist(node_from);
}

std::vector<std::string> DirectedGraph::GetPath(const std::string& node_to) {
  std::vector<std::string> path;
  if (!DoesPathExist(node_to)) return path;
  std::string iter_node = node_to;
  while (iter_node != path_to_[iter_node]) {
    path.insert(path.begin(), iter_node);
    iter_node = path_to_[iter_node];
  }
  path.insert(path.begin(), iter_node);
  return path;
}

std::vector<std::string> DirectedGraph::GetPath(const std::string& node_from, const std::string& node_to) {
  DFS(node_from);
  return GetPath(node_to);
}

void DirectedGraph::PrintPath(const std::vector<std::string>& path_nodes) const {
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

void DirectedGraph::PrintAllEdges() const {
  for (const auto& vertex : edges_) {
    const std::unordered_map<std::string, Edge>& adjoining_nodes_map = vertex.second;
    for (const auto& node_edge_map : adjoining_nodes_map) {
      const Edge& edge = node_edge_map.second;
      edge.PrintEdge();
    }
  }
}

}  // namespace directed_graph
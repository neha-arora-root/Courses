#include "directed_graph.h"

DirectedGraph::DirectedGraph(const std::vector<Node>& vertices) {
  V_ = E_ = 0;
  for (const Node& vertex : vertices) {
    if (vertices_.find(vertex.Id()) != vertices_.end()) {
      continue;
    }
    vertices_[vertex.Id()] = Node(vertex.Id());
    V_++;
  }
}

DirectedGraph::DirectedGraph(const std::vector<Edge>& edges) {
  V_ = E_ = 0;
  for (const auto& edge : edges) {
    AddEdge(edge);
  }
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
  E_++;
}

void DirectedGraph::DFSUtil(const std::string& node_id) {
  if (visited_[node_id]) return;
  visited_[node_id] = true;
  for (const auto& neighbor_id : adjacency_map_[node_id]) {
    path_to_[neighbor_id] = node_id;
    DFSUtil(neighbor_id);
  }
}

void DirectedGraph::DFS(const std::string& node_id) {
  for (const auto& entry : vertices_) {
    visited_[entry.first] = false;
    path_to_[entry.first] = "";
  }
  path_to_[node_id] = node_id;
  DFSUtil(node_id);
}

bool DirectedGraph::DoesPathExist(const std::string& node_id) {
  return path_to_[node_id] != "";
}

void DirectedGraph::PrintPath(const std::string& node_id) {
  if (!DoesPathExist(node_id)) {
    std::cout << "Path does not exist" << std::endl;
    return;
  }
  std::string path = node_id;
  std::string curr_node_id = node_id;
  while (path_to_[curr_node_id] != curr_node_id) {
    curr_node_id = path_to_[curr_node_id];
    path = curr_node_id + " -> " + path;
  }
  std::cout << path << std::endl;
}

std::unordered_map<std::string, std::vector<std::string> > DirectedGraph::GetReverseAdjacencyMap() {
  std::unordered_map<std::string, std::vector<std::string> > reverse_adjacency_map;
  for (const auto& entry : vertices_) {
    const std::string& from = entry.first;
    for (const auto& to : adjacency_map_[from]) {
      reverse_adjacency_map[to].push_back(from);
    }
  }
  return reverse_adjacency_map;
}

std::stack<std::string> DirectedGraph::PostOrderFromDFS() {
  std::stack<std::string> to_process;
  std::stack<std::string> post_order_dfs;
  auto reverse_adjacency_map = GetReverseAdjacencyMap();

  for (const auto& entry : vertices_) {
    visited_[entry.first] = false;
  }
  for (const auto& entry : vertices_) {
    if (visited_[entry.first]) {
      continue;
    }
    to_process.push(entry.first);
    visited_[entry.first] = true;
    while (!to_process.empty()) {
      const std::string& node_id = to_process.top();
      post_order_dfs.push(node_id);
      to_process.pop();
      for (int i = reverse_adjacency_map[node_id].size() - 1; i >= 0; i--) {
        const std::string& neighbor_id = reverse_adjacency_map[node_id][i];
        if (!visited_[neighbor_id]) {
          to_process.push(neighbor_id);
          visited_[neighbor_id] = true;
        }
      }
    }
  }
  std::stack<std::string> reverse_order;
  while (!post_order_dfs.empty()) {
    reverse_order.push(post_order_dfs.top());
    post_order_dfs.pop();
  }
  return reverse_order;
}

const bool DirectedGraph::IsCyclic() {
  std::unordered_map<std::string, bool> considering;
  for (const auto& entry : vertices_) {
    visited_[entry.first] = false;
    considering[entry.first] = false;
  }
  std::stack<std::string> to_process;

  for (const auto& entry : vertices_) {
    if (visited_[entry.first]) {
      continue;
    }
    to_process.push(entry.first);
    visited_[entry.first] = true;
    considering[entry.first] = true;
    while (!to_process.empty()) {
      const std::string& node_id = to_process.top();
      to_process.pop();
      for (int i = adjacency_map_[node_id].size() - 1; i >= 0; i--) {
        const std::string& neighbor = adjacency_map_[node_id][i];
        if (considering[neighbor]) {
          return true;
        }
        visited_[neighbor] = true;
        considering[neighbor] = true;
        to_process.push(neighbor);
      }
      considering[node_id] = false;
    }
  }
  return false;
}

const std::vector<std::string> DirectedGraph::TopologicalSort() {
  std::vector<std::string> topological_sort;
  if (IsCyclic()) {
    std::cout << "The graph has a cycle." << std::endl;
    return topological_sort;
  }
  std::stack<std::string> dfs_order = PostOrderFromDFS();
  for (const auto& entry : vertices_) {
    visited_[entry.first] = false;
  }

  std::stack<std::string> dfs_stack;
  while (!dfs_order.empty()) {
    const std::string start_node_id = dfs_order.top();
    dfs_order.pop();
    if (!visited_[start_node_id]) {
      dfs_stack.push(start_node_id);
    }
    while (!dfs_stack.empty()) {
      const std::string node_id = dfs_stack.top();
      dfs_stack.pop();
      topological_sort.push_back(node_id);
      for (int i = adjacency_map_[node_id].size() - 1; i >= 0; i--) {
        const auto& neighbor = adjacency_map_[node_id][i];
        if (!visited_[neighbor]) {
          visited_[neighbor] = true;
          dfs_stack.push(neighbor);
        }
      }
    }
  } 
  return topological_sort;
}

void DirectedGraph::PrintPath(const std::vector<std::string>& path_nodes) const {
  std::string path = "";
  if (path_nodes.size() == 0) {
    std::cout << "No nodes in the path." << std::endl;
    return;
  }

  path = path_nodes[path_nodes.size()-1];

  for (int i = path_nodes.size() - 2; i >= 0; i--) {
    const std::string& node = path_nodes[i];
    path = node + " -> " + path;
  }
  std::cout << path << std::endl;
}

void DirectedGraph::PrintAllPaths(const std::vector<std::vector<std::string> >& all_paths) const {
  for (const auto& path : all_paths) {
    PrintPath(path);
  }
}

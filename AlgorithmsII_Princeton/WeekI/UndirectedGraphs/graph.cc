#include "graph.h"

#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <stack>
#include <queue>

Graph::Graph(const int V, const std::vector<std::pair<int,int> >& edges) {
  vertices_ = V;
  adjacency_list_ = std::vector<std::vector<int> >(vertices_);
  edges_ = 0;
  for (const std::pair<int,int>& edge : edges) {
    int from = edge.first, to = edge.second;
    AddEdge(from, to);
  }
  reset_();
}

void Graph::reset_() { 
  visited_ = std::vector<bool>(vertices_, false);
  connected_components_ = std::vector<int>(vertices_);
  path_to_ = std::vector<int>(vertices_, -1);
}

void Graph::AddEdge(int from, int to) {
  if (from >= vertices_ || to >= vertices_) {
    std::cout << "Invalid edge found for pair (" << from << "," << to << "), skipping this edge formation" << std::endl;
    return;
  }
  edges_++;
  adjacency_list_[from].push_back(to);
  adjacency_list_[to].push_back(from);
}

int Graph::V() { return vertices_; }

int Graph::E() { return edges_; }

void Graph::DFSUtil(const int node, const int marker) {
  if (visited_[node]) {
    return;
  }
  visited_[node] = true;
  connected_components_[node] = marker;
  for (const int neighbor : adjacency_list_[node]) {
    if (!visited_[neighbor]) {
      path_to_[neighbor] = node;
      DFSUtil(neighbor, marker);
    }
  }
}

void Graph::DFS(const int node) {
  dfs_traversal_from_ = node;
  reset_();
  path_to_[node] = node; 
  DFSUtil(dfs_traversal_from_, node);
}

void Graph::DFSIterative(const int node) {
  reset_();
  std::stack<int> s;
  s.push(node);
  int prev_node = node;
  while (!s.empty()) {
    int curr_node = s.top();
    if (!visited_[curr_node]) {
      path_to_[curr_node] = prev_node;
    }
    prev_node = curr_node;
    s.pop();
    visited_[curr_node] = true;
    for (const int neighbor : adjacency_list_[curr_node]) {
      if (!visited_[neighbor]) {
        s.push(neighbor);
      }
    }
  }
}

void Graph::ConnectedComponents() {
  reset_();
  int marker = 0;
  for (int i = 0; i < vertices_; i++) {
    if (!visited_[i]) {
      DFSUtil(i, marker++);
    } 
  }
}

void Graph::PrintGraph() {
  std::cout << "The graph has " << std::to_string(vertices_) << " vertices and " << std::to_string(edges_) << " edges.";
  if (vertices_ ==  0 && edges_ == 0) {
    std::cout << std::endl;
    return;
  }
  std::cout << " They are connected as follows: " << std::endl;
  for (int from = 0; from < adjacency_list_.size(); from++) {
    for (int j = 0; j < adjacency_list_[from].size(); j++) {
      int to = adjacency_list_[from][j];
      if (from < to) {
        std::cout << from << " -> " << to << std::endl; 
      }
    }
  }
}

bool Graph::DoesPathExist(int to) {
  if (to >= path_to_.size()) {
    return false;
  }
  return visited_[to];
}

std::vector<int> Graph::Path(int to) {
  std::vector<int> path;
  if (!DoesPathExist(to) || to >= path_to_.size()) {
    return path;
  }
  while (path_to_[to] != to) {
    path.insert(path.begin(), to);
    to = path_to_[to];
  } 
  path.insert(path.begin(), to);
  return path;
}

void Graph::PrintPath(const std::vector<int>& path) {
  if (path.size() == 0) {
    std::cout << "No path found." << std::endl;
    return;
  }
  for (int i = 0; i < path.size() - 1; i++) {
    std::cout << path[i] << " -> ";
  }
  std::cout << path[path.size()-1] << std::endl;
}

std::vector<int> Graph::GetConnectedComponents() { return connected_components_; }

void Graph::PrintConnectedComponents() {
  for (int i = 0; i < vertices_; i++) {
    std::cout << "   " << i << " : " << connected_components_[i] << std::endl;
  }
}

void Graph::BFS(const int node) {
  bfs_traversal_from_ = node;
  reset_();
  std::queue<int> bfs_queue;
  path_to_[node] = node;
  bfs_queue.push(node);
  visited_[node] = true;
  while (!bfs_queue.empty()) {
    int curr_node = bfs_queue.front();
    bfs_queue.pop();
    for (int neighbor : adjacency_list_[curr_node]) {
      if (!visited_[neighbor]) {
        visited_[neighbor] = true;
        bfs_queue.push(neighbor);
        path_to_[neighbor] = curr_node;
      }
    }
  }
}

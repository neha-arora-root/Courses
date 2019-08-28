#ifndef DIRECTED_GRAPH_H_
#define DIRECTED_GRAPH_H_

#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>
#include <unordered_map>

namespace directed_graph {

class Node {
  private:
    std::string id_;
  public:
    Node(const std::string id=""): id_(id) {}
    const std::string& Id() const { return id_; }
};

class Edge {
  private:
    const std::string from_;
    const std::string to_;
    const int weight_;
  public:
    Edge(const std::string from, const std::string to, const int weight): from_(from), to_(to), weight_(weight) {}
    const std::string from() const { return from_; }
    const std::string to() const { return to_; }
    const int weight() const { return weight_; }
    void PrintEdge() const { std::cout << from_ << " -> " << to_ << " : (" << weight_ << ")" << std::endl; }
};

class DirectedGraph {
  private:
    std::unordered_map<std::string, std::string> path_to_;

    // Utility method for implementation of DFS.
    void DFSUtil(const std::string& node_id);

    // Utility method for implementation of BFS.
    void BFSUtil(const std::string& node_id);

  protected:
    int V_, E_;
    std::unordered_map<std::string, Node> vertices_;
    std::unordered_map<std::string, std::vector<std::string>> adjacency_map_;
    std::unordered_map<std::string, std::unordered_map<std::string, Edge>> edges_;
    std::unordered_set<std::string> visited_;

  public:
    // Create an empty graph.
    DirectedGraph() { V_ = E_ = 0; }

    // Create an empty graph with the given set of vertices.
    DirectedGraph(const std::vector<Node> vertices);

    // Create a graph with the given set of edges.
    DirectedGraph(const std::vector<Edge> edges);

    // Add vertex to graph.
    bool AddVertex(const Node& n);

    // Add edge to graph.
    void AddEdge(const Edge& edge);

    // Get count of vertices.
    int V() { return V_; }

    // Get count of edges.
    int E() { return E_; }

    // DFS implementaion.
    void DFS(const std::string& node_id);

    // BFS implementation.
    void BFS(const std::string& node_id);

    // If DFS or BFS is run already for a node, then the result for whether or not a path exists to the input node is returned.
    bool DoesPathExist(const std::string& node_to);

    // The result for whether or not a path exists from node_from to node_to is returned.
    bool DoesPathExist(const std::string& node_from, const std::string& node_to);

    // If DFS or BFS is run already for a node, then the path from input node is returned. A message for non-existent path is returned in case there is no path.
    std::vector<std::string> GetPath(const std::string& node_to);

    // The path from node_from to node_to is returned. A message for non-existent path is returned in case there is no path.
    std::vector<std::string> GetPath(const std::string& node_from, const std::string& node_to);

    // Print the input path.
    void PrintPath(const std::vector<std::string>& path_nodes) const;

    // Print all the edges in the graph.
    void PrintAllEdges() const;
};

}  // namespace directed_graph

#endif /* DIRECTED_GRAPH_H_ */
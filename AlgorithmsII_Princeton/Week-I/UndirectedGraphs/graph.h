#ifndef GRAPH_H_
#define GRAPH_H_

#include "../node.h"
#include "../edge.h"

#include <vector>
#include <utility>
#include <unordered_set>
#include <unordered_map>

namespace graph {

class Graph {

  private:
    std::unordered_map<std::string, std::string> path_to_;

    // Utility method for implementation of DFS.
    void DFSUtil(const std::string& node_id);

    // Utility method for implementation of BFS.
    void BFSUtil(const std::string& node_id);

  protected:
    // Count of vertices in graph.
    int V_;

    // Count of edges in graph.
    int E_;

    std::unordered_map<std::string, Node> vertices_;
    std::unordered_map<std::string, std::vector<std::string>> adjacency_map_;
    std::unordered_map<std::string, std::unordered_map<std::string, Edge>> edges_;
    std::unordered_set<std::string> visited_;

  public:
  	// Create an empty graph.
    Graph() { V_ = E_ = 0; }

    // Create an empty graph with the given set of vertices.
    Graph(const std::vector<Node>& vertices);

    // Create a graph with the given set of edges.
    Graph(const std::vector<Edge>& edges);

    // Add vertex to graph.
    bool AddVertex(const Node& n);

    // Add edge to graph.
    void AddEdge(const Edge& edge);

    // Get count of vertices in graph.
    int V() { return V_; }

    // Get count of edges in graph.
    int E() { return E_; }

    // Return whether the input node is visited or not.
    bool visited(const std::string& node_id);

    // DFS implementaion.
    void DFS(const std::string& node_id);

    // DFS iterative implementaion.
    void DFSIterative(const std::string& node_id);

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

};

}  //  namespace graph

#endif /* GRAPH_H_ */

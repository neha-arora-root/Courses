#ifndef DIRECTED_GRAPH_H_
#define DIRECTED_GRAPH_H_

#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>
#include <unordered_map>

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
};

class DirectedGraph {
  private:
    int V_, E_;
    std::unordered_map<std::string, Node> vertices_;
    std::unordered_map<std::string, std::vector<std::string>> adjacency_map_;
    std::unordered_map<std::string, bool> visited_;
    std::unordered_map<std::string, std::string> path_to_;

    // Utility function for DFS.
    void DFSUtil(const std::string& node_id);

    // Find post order traversal from DFS.
    std::stack<std::string> PostOrderFromDFS();

    // Get reverse adjacency map.
    std::unordered_map<std::string, std::vector<std::string> > GetReverseAdjacencyMap();

  public:
    // Create an empty graph.
    DirectedGraph() { V_ = E_ = 0; }

    // Create an empty graph with the given set of vertices.
    DirectedGraph(const std::vector<Node>& vertices);

    // Create a graph with the given set of edges.
    DirectedGraph(const std::vector<Edge>& edges);

    // Add edge to graph.
    void AddEdge(const Edge& edge);

    // Get count of vertices.
    int V() { return V_; }

    // Get count of edges.
    int E() { return E_; }

    // Depth first search traversal.
    void DFS(const std::string& node_id);

    // Get Path.
    //std::vector<std::string> Path() { return path_to_; }

    // Does path exist to node j?
    bool DoesPathExist(const std::string& node_id);

    // Print path to node j.
    void PrintPath(const std::string& node_id);

    // Print path when a vector of nodes is input.
    void PrintPath(const std::vector<std::string>& path_nodes) const;

    // Print all paths.
    void PrintAllPaths(const std::vector<std::vector<std::string> >& all_paths) const;

    // Check cyclicity.
    const bool IsCyclic();

    // Topological sorting.
    const std::vector<std::string > TopologicalSort();
};



#endif /* GRAPH_H */

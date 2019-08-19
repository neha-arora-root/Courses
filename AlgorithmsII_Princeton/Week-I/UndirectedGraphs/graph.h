#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <utility>

class Graph {
  private:
    int vertices_, edges_;
    int dfs_traversal_from_;
    int bfs_traversal_from_;
    std::vector<std::vector<int> > adjacency_list_;
    std::vector<bool> visited_;
    std::vector<int> path_to_;
    std::vector<int> connected_components_;

    void reset_();

  public:
    // Creates graph with number of vertices and edges.
    Graph(const int V, const std::vector<std::pair<int, int> >& edges);

    // Returns the number of vertices in the graph.
    int V();

    // Returns the number of edges in the graph.
    int E();

    // Adds an edge in the graph between nodes to and from.
    void AddEdge(int from, int to);

    // Prints the number of vertices and edges in the graph and information for each edge.
    void PrintGraph();

    // Utility method for implementing depth first search traversal and related routines such as finding path from a given node to other connected nodes and finding the connected components in a graph. 
    void DFSUtil(const int node, const int marker);

    // Records paths to other nodes in the graph from a given node via depth first search traversal.
    void DFS(const int node);

    // Iterative implementation of depth first search traversal.
    void DFSIterative(const int node);

    // Does path exist from the dfs_traversal_from_ node to the required node.
    bool DoesPathExist(int to);

    // Finds path from dfs_traversal_from_ node to the required node, returns empty path if no path is found.
    std::vector<int> Path(int to);

    // Prints the path found in the above case.
    void PrintPath(const std::vector<int>& path);

    // Finds connected components in graph.
    void ConnectedComponents();

    // Prints connected components by assigning each vertex their respective component.
    void PrintConnectedComponents();

    // Returns connected_components list.
    std::vector<int> GetConnectedComponents();

    // Records paths to other nodes in the graph from a given node via breadth first search traversal.
    void BFS(const int node);

};
#endif /* GRAPH_H_ */

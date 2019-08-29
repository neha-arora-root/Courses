This repository covers
================================================================================================================

1)  This includes basic graph implementation with constructors for:  
*  Empty graph (no vertices, no edges)
*  Graph with vertices (Each vertex is an island)
*  Graph with edges (Graph with vertices and edges corresponding to input edges)
*  Method to add vertex to an already created graph instance
*  Method to add edge to an already created graph instance

  The base implementation also includes: 
*  DFS - both recursive and iterative
*  BFS
*  Method call to determine if path exists between two nodes

2)  Implementation for finding connected components and printing these

3)  Implementation of the following for a given graph <i>G(V, E)</i>:
*  Diameter: If <i>d<sub>(i,j)</sub></i> denotes the shortest distance between nodes <i>i</i> and <i>j</i>, then diameter of the graph is the largest distance among all shortest distances between two nodes in the graph
<p align="center"><i> diam(G) = max<sub>(u,v&isin;V)</sub>d<sub>u,v</sub></i></p>


Compile and run code
================================================================================================================

To run graph base tests:  
__Compile:__ g++ -o output_graph graph.cc graph_test.cc -std=c++11  
__Run:__ ./output_graph  

To run connected components tests:  
__Compile:__ g++ -o output_connected_components connected_components.cc connected_components_test.cc -std=c++11  
__Run:__ ./output_connected_components

#include "graph.h"
#include "../test_utils.h"

namespace graph {

/**
* Test graph creation with no vertices and edges.
*/
void TestEmptyGraphCreation(testing::Testing& test_suite) {
	test_suite.init("empty graph: no vertices, no edges");
	Graph graph;
	test_suite.test(graph.V() == 0);
	test_suite.test(graph.E() == 0);
	test_suite.TestResults();
}

/**
* Test empty graph creation with set of vertices.
*/
void TestGraphCreationWithOnlyVertices(testing::Testing& test_suite) {
    test_suite.init("empty graph creation with only vertices and no edges");
    Node a("A"), b("B"), c("C");
    Graph graph({a, b, c});
    test_suite.test(graph.V() == 3);
    test_suite.test(graph.E() == 0);
    test_suite.TestResults();
}

/**
* Test graph creation with list of edges.
*/
void TestGraphCreationWithEdges(testing::Testing& test_suite) {
    test_suite.init("graph creation with edges");
    Node a("A"), b("B"), c("C");
    Edge e1(a.Id(), b.Id(), 1), e2(a.Id(), c.Id(), 1);
    Graph graph({e1, e2});
    test_suite.test(graph.V() == 3);
    test_suite.test(graph.E() == 2);
    test_suite.TestResults();
}

/**
* Test path creation between nodes via DFS.
*/
void TestPathCreationForNodesWithDFS(testing::Testing& test_suite) {
	test_suite.init("DFS traversal to find path between nodes");
    Node a("A"), b("B"), c("C"), d("D"), e("E"), f("F");
    Edge e1(a.Id(), b.Id(), 1), e2(a.Id(), c.Id(), 1), e3(b.Id(), d.Id(), 1), e4(d.Id(), e.Id(), 1);
    Graph graph({e1, e2, e3, e4});
    graph.DFS(a.Id());
    const std::vector<std::string> expected_path = {"A", "B", "D", "E"};
    const std::vector<std::string> p1 = graph.GetPath(e.Id());
    test_suite.test(testing::ComparePaths(p1, expected_path));
    graph.PrintPath(p1);
    const std::vector<std::string> p2 = graph.GetPath(a.Id(), e.Id());
    test_suite.test(testing::ComparePaths(p2, expected_path));
    graph.PrintPath(p2);
    const std::vector<std::string> p3 = graph.GetPath(b.Id(), f.Id());
    graph.PrintPath(p3);
    test_suite.test(testing::ComparePaths(p3, {}));
    test_suite.TestResults();
}

/**
* Test iterative depth first search traversal implementation.
*/
void TestPathCreationForNodesWithDFSIterative(testing::Testing& test_suite) {
	test_suite.init("Iterative DFS traversal to find path between nodes");
	Node a("A"), b("B"), c("C"), d("D"), e("E"), f("F");
    Edge e1(a.Id(), b.Id(), 1), e2(a.Id(), c.Id(), 1), e3(b.Id(), d.Id(), 1), e4(c.Id(), d.Id(), 1), e5(d.Id(), e.Id(), 1), e6(e.Id(), f.Id(), 1), e7(a.Id(), f.Id(), 3);
    Graph graph({e1, e2, e3, e4, e5, e6, e7});
    graph.DFSIterative(a.Id());
    const std::vector<std::string> expected_path = {"A", "B", "E"};
    const std::vector<std::string> path = graph.GetPath(e.Id());
    test_suite.test(testing::ComparePaths(path, expected_path));
    graph.PrintPath(path);
    test_suite.TestResults();
}

/**
* Test path creation between nodes via BFS.
*/
void TestPathCreationForNodesWithBFS(testing::Testing& test_suite) {
    test_suite.init("BFS traversal to find path between nodes");
    Node a("A"), b("B"), c("C"), d("D"), e("E"), f("F");
    Edge e1(a.Id(), b.Id(), 1), e2(a.Id(), c.Id(), 1), e3(b.Id(), d.Id(), 1), e4(d.Id(), e.Id(), 1);
    Graph graph({e1, e2, e3, e4});
    graph.BFS(a.Id());
    const std::vector<std::string> expected_path = {"A", "B", "D", "E"};
    const std::vector<std::string> p1 = graph.GetPath(e.Id());
    test_suite.test(testing::ComparePaths(p1, expected_path));
    graph.PrintPath(p1);
    graph.BFS(b.Id());
    const std::vector<std::string> p2 = graph.GetPath(f.Id());
    graph.PrintPath(p2);
    test_suite.test(testing::ComparePaths(p2, {}));
    test_suite.TestResults();
}

}  // namespace graph

int main () {
  testing::Testing test_suite("UNDIRECTED GRAPHS");

  graph::TestEmptyGraphCreation(test_suite);
  graph::TestGraphCreationWithOnlyVertices(test_suite);
  graph::TestGraphCreationWithEdges(test_suite);
  graph::TestPathCreationForNodesWithDFS(test_suite);
  graph::TestPathCreationForNodesWithDFSIterative(test_suite);
  graph::TestPathCreationForNodesWithBFS(test_suite);

  test_suite.PrintStats();
}
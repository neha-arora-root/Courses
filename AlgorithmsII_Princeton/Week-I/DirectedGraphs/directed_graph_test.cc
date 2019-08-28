#include "directed_graph.h"
#include "../test_utils.h"

namespace directed_graph {

  /**
   * Util function to compare two paths.
   */
  bool ComparePaths(const std::vector<std::string>& path_1, const std::vector<std::string>& path_2) {
    if (path_1.size() != path_2.size()) {
      return false;
    }
    for (int i = 0; i < path_1.size(); i++) {
      if (path_1[i] != path_2[i]) {
        return false;
      }
    }
    return true;
  }

  /**
   * Test graph creation with no vertices and edges.
   */
  void TestEmptyGraphCreation(testing::Testing& test_suite) {
    test_suite.init("empty graph: no vertices, no edges");
    DirectedGraph dg;
    test_suite.test(dg.V() == 0);
    test_suite.test(dg.E() == 0);
    test_suite.TestResults();
  }

  /**
   * Test empty graph creation with set of vertices.
   */
  void TestGraphCreationWithOnlyVertices(testing::Testing& test_suite) {
    test_suite.init("empty directed graph creation with only vertices and no edges");
    Node a("A"), b("B"), c("C");
    DirectedGraph dg({a, b, c});
    test_suite.test(dg.V() == 3);
    test_suite.test(dg.E() == 0);
    test_suite.TestResults();
  }

  /**
   * Test graph creation with list of edges.
   */
  void TestGraphCreationWithEdges(testing::Testing& test_suite) {
    test_suite.init("directed graph creation with edges");
    Node a("A"), b("B"), c("C");
    Edge e1(a.Id(), b.Id(), 1), e2(a.Id(), c.Id(), 1);
    DirectedGraph dg({e1, e2});
    test_suite.test(dg.V() == 3);
    test_suite.test(dg.E() == 2);
    test_suite.TestResults();
  }

  /**
   * Test path creation between nodes via DFS.
   */
  void TestPathCreationForNodesWithDFS(testing::Testing& test_suite) {
    test_suite.init("DFS traversal to find path between nodes");
    Node a("A"), b("B"), c("C"), d("D"), e("E"), f("F");
    Edge e1(a.Id(), b.Id(), 1), e2(a.Id(), c.Id(), 1), e3(b.Id(), d.Id(), 1), e4(d.Id(), e.Id(), 1);
    DirectedGraph dg({e1, e2, e3, e4});
    dg.DFS(a.Id());
    const std::vector<std::string> expected_path = {"A", "B", "D", "E"};
    const std::vector<std::string> p1 = dg.GetPath(e.Id());
    test_suite.test(ComparePaths(p1, expected_path));
    dg.PrintPath(p1);
    const std::vector<std::string> p2 = dg.GetPath(a.Id(), e.Id());
    test_suite.test(ComparePaths(p2, expected_path));
    dg.PrintPath(p2);
    const std::vector<std::string> p3 = dg.GetPath(b.Id(), f.Id());
    dg.PrintPath(p3);
    test_suite.test(ComparePaths(p3, {}));
    test_suite.TestResults();
  }

  /**
   * Test path creation between nodes via BFS.
   */
  void TestPathCreationForNodesWithBFS(testing::Testing& test_suite) {
    test_suite.init("BFS traversal to find path between nodes");
    Node a("A"), b("B"), c("C"), d("D"), e("E"), f("F");
    Edge e1(a.Id(), b.Id(), 1), e2(a.Id(), c.Id(), 1), e3(b.Id(), d.Id(), 1), e4(d.Id(), e.Id(), 1);
    DirectedGraph dg({e1, e2, e3, e4});
    dg.BFS(a.Id());
    const std::vector<std::string> expected_path = {"A", "B", "D", "E"};
    const std::vector<std::string> p1 = dg.GetPath(e.Id());
    test_suite.test(ComparePaths(p1, expected_path));
    dg.PrintPath(p1);
    dg.BFS(b.Id());
    const std::vector<std::string> p2 = dg.GetPath(f.Id());
    dg.PrintPath(p2);
    test_suite.test(ComparePaths(p2, {}));
    test_suite.TestResults();
  }

}  // namespace directed_graph

int main () {
  testing::Testing test_suite("DIRECTED GRAPHS");

  directed_graph::TestEmptyGraphCreation(test_suite);
  directed_graph::TestGraphCreationWithOnlyVertices(test_suite);
  directed_graph::TestGraphCreationWithEdges(test_suite);
  directed_graph::TestPathCreationForNodesWithDFS(test_suite);
  directed_graph::TestPathCreationForNodesWithBFS(test_suite);

  test_suite.PrintStats();
}

#include "directed_graph.h"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

void run(std::string test_name, int& test_total) {
  std::cout << "Test for " << test_name << ": RUN" << std::endl;
  test_total++;
}

void ok(std::string test_name, int& test_pass) {
  test_pass++;
  std::cout << "Test for " << test_name << ": OK" << std::endl;
  std::cout << "----------------------------------------------------------------------------------" << std::endl;
}

void fail(std::string test_name, int& test_fail) {
  test_fail++;
  std::cout << "Test for " << test_name << ": FAIL" << std::endl;
  std::cout << "-----------------------------------------------------------------------------------" << std::endl;
}

int main () {
  std::cout << std::endl << "TEST SUITE FOR DIRECTED GRAPHS" << std::endl << std::endl;

  int test_pass = 0, test_fail = 0, test_total = 0;
  bool test_flag = true;

  Node a("A"), b("B"), c("C"), d("D"), e("E"), f("F"), g("G"), h("H"), i("I"), j("J"), k("K"), l("L");
  Edge e1(a.Id(), b.Id(), 5);
  Edge e2(a.Id(), c.Id(), 3);
  Edge e3(b.Id(), d.Id(), 2);

  Edge e4(e.Id(), f.Id(), 1);
  Edge e5(f.Id(), g.Id(), 3);
  Edge e6(e.Id(), h.Id(), 7);
  Edge e7(h.Id(), g.Id(), 5);
  Edge e8(h.Id(), k.Id(), 4);
  Edge e9(k.Id(), l.Id(), 3);

  Node c1("C1"), c2("C2"), c3("C3");
  Edge ec1(c1.Id(), c2.Id(), 1), ec2(c2.Id(), c3.Id(), 1), ec3(c3.Id(), c1.Id(), 1);

  std::string test_name;
  /**
   * Test empty graph creation with set of vertices.
   */
  test_name = "empty directed graph creation with only vertices and no edges";
  std::vector<Node> graph_nodes = std::vector<Node>({a, b, c});
  DirectedGraph empty_dg = DirectedGraph(graph_nodes);
  run(test_name, test_total);
  if (empty_dg.V() != 3) {
    test_flag = false;
    std::cout << "Required vertices = " << graph_nodes.size() << ", Found = " << empty_dg.V() << std::endl;
  }
  if (empty_dg.E() != 0) {
    test_flag = false;
    std::cout << "Required edges = 0, Found = " << empty_dg.E() << std::endl;
  }

  test_flag? ok(test_name, test_pass) : fail(test_name, test_fail);
  test_flag = true;

  /**
   * Test graph creation with list of edges.
   */
  test_name = "directed graph creation with edges";
  std::vector<Edge> graph_edges = std::vector<Edge>({e1, e2});
  DirectedGraph dg = DirectedGraph(graph_edges);
  run(test_name, test_total);
  if (dg.V() != 3) {
    test_flag = false;
    std::cout << "Required vertices = " << graph_nodes.size()  << ", Found = " << dg.V() << std::endl;
  }
  if (dg.E() != 2) {
    test_flag = false;
    std::cout << "Required edges = " << graph_edges.size() << ", Found = " << dg.E() << std::endl;
  }

  test_flag? ok(test_name, test_pass) : fail(test_name, test_fail);
  test_flag = true;

  /**
   * Test DFS.
   */
  test_name = "DFS";
  run(test_name, test_total);
  dg.AddEdge(e3);
  dg.DFS("A");
  dg.PrintPath("D");

  test_flag? ok(test_name, test_pass) : fail(test_name, test_fail);
  test_flag = true;

  /**
   * Test topological sorting.
   */
  test_name = "topological sorting";
  std::vector<Edge> graph_edges_2 = std::vector<Edge>({e4, e5, e6, e7, e8, e9});
  DirectedGraph dg2 = DirectedGraph(graph_edges_2);

  run(test_name, test_total);
  const auto topological_sort = dg2.TopologicalSort();
  dg2.PrintPath(topological_sort);
  std::vector<std::string> expected_order = std::vector<std::string>({"E", "F", "G", "H", "K", "L"});
  if (expected_order.size() != topological_sort.size()) {
    test_flag = false;
  } else {
    for (int i = 0; i < expected_order.size(); i++) {
      if (expected_order[i] != topological_sort[i]) {
        test_flag = false;
      }
    }
  }
  test_flag? ok(test_name, test_pass) : fail(test_name, test_fail);
  test_flag = true;

  /**
   */
  test_name = "topological sort in cyclic graph";
  run(test_name, test_total);
  DirectedGraph cyclic_graph = DirectedGraph(std::vector<Edge>({ec1, ec2, ec3}));
  const auto topological_sort_2 = cyclic_graph.TopologicalSort();
  if (topological_sort_2.size() != 0) {
    test_flag = false;
  }
  test_flag? ok(test_name, test_pass) : fail(test_name, test_fail);
  test_flag = true;

  /**
   * Print records for total tests, tests that passed and that failed.
   */
  std::cout << "Ran total tests: " << test_total << std::endl;
  std::cout << "Tests Ok: " << test_pass << std::endl;
  std::cout << "Tests Fail: " << test_fail << std::endl << std::endl;

  return 0;
}



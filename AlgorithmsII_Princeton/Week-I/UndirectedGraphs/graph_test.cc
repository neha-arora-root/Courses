#include "graph.h"

#include <iostream>
#include <string>

void PrintRUN(std::string test_name, int& test_total) {
  std::cout << "Test for " << test_name << ": RUN" << std::endl;
  test_total++;
}

void PrintOK(std::string test_name, int& test_pass) {
  test_pass++;
  std::cout << "Test for " << test_name << ": OK" << std::endl;
  std::cout << "-------------------------------------------------------------" << std::endl;
}

void PrintFAIL(std::string test_name, int& test_fail) {
  test_fail++;
  std::cout << "Test for " << test_name << ": FAIL" << std::endl;
  std::cout << "-------------------------------------------------------------" << std::endl;
}

int main() {
  std::cout << std::endl << "TEST SUITE FOR DFS IMPLEMENTATION IN GRAPHS" << std::endl << std::endl;

  int test_pass = 0, test_fail = 0, test_total = 0;

  /**
   * Graph creation with empty edges list.
   */
  int num = 3;
  std::string test_name_empty_edges = "empty edges graph creation";
  std::vector<std::pair<int, int> > empty_edges;
  Graph empty_edges_graph = Graph(num, empty_edges);
  PrintRUN(test_name_empty_edges, test_total);
  empty_edges_graph.PrintGraph();
  if (empty_edges_graph.V() == num && empty_edges_graph.E() == 0) {
    PrintOK(test_name_empty_edges, test_pass);
  } else {
    PrintFAIL(test_name_empty_edges, test_fail);
  }

  /**
   * Graph creation with invalid edges.
   */
  std::string test_name_invalid_edges = "invalid edges graph creation";
  std::vector<std::pair<int, int> > edges;
  edges.push_back(std::make_pair(0,1));
  edges.push_back(std::make_pair(0,2));
  edges.push_back(std::make_pair(0,5));
  edges.push_back(std::make_pair(1,4));
  edges.push_back(std::make_pair(2,3));
  PrintRUN(test_name_invalid_edges, test_total);
  Graph invalid_edges_graph = Graph(4, edges);
  invalid_edges_graph.PrintGraph();
  if (invalid_edges_graph.V() == 4 && invalid_edges_graph.E() == 3) {
    PrintOK(test_name_invalid_edges, test_pass);
  } else {
    PrintFAIL(test_name_invalid_edges, test_pass);
  }

  /**
   * Graph creation with valid edges.
   */
  std::string test_name_valid_edges = "valid edges graph creation";
  PrintRUN(test_name_valid_edges, test_total);
  Graph valid_edges_graph = Graph(6, edges);
  valid_edges_graph.PrintGraph();
  if (valid_edges_graph.V() == 6 && valid_edges_graph.E() == 5) {
    PrintOK(test_name_valid_edges, test_pass);
  } else {
    PrintFAIL(test_name_valid_edges, test_pass);
  }

  /**
   * Test depth first search implementation.
   */
  std::string test_name_dfs = "depth first search traversal";
  PrintRUN(test_name_dfs, test_total);
  std::vector<std::pair<int, int> > dfs_edges;
  dfs_edges.push_back(std::make_pair(0,1));
  dfs_edges.push_back(std::make_pair(1,2));
  dfs_edges.push_back(std::make_pair(2,0));
  dfs_edges.push_back(std::make_pair(3,4));
  Graph dfs_graph(5, dfs_edges);
  // dfs_graph.PrintGraph();
  dfs_graph.DFS(0);
  std::vector<int> expected_path_to_2 {0,1,2};
  std::vector<int> actual_path_to_2 = dfs_graph.Path(2);
  bool test_flag = true;
  if (actual_path_to_2.size() != expected_path_to_2.size()) {
    test_flag = false;
  } else {
    for (int i = 0; i < expected_path_to_2.size(); i++) {
      if (expected_path_to_2[i] != actual_path_to_2[i]) {
        test_flag = false;
        break;
      }
    }
  }
  dfs_graph.PrintPath(actual_path_to_2);
  if (test_flag) {
    PrintOK(test_name_dfs, test_pass);
  } else {
    PrintFAIL(test_name_dfs, test_fail);
  }

  /**
   * Test iterative depth first search traversal implementation.
   */
  std::string test_name_iterative_dfs = "iterative depth first search traversal";
  PrintRUN(test_name_iterative_dfs, test_total);
  dfs_graph.DFSIterative(0);
  test_flag = true;
  std::vector<int> actual_path_to_2_iterative = dfs_graph.Path(2);
  if (actual_path_to_2_iterative.size() != expected_path_to_2.size()) {
    test_flag = false;
  } else {
    for (int i = 0; i < expected_path_to_2.size(); i++) {
      if (expected_path_to_2[i] != actual_path_to_2_iterative[i]) {
        test_flag = false;
        break;
      }
    }
  }
  dfs_graph.PrintPath(actual_path_to_2_iterative);
  if (test_flag) {
    PrintOK(test_name_iterative_dfs, test_pass);
  } else {
    PrintFAIL(test_name_iterative_dfs, test_fail);
  }

  /**
   * Test connected components implementation.
   */
  std::string test_name_cc = "connected components";
  PrintRUN(test_name_cc, test_total);
  dfs_graph.ConnectedComponents();
  dfs_graph.PrintConnectedComponents();
  std::vector<int> actual_cc = dfs_graph.GetConnectedComponents();
  std::vector<int> expected_cc {0, 0, 0, 1, 1};
  test_flag = true;
  if (actual_cc.size() != expected_cc.size()) {
    test_flag = false;
  } else {
    for (int i = 0; i < expected_cc.size(); i++) {
      if (expected_cc[i] != actual_cc[i]) {
        test_flag = false;
        break;
      }
    }
  }
  if (test_flag) {
    PrintOK(test_name_cc, test_pass);
  } else {
    PrintFAIL(test_name_cc, test_fail);
  }

  /**
   * Test BFS implementation.
   */
  std::string test_name_bfs = "breadth first search";
  PrintRUN(test_name_bfs, test_total);
  dfs_graph.BFS(0);
  std::vector<int> bfs_path_to_2 = dfs_graph.Path(2);
  std::vector<int> expected_bfs_path_to_2 {0, 2};
  test_flag = true;
  if (bfs_path_to_2.size() != expected_bfs_path_to_2.size()) {
    test_flag = false;
  } else {
    for (int i = 0; i < bfs_path_to_2.size(); i++) {
      if (bfs_path_to_2[i] != expected_bfs_path_to_2[i]) {
        test_flag = false;
        break;
      }
    }
  }
  dfs_graph.PrintPath(bfs_path_to_2);
  if (test_flag) {
    PrintOK(test_name_bfs, test_pass);
  } else {
    PrintFAIL(test_name_bfs, test_fail);
  }

  /**
   * Print records for total tests, tests that passed and that failed.
   */
  std::cout << "Ran total tests: " << test_total << std::endl;
  std::cout << "Tests Ok: " << test_pass << std::endl;
  std::cout << "Tests Fail: " << test_fail << std::endl << std::endl;

  return 0;
}

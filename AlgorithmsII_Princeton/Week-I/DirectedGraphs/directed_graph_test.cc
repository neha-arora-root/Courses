#include "directed_graph.h"

namespace directed_graph {

#define ASSIGN_IF_FALSE(conditional_value, assignee_value) AssignIfFalse(conditional_value, assignee_value)

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

void AssignIfFalse(const bool conditional_value, bool& assignee_value) {
    if (!conditional_value) {
        assignee_value = false;
    }
}

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
void TestEmptyGraphCreation(int& test_total, int& test_pass, int& test_fail) {
	std::string test_name = "empty graph: no vertices, no edges";
	run(test_name, test_total);
	DirectedGraph dg;
	bool test_flag = true;
	if (dg.V() != 0) {
		std::cout << "Non-zeros vertices found." << std::endl;
		test_flag = false;
	}
	if (dg.E() != 0) {
		std::cout << "Non-zeros edges found." << std::endl;
		test_flag = true;
	}
	test_flag? ok(test_name, test_pass) : fail(test_name, test_fail);
}

/**
 * Test empty graph creation with set of vertices.
 */
void TestGraphCreationWithOnlyVertices(int& test_total, int& test_pass, int& test_fail) {
	std::string test_name = "empty directed graph creation with only vertices and no edges";
	run(test_name, test_total);
	bool test_flag = true;
	Node a("A"), b("B"), c("C");
	DirectedGraph dg({a, b, c});

	if (dg.V() != 3) {
	    test_flag = false;
	    std::cout << "Required vertices = " << 3 << ", Found = " << dg.V() << std::endl;
	}
	if (dg.E() != 0) {
	    test_flag = false;
	    std::cout << "Required edges = 0, Found = " << dg.E() << std::endl;
	}
	test_flag? ok(test_name, test_pass) : fail(test_name, test_fail);
}

/**
 * Test graph creation with list of edges.
 */
void TestGraphCreationWithEdges(int& test_total, int& test_pass, int& test_fail) {
	std::string test_name = "directed graph creation with edges";
	run(test_name, test_total);
	bool test_flag = true;
	Node a("A"), b("B"), c("C");
	Edge e1(a.Id(), b.Id(), 1), e2(a.Id(), c.Id(), 1);
	DirectedGraph dg({e1, e2});

	if (dg.V() != 3) {
	    test_flag = false;
	    std::cout << "Required vertices = " << 3 << ", Found = " << dg.V() << std::endl;
	  }
	  if (dg.E() != 2) {
	    test_flag = false;
	    std::cout << "Required edges = 2, Found = " << dg.E() << std::endl;
	  }
	test_flag? ok(test_name, test_pass) : fail(test_name, test_fail);
}

/**
 * Test path creation between nodes via DFS.
 */
void TestPathCreationForNodesWithDFS(int& test_total, int& test_pass, int& test_fail) {
	std::string test_name = "DFS traversal to find path between nodes";
	run(test_name, test_total);
	bool test_flag = true;
	Node a("A"), b("B"), c("C"), d("D"), e("E"), f("F");
	Edge e1(a.Id(), b.Id(), 1), e2(a.Id(), c.Id(), 1), e3(b.Id(), d.Id(), 1), e4(d.Id(), e.Id(), 1);
	DirectedGraph dg({e1, e2, e3, e4});
	dg.DFS(a.Id());
	const std::vector<std::string> expected_path = {"A", "B", "D", "E"};
	const std::vector<std::string> p1 = dg.GetPath(e.Id());
	ASSIGN_IF_FALSE(ComparePaths(p1, expected_path), test_flag);
	dg.PrintPath(p1);
	const std::vector<std::string> p2 = dg.GetPath(a.Id(), e.Id());
	ASSIGN_IF_FALSE(ComparePaths(p2, expected_path), test_flag);
	dg.PrintPath(p2);
	const std::vector<std::string> p3 = dg.GetPath(b.Id(), f.Id());
	dg.PrintPath(p3);
	ASSIGN_IF_FALSE(ComparePaths(p3, {}), test_flag);

	test_flag? ok(test_name, test_pass) : fail(test_name, test_fail);
}

/**
 * Test path creation between nodes via BFS.
 */
void TestPathCreationForNodesWithBFS(int& test_total, int& test_pass, int& test_fail) {
	std::string test_name = "BFS traversal to find path between nodes";
	run(test_name, test_total);
	bool test_flag = true;
	Node a("A"), b("B"), c("C"), d("D"), e("E"), f("F");
	Edge e1(a.Id(), b.Id(), 1), e2(a.Id(), c.Id(), 1), e3(b.Id(), d.Id(), 1), e4(d.Id(), e.Id(), 1);
	DirectedGraph dg({e1, e2, e3, e4});
	dg.BFS(a.Id());
	const std::vector<std::string> expected_path = {"A", "B", "D", "E"};
	const std::vector<std::string> p1 = dg.GetPath(e.Id());
	ASSIGN_IF_FALSE(ComparePaths(p1, expected_path), test_flag);
	dg.PrintPath(p1);
	dg.BFS(b.Id());
	const std::vector<std::string> p2 = dg.GetPath(f.Id());
	dg.PrintPath(p2);
	ASSIGN_IF_FALSE(ComparePaths(p2, {}), test_flag);

	test_flag? ok(test_name, test_pass) : fail(test_name, test_fail);
}

/**
* Print records for total tests, tests that passed and that failed.
*/
void PrintStats(int& test_total, int& test_pass, int& test_fail) {
	std::cout << "Ran total tests: " << test_total << std::endl;
	std::cout << "Tests Ok: " << test_pass << std::endl;
	std::cout << "Tests Fail: " << test_fail << std::endl << std::endl;
}

}  // namespace directed_graph

int main () {
  std::cout << std::endl << "TEST SUITE FOR DIRECTED GRAPHS" << std::endl << std::endl;

  int test_pass = 0, test_fail = 0, test_total = 0;
  directed_graph::TestEmptyGraphCreation(test_total, test_pass, test_fail);
  directed_graph::TestGraphCreationWithOnlyVertices(test_total, test_pass, test_fail);
  directed_graph::TestGraphCreationWithEdges(test_total, test_pass, test_fail);
  directed_graph::TestPathCreationForNodesWithDFS(test_total, test_pass, test_fail);
  directed_graph::TestPathCreationForNodesWithBFS(test_total, test_pass, test_fail);

  directed_graph::PrintStats(test_total, test_pass, test_fail);
}
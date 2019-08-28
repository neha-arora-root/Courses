#include "topological_sort.h"
#include "../test_utils.h"

namespace directed_graph {

void TestCycleInGraph(testing::Testing& test_suite) {
	test_suite.init("test cycle in graph");
	Node a("A"), b("B"), c("C"), d("D"), e("E"), f("F");
	Edge e1(a.Id(), b.Id(), 1), e2(b.Id(), c.Id(), 1), e3(c.Id(), a.Id(), 1), e4(d.Id(), e.Id(), 1), e5(d.Id(), f.Id(), 1), e6(e.Id(), f.Id(), 1);
	TopologicalSort dg_1({e1, e2, e3});
	test_suite.test(dg_1.IsCyclic());
	TopologicalSort dg_2({e4, e5, e6});
	test_suite.test(!dg_2.IsCyclic());
	test_suite.TestResults();
}

void TestTopologicalSorting(testing::Testing& test_suite) {
	test_suite.init("test topological sorting in graph");
	Node a("A"), b("B"), c("C"), d("D"), e("E"), f("F"), g("G");
	Edge e1(a.Id(), b.Id(), 1), e2(b.Id(), c.Id(), 1), e3(c.Id(), a.Id(), 1);
	TopologicalSort dg_1({e1, e2, e3});
	const std::vector<std::string> order_1 = dg_1.TopologicallySorted();
	test_suite.test(order_1.size() == 0);

	Edge e4(a.Id(), b.Id(), 1), e5(a.Id(), c.Id(), 1), e6(b.Id(), d.Id(), 1), e7(c.Id(), d.Id(), 1), e8(d.Id(), f.Id(), 1), e9(e.Id(), f.Id(), 1), e10(f.Id(), g.Id(), 1);
	TopologicalSort dg_2({e4, e5, e6, e7, e8, e9, e10});
	// dg_2.PrintAllEdges();
	const std::vector<std::string> order_2 = dg_2.TopologicallySorted();
	std::unordered_map<std::string, int> nodes_positions;
	for (int i = 0; i < order_2.size(); i++) { 
		nodes_positions[order_2[i]] = i; 
	}
	// The following ordering should hold for topological sorting.
	test_suite.test(nodes_positions["A"] < nodes_positions["B"]);
	test_suite.test(nodes_positions["A"] < nodes_positions["C"]);
	test_suite.test(nodes_positions["B"] < nodes_positions["D"]);
	test_suite.test(nodes_positions["C"] < nodes_positions["D"]);
	test_suite.test(nodes_positions["D"] < nodes_positions["F"]);
	test_suite.test(nodes_positions["E"] < nodes_positions["F"]);
	test_suite.test(nodes_positions["F"] < nodes_positions["G"]);
	dg_2.PrintOrder(order_2);
	test_suite.TestResults();
}

}  // namespace directed_graph


int main () {
  testing::Testing test_suite("TEST SUITE FOR DIRECTED GRAPHS");

  directed_graph::TestCycleInGraph(test_suite);
  directed_graph::TestTopologicalSorting(test_suite);

  test_suite.PrintStats();
}
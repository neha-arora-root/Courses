#include "topological_sort.h"

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
* Print records for total tests, tests that passed and that failed.
*/
void PrintStats(int& test_total, int& test_pass, int& test_fail) {
	std::cout << "Ran total tests: " << test_total << std::endl;
	std::cout << "Tests Ok: " << test_pass << std::endl;
	std::cout << "Tests Fail: " << test_fail << std::endl << std::endl;
}

void TestCycleInGraph(int& test_total, int& test_pass, int& test_fail) {
	std::string test_name = "test cycle in graph";
	run(test_name, test_total);
	bool test_flag = true;
	Node a("A"), b("B"), c("C"), d("D"), e("E"), f("F");
	Edge e1(a.Id(), b.Id(), 1), e2(b.Id(), c.Id(), 1), e3(c.Id(), a.Id(), 1), e4(d.Id(), e.Id(), 1), e5(d.Id(), f.Id(), 1), e6(e.Id(), f.Id(), 1);
	TopologicalSort dg_1({e1, e2, e3});
	ASSIGN_IF_FALSE(dg_1.IsCyclic(), test_flag);
	TopologicalSort dg_2({e4, e5, e6});
	ASSIGN_IF_FALSE(!dg_2.IsCyclic(), test_flag);
	test_flag? ok(test_name, test_pass) : fail(test_name, test_fail);
}

void TestTopologicalSorting(int& test_total, int& test_pass, int& test_fail) {
	std::string test_name = "test topological sorting in graph";
	run(test_name, test_total);
	bool test_flag = true;
	Node a("A"), b("B"), c("C"), d("D"), e("E"), f("F"), g("G");
	Edge e1(a.Id(), b.Id(), 1), e2(b.Id(), c.Id(), 1), e3(c.Id(), a.Id(), 1);
	TopologicalSort dg_1({e1, e2, e3});
	const std::vector<std::string> order_1 = dg_1.TopologicallySorted();
	ASSIGN_IF_FALSE(order_1.size() == 0, test_flag);

	Edge e4(a.Id(), b.Id(), 1), e5(a.Id(), c.Id(), 1), e6(b.Id(), d.Id(), 1), e7(c.Id(), d.Id(), 1), e8(d.Id(), f.Id(), 1), e9(e.Id(), f.Id(), 1), e10(f.Id(), g.Id(), 1);
	TopologicalSort dg_2({e4, e5, e6, e7, e8, e9, e10});
	// dg_2.PrintAllEdges();
	const std::vector<std::string> order_2 = dg_2.TopologicallySorted();
	std::unordered_map<std::string, int> nodes_positions;
	for (int i = 0; i < order_2.size(); i++) { 
		nodes_positions[order_2[i]] = i; 
	}
	// The following ordering should hold for topological sorting.
	ASSIGN_IF_FALSE(nodes_positions["A"] < nodes_positions["B"], test_flag);
	ASSIGN_IF_FALSE(nodes_positions["A"] < nodes_positions["C"], test_flag);
	ASSIGN_IF_FALSE(nodes_positions["B"] < nodes_positions["D"], test_flag);
	ASSIGN_IF_FALSE(nodes_positions["C"] < nodes_positions["D"], test_flag);
	ASSIGN_IF_FALSE(nodes_positions["D"] < nodes_positions["F"], test_flag);
	ASSIGN_IF_FALSE(nodes_positions["E"] < nodes_positions["F"], test_flag);
	ASSIGN_IF_FALSE(nodes_positions["F"] < nodes_positions["G"], test_flag);
	dg_2.PrintOrder(order_2);
	test_flag? ok(test_name, test_pass) : fail(test_name, test_fail);
}

}  // namespace directed_graph


int main () {
  std::cout << std::endl << "TEST SUITE FOR DIRECTED GRAPHS" << std::endl << std::endl;

  int test_pass = 0, test_fail = 0, test_total = 0;
  directed_graph::TestCycleInGraph(test_total, test_pass, test_fail);
  directed_graph::TestTopologicalSorting(test_total, test_pass, test_fail);
  directed_graph::PrintStats(test_total, test_pass, test_fail);
}
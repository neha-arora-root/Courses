#include "connected_components.h"
#include "../test_utils.h"

namespace graph {

	void TestConnectedComponents(testing::Testing& test_suite) {
		test_suite.init("DFS traversal to find path between nodes");
	    Node a("A"), b("B"), c("C"), d("D"), e("E"), f("F"), g("G"), h("H");
	    Edge e1(a.Id(), b.Id(), 1), e2(b.Id(), c.Id(), 1), e3(c.Id(), a.Id(), 1), e4(d.Id(), e.Id(), 1), e5(e.Id(), f.Id(), 1), e6(f.Id(), d.Id(), 1), e7(f.Id(), g.Id(), 1);
	    ConnectedComponents graph({e1, e2, e3, e4, e5, e6, e7});
	    graph.AddVertex(h);
	    auto cc = graph.GetConnectedComponents();
	    test_suite.test(cc.size() == 8);
	    int cc_1 = cc["A"];
	    test_suite.test(cc["B"] == cc_1);
	    test_suite.test(cc["C"] == cc_1);
	    int cc_2 = cc["D"];
	    test_suite.test(cc["D"] == cc_2);
	    test_suite.test(cc["E"] == cc_2);
	    test_suite.test(cc["F"] == cc_2);
	    test_suite.test(cc["G"] == cc_2);
	    int cc_3 = cc["H"];
	    test_suite.test(cc_3 != cc_1);
	    test_suite.test(cc_3 != cc_2);

	    graph.PrintConnectedComponents(cc);
	    test_suite.TestResults();
	}

}  // namespace graph

int main() {
	testing::Testing test_suite("CONNECTED COMPONENTS IN GRAPHS");
	graph::TestConnectedComponents(test_suite);

	test_suite.PrintStats();
}
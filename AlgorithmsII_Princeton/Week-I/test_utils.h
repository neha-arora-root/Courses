#ifndef TEST_UTILS_H_
#define TEST_UTILS_H_

#include <iostream>

namespace testing {

  class TestUnit {
    public:
      TestUnit(const std::string& test_name) : test_name_(test_name) {
        std::cout << "Test for " << test_name_ << ": RUN" << std::endl;
      }

      ~TestUnit() {}

      /**
       * Print the test being run when the result is as expected.
       */
      void ok() {
        std::cout << "Test for " << test_name_ << ": OK" << std::endl;
        std::cout << "----------------------------------------------------------------------------------" << std::endl;
      }

      /**
       * Print the test being run when the result is not as expected.
       */
      void fail() {
        std::cout << "Test for " << test_name_ << ": FAIL" << std::endl;
        std::cout << "-----------------------------------------------------------------------------------" << std::endl;
      }


    private:
      const std::string test_name_;
  };

  class Testing {

    public:

      Testing(const std::string& heading) : test_total_(0), test_pass_(0), test_fail_(0) {
        std::string base = "TEST SUITE";
        if (!heading.empty()) {
          base += " FOR " + heading;
        }
        std::cout << std::endl << base << std::endl << std::endl;
      }

      void set_test_flag(bool value) {
        test_flag_ = value;
      }

      void init(const std::string& test_name) {
      	test_flag_ = true;
        test_total_++;
        unit = new testing::TestUnit(test_name);
      }

      void test(const bool condition) {
	    if (!condition) {
	      test_flag_ = false;
	    }
	  }

      /**
       * Update the count of passing or failing tests and print whether the particular test passed or failed.
       */
      void TestResults() {
        test_flag_? unit->ok() : unit->fail();
        test_flag_? test_pass_++ : test_fail_++;

        delete unit;
      }

      /**
       * Print records for total tests, tests that passed and that failed.
       */
      void PrintStats() {
        std::cout << "Tests Run  : " << test_total_ << std::endl;
        std::cout << "Tests Ok   : " << test_pass_ << std::endl;
        std::cout << "Tests Fail : " << test_fail_ << std::endl << std::endl;
      }

    private:
      int test_total_, test_pass_, test_fail_;
      bool test_flag_;
      testing::TestUnit *unit;
  };

}  // namespace testing

#endif /* TEST_UTILS_H_ */

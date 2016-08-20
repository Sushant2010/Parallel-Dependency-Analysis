#include <iostream>

namespace TestH {
	class SomeTestSuite {
	public:
		SomeTestSuite() { SomeTestSuite::test; }
	private:
		void test()
		{
			std::cout << "this is a test";

		}
	};

	bool run_tests()
	{
		SomeTestSuite sts;

		return false;
	}
}
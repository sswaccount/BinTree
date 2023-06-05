#include "TestData.h"
#include "TestSolution.h"
#include "SolutionTry_1.h"
int main()
{
	TestData td(10);

	TestSolution ts1(td);
	ts1.run();

	TestSolution<SolutionTry_1> ts2(td);
	ts2.run();

	//SolutionTry_1 st1("./data/data_1/data_1");
	//cout << st1.solve() << endl;

	return 0;
}
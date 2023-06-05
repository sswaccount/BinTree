#include "TestData.h"
#include "TestSolution.h"
#include "SolutionTry_1.h"
int main()
{
	TestData td;

	TestSolution ts1(td);
	ts1.run();

	TestSolution<SolutionTry_1> ts2(td);
	ts2.run();

	return 0;
}
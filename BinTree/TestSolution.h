#pragma once

#include "TestData.h"
#include "SolutionStd.h"


template<typename Method=SolutionStd>
class TestSolution
{
public:
	TestSolution(const TestData& td);

	void run();

protected:
	double solve(const string& datapath);
	vector<string> testdatapath;
	unsigned int total;
};


template<typename Method>
TestSolution<Method>::TestSolution(const TestData& td)
	: testdatapath(td.get_data_path()) {
	total = testdatapath.size();
}

template<typename Method>
void TestSolution<Method>::run()
{
	double ans = 0;
	for (unsigned int i = 0; i < total; ++i)
	{
		ans += solve(testdatapath[i]);
	}
	cout << Method::method_name << " : 平均剩余优化空间 : " << ans / total * 100 << "%\n";
}

template<typename Method>
double TestSolution<Method>::solve(const string& datapath)
{
	Method method(datapath);
	idx current_method_answer = method.solve();

	idx best_method_answer, value_limit;
	ReadFileStream read(datapath + ".out");
	read >> best_method_answer >> value_limit;
	
	if (best_method_answer == value_limit)
		return 0.0;
	return 1.0 * (current_method_answer - best_method_answer) / (value_limit - best_method_answer);
}
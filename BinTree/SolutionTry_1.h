#pragma once

#include "SolutionBase.h"

class SolutionTry_1 : public SolutionBase 
{
public:
	SolutionTry_1(const string& filepath_);
	int solve();

	static string method_name;

private:
	idx compute_cost(idx id = 1);
	vector<idx> cost;
};


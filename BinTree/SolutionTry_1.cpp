#include "SolutionTry_1.h"

string SolutionTry_1::method_name = "Method_Try_1";


SolutionTry_1::SolutionTry_1(const string& filepath_)
	:SolutionBase(filepath_) {
	input();
}


int SolutionTry_1::solve()
{
	cost = vector<idx>(1 << TREEDEPTH, 0);
	compute_cost();

	return cost[1];
}

idx SolutionTry_1::compute_cost(idx id)
{
	if (w[id] != 0) {
		cost[id] = w[id];
		return cost[id];
	}
	cost[id] = compute_cost(id << 1) + compute_cost((id << 1) + 1) + w[id];
	return cost[id];
}


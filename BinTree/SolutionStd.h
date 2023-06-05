#pragma once

#include "using_head.h"
#include "SolutionBase.h"

class SolutionStd : public SolutionBase
{
public:
	SolutionStd(const string& path_);
	int solve();
	static string method_name;

private:
	void print(GRBModel &model, vector<GRBVar>& vgv);
	int get(GRBVar& var);
	void generate();
	string filename;
	//fs::path path;
	GRBEnv *env;
};


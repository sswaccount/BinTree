#pragma once

#include "using_head.h"
#include "param.h"

class SolutionBase
{
public:
	SolutionBase(const string& filepath_);
	virtual int solve() = 0;
protected:
	void input(idx size_1 = (1 << TREEDEPTH),
		idx size_2 = (1 << TREEDEPTH),
		idx size_3 = TREEDEPTH);

	string filepath;

	// 构建节点的映射，不浪费空间，
	// 否则需要申请(1<<TREEDEPTH+1)数据

	// 但为了方便理解，暂时改为idx vector
	vector<bool> x;
	vector<idx> w;
	vector<idx> count;
};


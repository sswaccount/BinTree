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

	// �����ڵ��ӳ�䣬���˷ѿռ䣬
	// ������Ҫ����(1<<TREEDEPTH+1)����

	// ��Ϊ�˷�����⣬��ʱ��Ϊidx vector
	vector<bool> x;
	vector<idx> w;
	vector<idx> count;
};


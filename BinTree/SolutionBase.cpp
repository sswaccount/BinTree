#include "SolutionBase.h"
#include "file_stream.h"

SolutionBase::SolutionBase(const string& filepath_)
	:filepath(filepath_)
{
}

void SolutionBase::input(idx size_1, idx size_2, idx size_3) {
	x = vector<bool>(size_1, false);
	w = vector<idx>(size_2, 0);
	count = vector<idx>(size_3, 0);

	ReadFileStream read(filepath + ".in");
	int flag;
	while (read >> flag)
	{
		if (flag == 0)
		{
			int id, weight;
			read >> id >> weight;
			w[id] = weight;
		}
		else if (flag == 1)
		{
			int father, son;
			read >> father >> son;
			x[father] = x[son] = true;
		}
		else
		{
			for (auto& i : count)
				read >> i;
			break;
		}
	}

}
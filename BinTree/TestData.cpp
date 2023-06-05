#include "TestData.h"
#include "SolutionStd.h"
#include "util.h"

string TestData::mainpath = "data_";

TestData::TestData(int n)
{
    int num = count_dir_num("./data");
    srand((unsigned)time(NULL));
    for (int i = 1; i <= n; ++i)
    {
        stringstream ss;
        string name;
        ss << i;
        ss >> name;
        data.push_back(mainpath + name);
    }

    if (num == data.size())
    {
        for (auto& i : data)
            data_path.push_back(i.get_postfix_path());
        return;
    }

    for (auto& i : data)
    {
        i.write_indata();
        i.write_dotdata();
        i.generate_png();
        data_path.push_back(i.get_postfix_path());
    }

    for (auto& i : data_path)
    {
        SolutionStd stdans(i);
        stdans.solve();
    }
}

vector<string> TestData::get_data_path() const
{
    return data_path;
}
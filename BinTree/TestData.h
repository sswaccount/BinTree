#pragma once

#include "MakeSeq.h"

class TestData
{
public:
    TestData(int n = 10);
    vector<string> get_data_path() const;

private:

    vector<MakeSeq> data;
    vector<string> data_path;
    static string mainpath;
};

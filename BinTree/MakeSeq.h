#pragma once

#include "tree.h"

class MakeSeq
{
public:
    MakeSeq(const string& filename);

    void write_indata();
    void write_dotdata();
    void generate_png();

    string get_postfix_path();

private:
    Node* root, * outroot;
    string postfix_path;
    vector<idx> makeseq(Node*);
    void check_vaild(vector<idx>&);
    vector<idx> xi, xi_;
};



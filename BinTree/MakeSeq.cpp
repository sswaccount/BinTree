#include "MakeSeq.h"
#include "util.h"

MakeSeq::MakeSeq(const string& filename)
    : postfix_path(prefix_path + filename + "/" + filename)
{
    string command = prefix_path + filename;
    create_dir(command);

    root = random_tree(0, 1);
    outroot = random_tree(0, 1);

    xi = makeseq(root);
    xi_ = makeseq(outroot);
}

void MakeSeq::write_indata()
{
    WriteFileStream wf(postfix_path + ".in");
    outputSTD(wf, root);

    // Êä³ö½á¹û
    wf << "2 ";
    for (auto i : xi_)
        wf << i << ' ';
    wf << '\n';
}

void MakeSeq::write_dotdata()
{
    WriteFileStream wf(postfix_path + ".dot");
    wf << "graph g {\ngraph[ordering=\"out\"];\n";
    output(wf, root);
    wf << "}\n";
}

void MakeSeq::generate_png()
{
    string param = dot_ + postfix_path + dot_dot +
        GRAPHVIZPARAM + postfix_path + dot_png;
    system(param.data());
}

vector<idx> MakeSeq::makeseq(Node* root_)
{
    vector<idx> temp = vector<idx>(TREEDEPTH);

    count(root_, temp);

    check_vaild(temp);

    return temp;
}

void MakeSeq::check_vaild(vector<idx>& temp)
{
    int num = pow(2, TREEDEPTH);
    int ans = 0;
    int base = num;
    for (auto i : temp)
    {
        ans += i * base;
        base /= 2;
    }
    if (ans != num)
    {
        cout << "error at generate bintree data\n";
        exit(-1);
    }
}


string MakeSeq::get_postfix_path()
{
    return postfix_path;
}
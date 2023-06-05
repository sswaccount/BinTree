#include "tree.h"
#include "util.h"

bool judge(int depth)
{
    int num = rand() % 100;
    if (depth * 100.0 / TREEDEPTH > num)
        return false;
    return true;
}

Node* random_tree(int depth, int id)
{
    if (depth == TREEDEPTH)
        return nullptr;
    Node* root = new Node(id, randomInt(NUMUP, NUMDOWN));
    if (judge(depth))
    {
        root->left = random_tree(depth + 1, id * 2);
        root->right = random_tree(depth + 1, id * 2 + 1);
    }
    return root;
}

void output(WriteFileStream& wf, Node* root)
{
    if (root == nullptr)
        return;
    if (root->left != nullptr)
    {
        wf << root->id
            << "[label=\"\", shape=circle, width=0.5];\n";
        wf << root->id << "--" << root->left->id << ";\n";
        wf << root->id << "--" << root->right->id << ";\n";
    }
    else
    {
        wf << root->id << "[label=\""
            << root->key << "\",shape=circle, width=0.5];\n";
    }
    output(wf, root->left);
    output(wf, root->right);
}

void outputSTD(WriteFileStream& wf, Node* root)
{
    if (root == nullptr)
        return;
    if (root->left == nullptr)
    {
        wf << "0 " << root->id << " " << root->key << endl;
    }
    else
    {
        wf << "1 " << root->id << " " << root->left->id << endl;
        wf << "1 " << root->id << " " << root->right->id << endl;
    }
    outputSTD(wf, root->left);
    outputSTD(wf, root->right);
}

void count(Node* root, vector<idx>& temp, int depth)
{
    if (root->left == nullptr)
        ++temp[depth];
    else
    {
        count(root->left, temp, depth + 1);
        count(root->right, temp, depth + 1);
    }
}
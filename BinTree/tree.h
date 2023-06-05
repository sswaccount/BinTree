#pragma once

#include "file_stream.h"
#include "param.h"

struct Node
{
    int id;
    int key;
    Node* left, * right;
    Node(int id_, int key_ = 0)
        : id(id_), key(key_), left(nullptr), right(nullptr) {}
    ~Node()
    {
        delete left;
        delete right;
    }
};

bool judge(int);

Node* random_tree(int, int);

void output(WriteFileStream&, Node*);

void outputSTD(WriteFileStream&, Node*);

void count(Node* root, vector<idx>& temp, int depth = 0);


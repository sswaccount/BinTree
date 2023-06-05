#pragma once

#include "using_head.h"

typedef unsigned int idx;

constexpr unsigned int TREEDEPTH = 5;
constexpr unsigned int NUMUP = 1;
constexpr unsigned int NUMDOWN = 50;

const string GRAPHVIZPARAM = " | gvpr -c -f ./binarytree.gvpr | neato -n -Tpng -o ";
const string dot_ = "dot ";
const string dot_dot = ".dot";
const string dot_png = ".png";
const string prefix_path = "./data/";
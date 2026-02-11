// bridges.hpp
// Jenae Matson
// 2025-09-24
// Header for CS411 Assignment 2

#pragma once
#include <vector>

using std::vector;

using Brg = vector<int>;

// bridges
// Defined in source file
int bridges(int w, int e,
            const vector<Brg> & bridges);

// bridges_recurse
// Defined in source file
int bridges_recurse(const vector<Brg> & bridges, vector<Brg> current_solution,
                    int index, int west, int east, int profit);
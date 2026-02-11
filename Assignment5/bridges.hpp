// bridges.hpp
// Jenae Matson
// 2025-11-03
// Header for CS411 Assignment 5

#pragma once
#include <vector>

using Brg = std::vector<int>;

// bridges
// Defined in source file
int bridges(int w, int e, const std::vector<Brg> & bridges);

// canbuild
// Defined in source file
bool canbuild(const Brg & a, const Brg & b);
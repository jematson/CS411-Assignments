// bridges.cpp
// Jenae Matson
// 2025-09-24
// Source for CS411 Assigment 2

#include "bridges.hpp"
#include <vector>
using std::vector;

using Brg = vector<int>;

// bridges
// Determine the maximum toll that can be collected from 
// the given collection of bridges.
int bridges(int w, int e,
            const vector<Brg> & bridges)
{
    // Initialize an empty solution
    vector<Brg> solution;

    return bridges_recurse(bridges, solution, 0, w, e, 0);
}


// bridges_recurse
// Given a partial set of bridges to build, return the highest profit 
// from either building (if possible) or not building the next bridge.
int bridges_recurse(const vector<Brg> & bridges, vector<Brg> current_solution,
                    int index, int west, int east, int profit) 
{

    // BASE CASE
    // Reached the end of the list of bridges
    if (index == bridges.size()) {

        return profit;
    }

    // RECURSIVE CASE

    // Make a recursive call that doesn't include the next bridge
    int right_profit = bridges_recurse(bridges, current_solution, index + 1, west, east, profit);

    // Attempt to add the next bridge
    bool illegal = false;
    Brg a = bridges[index];
    int left_profit = profit;

    // Check the current bridge against all others in the solution
    for (int i = 0; i < current_solution.size(); ++i) {
        Brg b = current_solution[i];

        // Bridges cannot cross each other
        if ( a[0] < b[0] && a[1] > b[1] ) {
            illegal = true;
            break;
        } else if ( a[0] > b[0] && a[1] < b[1] ) {
            illegal = true;
            break;
        // Cities can have only one bridge each
        } else if ( a[0] == b[0] || a[1] == b[1] ) {
            illegal = true;
            break;
        }
    }
    
    // If it doesn't conflict, build the bridge and add its toll to the profit
    if (!illegal) {
        current_solution.push_back(a);
        left_profit += a[2];

        // Unless the added bridge spans a northernmost city to a southernmost city,
        // make a recursive call including the new bridge
        if (!(a[0] == 0 && a[1] == east - 1) && !(a[0] == west - 1 && a[1] == 0)) {

            left_profit = bridges_recurse(bridges, current_solution, index + 1, west, east, left_profit);
        }
    }

    // Return the profit of the most profitable branch
    profit = left_profit > right_profit ? left_profit : right_profit;

    return profit;
}
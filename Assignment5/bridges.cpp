// bridges.cpp
// Jenae Matson
// 2025-11-03
// Source for CS411 Assigment 5

#include "bridges.hpp"
#include <vector>
using std::vector;
#include <algorithm>
using std::sort;

using Brg = vector<int>;

// bridges
// Determine the maximum toll that can be collected from 
// the given collection of bridges.
int bridges(int w, int e, const vector<Brg> & bridges)
{
    int n = bridges.size();

    // If no bridges, return 0
    if ( n < 1 ) {
        return 0;
    }
    // If only 1 bridge, return its toll
    if ( n == 1 ) {
        return bridges[0][2];
    }

    // Make copy of bridges to sort by west city
    vector<Brg> bridgeCopy = bridges;
    sort(bridgeCopy.begin(), bridgeCopy.end(),
            [](const Brg& a, const Brg& b) {
                return a[0] < b[0];
            });

    // tolls[i] holds the highest toll possible using bridge i and any before it
    vector<int> tolls(n, 0);

    // tolls[0] is just the value of the first bridge
    tolls[0] = bridgeCopy[0][2];

    int bestToll = tolls[0];

    for (int i = 1; i < n; i++) {
        // Start tolls[i] as just the toll for bridge i
        tolls[i] = bridgeCopy[i][2];

        // Track most profitable subsolution before i that i can be added to
        int best_subsol = 0;

        // Iterate over all calculated subsolutions of bridges before i
        for (int j = i-1; j >= 0; j--) {
            // If bridges i and j don't cross, then bridge i can be added to j's subsolution
            if (canbuild(bridgeCopy[i], bridgeCopy[j])) {
                if (tolls[j] > best_subsol)
                    best_subsol = tolls[j];
            }
        }

        // Add up the most profitable subsolution toll available for bridge i
        tolls[i] += best_subsol;

        if (tolls[i] > bestToll)
            bestToll = tolls[i];
    }

    return bestToll;
}

// canbuild
// Returns true if the given bridges can be built together
bool canbuild(const Brg & a, const Brg & b) {
    bool illegal = false;
    // Bridges cannot cross each other
    if ( a[0] < b[0] && a[1] > b[1] ) {
        illegal = true;
    } else if ( a[0] > b[0] && a[1] < b[1] ) {
        illegal = true;
    // Cities can have only one bridge each
    } else if ( a[0] == b[0] || a[1] == b[1] ) {
        illegal = true;
    }
    return !illegal;
}
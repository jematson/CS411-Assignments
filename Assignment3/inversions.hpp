// inversions.hpp
// Jenae Matson
// 2025-10-04
// Header for CS411 Assignment 3 Exercise B

#pragma once

#include <vector>
using std::vector;
#include <cstddef>
using std::size_t;
#include <utility>
using std::swap;
using std::move;
#include <iterator>
using std::begin;
using std::end;
using std::iterator_traits;
#include <algorithm>
using std::move;


// stableMerge
// Merge two sorted sequences of data into one, returning the number of inversions.
// Modified from Professor Glenn Chappell's stableMerge
template <typename RAIter>
size_t stableMerge(RAIter first, RAIter middle, RAIter last)
{
    size_t total = 0;

    using Value = typename iterator_traits<RAIter>::value_type;

    vector<Value> buffer(last - first); // Buffer for temporary copy of data
    auto in1 = first;          // Read location in 1st half
    auto in2 = middle;         // Read location in 2nd half
    auto out = buffer.begin();  // Write location in buffer

    // Merge two sorted lists into a single list in buff.
    while (in1 != middle && in2 != last)
    {
        if (*in2 < *in1) {  // Must do comparison this way, to be stable.
            *out++ = std::move(*in2++);
            total += (middle - in1);    // Add inversions.
        } else {
            *out++ = std::move(*in1++);
        }
    }

    // Move remainder of original sequence to buffer.
    move(in1, middle, out);
    move(in2, last, out);

    // Move buffer contents back to original sequence location.
    move(buffer.begin(), buffer.end(), first);

    return total;
}


// inversions
// Return the number of inversions in the given sequence using mergeSort
// Modified from Professor Glenn Chappell's iterativeMergeSort
template<typename RAIter>
size_t inversions(RAIter first, RAIter last)
{
    // Initialize the number of inversions
    size_t total = 0;

    // Compute size of entire range
    size_t size = last - first;

    // We merge ranges of size 1 into ranges of size 2. Then we merge
    // ranges of size 2 into ranges of size 4. This continues until
    // the entire range is sorted.
    //
    // The outer loop goes through sizes: 1, 2, 4, 8, etc. The inner
    // loop goes through pairs of ranges of the current size. Each pair
    // is merged into a single sorted range of twice that size. The last
    // subrange to be merged may need to be shorter.

    size_t partsize = 1;  // Size of two subranges to be merged
    while (partsize < size)
    {
        auto lo = first;  // Start of 1st subrange to be merged
        while (lo + partsize < last)
        {
            auto hi = lo + partsize * 2;
                          // Past end of 2nd subrange to be merged
            if (last < hi)
                hi = last;
            total += stableMerge(lo, lo + partsize, hi);    // Add up inversions

            lo = hi;      // Onward to the next pair of subranges
        }
        partsize *= 2;    // All ranges of current size have been
                          //  merged. Proceed to the next size
    }

    return total;
}
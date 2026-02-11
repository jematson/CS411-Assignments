// contigsum.hpp
// Jenae Matson
// 2025-10-04
// Header for CS411 Assigment 3 Exercise A

#pragma once

#include <vector>
using std::vector;

// Represents the following values of a sequence, in order:
// A: greatest contiguous sum
// B: greatest contiguous sum of a subsequence containing the first value
// C: greatest contiguous sum of a subsequence containing the last value
// D: total sum
using abcd = vector<int>;


// contigSumRecurse
// Given a subsequence of integers, return its abcd values
template<typename RAIter>
abcd contigSumRecurse(RAIter first, RAIter last)
{
    // Initialize abcd values for the subsequence
    abcd result = {0, 0, 0, 0};

    // BASE CASE
    // List size 0
    if (first == last) {
        return result;
    }

    auto size = last - first;

    // List size 1
    if (size == 1) {
        if (*first > 0) {
            result[0] =  *first;
            result[1] = *first;
            result[2] = *first;
        }
        result[3] = *first;
        return result;
    }

    // RECURSIVE CASE
    // List size 2 or more
    auto middle = first + size/2;

    abcd left_result = contigSumRecurse(first, middle);
    abcd right_result = contigSumRecurse(middle, last);

    // Calculate abcd values for the subsequence based on the values of its halves
    vector<int> a_options = {left_result[0], right_result[0], left_result[2]+right_result[1]};
    for (int i = 0; i < a_options.size(); i++) {

        if (a_options[i] > result[0]) {
            result[0] = a_options[i];
        }
    }
    result[1] = left_result[3]+right_result[1] > left_result[1] ? left_result[3]+right_result[1] : left_result[1];
    result[2] = right_result[3]+left_result[2] > right_result[2] ? right_result[3]+left_result[2] : right_result[2];
    result[3] = left_result[3] + right_result[3];

    return result;
}


// contigSum
// Given a sequence of integers, return the greatest contigous sum
template<typename RAIter>
int contigSum(RAIter first, RAIter last)
{
    auto final_result = contigSumRecurse(first, last);

    return final_result[0];
}
// huffcode.hpp
// Jenae Matson
// 2025-11-10
// Header for CS411 Assignment 6

#pragma once

#include <string>
// For std::string
#include <unordered_map>
// For std::unordered_map
#include <memory>
// For std::shared_ptr


// Predeclaring class Node
class Node;


// Class HuffCode
// Encoding & decoding using a Huffman code
class HuffCode {

// ***** HuffCode: ctors, dctor, op= *****
public:

    // Compiler-generated default ctor, copy ctor, copy =, dctor used

// ***** HuffCode: general public functions *****
public:

    void setWeights(const std::unordered_map<char, int> & theweights);

    std::string encode(const std::string & text) const;

    std::string decode(const std::string & codestr) const;

// ***** HuffCode: data members *****
private:

    std::shared_ptr<Node> root;

};  // End class HuffCode


// Class Node
// Define a node of a Huffman tree
class Node {
public:
    int value;
    char letter;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;

    Node(int x) {
        value = x;
        letter = '\0';
        left = nullptr;
        right = nullptr;
    }

    Node(int x, char y) {
        value = x;
        letter = y;
        left = nullptr;
        right = nullptr;
    }
};
// huffcode.cpp
// Jenae Matson
// 2025-11-10
//
// Source for CS411 Assignment 6

#include "huffcode.hpp"  // for class HuffCode declaration
#include <string>
using std::string;
#include <unordered_map>
using std::unordered_map;
#include <queue>
using std::priority_queue;
#include <vector>
using std::vector;
#include <algorithm>
using std::reverse;
#include <memory>
using std::shared_ptr;
using std::make_shared;



void HuffCode::setWeights(const unordered_map<char, int> & theweights)
{
    // Comparison function for Huffman nodes
    auto compare = [] (const shared_ptr<Node>& a, const shared_ptr<Node>& b) {
        return a->value > b->value;
    };

    // Create priority queue of letter with ascending weights
    priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, decltype(compare)> tree(compare);

    // Create a leaf node for each letter
    for (const auto& pair : theweights) {
        shared_ptr<Node> a = make_shared<Node>(pair.second, pair.first);
        tree.push(a);
    }

    // Construc Huffman tree
    while (true) {
        // If one node remaining, assign it as the root of the tree
        if (tree.size() == 1) {
            shared_ptr<Node> newRoot = tree.top();
            root = newRoot;
            break;
        }

        // Get lowest two leaves
        shared_ptr<Node> a = tree.top();
        tree.pop();
        shared_ptr<Node> b = tree.top();
        tree.pop();

        // Give them a parent node
        shared_ptr<Node> c = make_shared<Node>(a->value + b->value);
        c->left = a;
        c->right = b;

        tree.push(c);
    }
}


string encode_recurse(const shared_ptr<Node>& node, const char & letter) {

    //BASE CASE, reached leaf
    if (node->left == nullptr && node->right == nullptr) {
        // Reached the letter we want
        if (node->letter == letter) {
            return "-1";
        // Reached dead end
        } else {
            return "-2";
        }
    }

    // RECURSIVE CASE

    string left = node->left == nullptr ? "-2" : encode_recurse(node->left, letter);

    string right = node->right == nullptr ? "-2" : encode_recurse(node->right, letter);

    if (stoi(left) >= -1) {
        // Add 1 for left branch
        left = stoi(left) == -1 ? "" : left;
        return left + '1';
    } else if (stoi(right) >= -1) {
        // Add 0 for right branch
        right = stoi(right) == -1 ? "" : right;
        return right + '0';
    } else {
        return "-2";
    }
}


string HuffCode::encode(const string & text) const
{
    string answer = "";

    // Handle blank input
    if (text.length() < 1) {
        return answer;
    }

    for (char c : text) {
        string code = encode_recurse(root, c);
        // Code gets built backwards, so reverse
        reverse(code.begin(), code.end());
        answer += code;
    }

    return answer;
}


string HuffCode::decode(const string & codestr) const
{
    string answer = "";

    // Handle blank input
    if (codestr.length() < 1) {
        return answer;
    }

    shared_ptr<Node> node = root;

    // Follow code through the Huffman tree
    for (char c : codestr) {

        // Left for 1
        if (c == '1') {
            node = node->left;

        // Right for 0
        } else if (c == '0') {
            node = node->right;
        }

        // If we reach a leaf, add the letter and return to root
        if (node->letter != '\0') {
            answer += node->letter;
            node = root;
        }
    }

    return answer;
}
#ifndef CLASSESFORPERSISTENTTREE_HPP
#define CLASSESFORPERSISTENTTREE_HPP
#include <memory>

#define ll long long

class RecMod {
public:
    int x, y1, y2, mod;

    RecMod() : x(0), y1(0), y2(0), mod(0) {}
    RecMod(int new_x, int new_y1, int new_y2, int new_mod) : x(new_x), y1(new_y1), y2(new_y2), mod(new_mod) {}
};

class Node {
public:
    ll start, end, mod;
    std::shared_ptr<Node> left, right;

    Node(ll l, ll r) : start(l), end(r) {
        mod = 0;
        left = nullptr;
        right = nullptr;
    }
    Node() : Node(0, 0) {}
    Node(Node const& node) : Node(node.start, node.end) {
        mod = node.mod;
        left = node.left;
        right = node.right;
    }
};

#endif
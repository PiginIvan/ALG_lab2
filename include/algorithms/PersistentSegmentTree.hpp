#ifndef PERSISTENTSEGMENTTREE_HPP
#define PERSISTENTSEGMENTTREE_HPP
#include <vector>
#include <memory>
#include "../objects/rectangle.hpp"
#include "classesForPersistentTree.hpp"

#define ll long long

class PersistentSegmentTree {
private:
    std::vector<int> xUnique, yUnique;
    std::vector<std::shared_ptr<Node>> trees;

    std::shared_ptr<Node> createTree(ll l, ll r);
    std::shared_ptr<Node> modify(const std::shared_ptr<Node>& cur, int l, int r, int mod);
    ll get(const std::shared_ptr<Node>& cur, ll value);
    Point compressPoint(const Point& p);
    void selectUniqueCoords(const std::vector<Rectangle>& rectangles);
    std::vector<RecMod> fillRecMods(const std::vector<Rectangle>& rectangles);
    void buildTree(const std::vector<Rectangle>& rectangles);

public:
    void preprocessing(const std::vector<Rectangle>& rectangles);
    std::vector<ll> countAns(std::vector<Point> points);

};



#endif
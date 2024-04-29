#include "../../include/algorithms/PersistentSegmentTree.hpp"
#include <set>
#include <algorithm>

std::shared_ptr<Node> PersistentSegmentTree::createTree(ll l, ll r) {
    auto root = std::make_shared<Node>(l, r);
    if (l == r) {
        return root;
    }
    ll mid = (l + r) / 2;
    root->left = createTree(l, mid);
    root->right = createTree(mid + 1, r);
    return root;
}

std::shared_ptr<Node> PersistentSegmentTree::modify(const std::shared_ptr<Node>& cur, int l, int r, int mod) {
    if (cur->start >= r || cur->end < l) return cur;
    if (cur->start >= l && cur->end < r) {
        auto newRoot = std::make_shared<Node>(*cur);
        newRoot->mod += mod;
        return newRoot;
    } 
    else {
        auto newRoot = std::make_shared<Node>(*cur);
        newRoot->left = modify(cur->left, l, r, mod);
        newRoot->right = modify(cur->right, l, r, mod);
        return newRoot;
    }
}

ll PersistentSegmentTree::get(const std::shared_ptr<Node>& cur, ll value) {
    ll ans = 0;
    if (cur->right != nullptr && cur->right->start <= value) ans += get(cur->right, value);
    else if (cur->left != nullptr && cur->left->end >= value) ans += get(cur->left, value);
    ans += cur->mod;
    return ans;
}

Point PersistentSegmentTree::compressPoint(const Point& p) {
    Point compressedPoint;
    compressedPoint.x = static_cast<int>((std::lower_bound(xUnique.begin(), xUnique.end(), p.x) - xUnique.begin()));
    compressedPoint.y = static_cast<int>((std::lower_bound(yUnique.begin(), yUnique.end(), p.y) - yUnique.begin()));
    return compressedPoint;
}

void PersistentSegmentTree::selectUniqueCoords(const std::vector<Rectangle>& rectangles) {
    std::set<int> x_coords, y_coords;
    xUnique = std::vector<int>();
    yUnique = std::vector<int>();
    for (const auto& r: rectangles) {
        x_coords.insert(r.low_left.x);
        y_coords.insert(r.low_left.y);
        x_coords.insert(r.top_right.x);
        y_coords.insert(r.top_right.y);
    }
    xUnique.insert(xUnique.begin(), x_coords.begin(), x_coords.end());
    yUnique.insert(yUnique.begin(), y_coords.begin(), y_coords.end());
}

std::vector<RecMod> PersistentSegmentTree::fillRecMods(const std::vector<Rectangle>& rectangles) {
    std::vector<RecMod> mods(rectangles.size() * 2);
    int i = 0;
    for (auto &r: rectangles) {
        Point low_left_point = compressPoint(r.low_left);
        Point top_right_point = compressPoint(r.top_right);
        mods[2 * i] = RecMod(low_left_point.x, low_left_point.y, top_right_point.y, 1);
        mods[2 * i + 1] = RecMod(top_right_point.x, low_left_point.y, top_right_point.y, -1);
        i++;
    }
    std::sort(mods.begin(), mods.end(), [](RecMod a, RecMod b) { if (a.x == b.x) { return a.mod < b.mod; } return a.x < b.x; });
    return mods;
}

void PersistentSegmentTree::buildTree(const std::vector<Rectangle>& rectangles) {
    std::vector<RecMod> mods = fillRecMods(rectangles);
    trees = std::vector<std::shared_ptr<Node>>(xUnique.size());
    std::shared_ptr<Node> startTree;
    if (yUnique.empty()) startTree = nullptr;
    else startTree = createTree(0, yUnique.size() - 1);
    ll modInd = 0, treeInd = 0;
    for (int x = 0; x < xUnique.size(); ++x) {
        std::shared_ptr<Node> curTree;
        if (treeInd == 0) curTree = startTree;
        else curTree = trees[treeInd - 1];
        while (mods[modInd].x == x) {
            curTree = modify(curTree, mods[modInd].y1, mods[modInd].y2, mods[modInd].mod);
            modInd++;
        }
        trees[treeInd++] = curTree;
    }
}

void PersistentSegmentTree::preprocessing(const std::vector<Rectangle>& rectangles) {
    selectUniqueCoords(rectangles);
    buildTree(rectangles);
}

std::vector<ll> PersistentSegmentTree::countAns(std::vector<Point> points) {
    std::vector<ll> ans(points.size());
    for (int i = 0; i < points.size(); i++) {
        auto realXvalue = std::upper_bound(xUnique.begin(), xUnique.end(), points[i].x);
        auto realYvalue = std::upper_bound(yUnique.begin(), yUnique.end(), points[i].y);
        if (realXvalue == xUnique.end() || realXvalue == xUnique.begin() || realYvalue == yUnique.begin() || realYvalue == yUnique.end()) {
            ans[i] = 0;
        }
        else {
            ans[i] = get(trees[realXvalue - xUnique.begin() - 1], realYvalue - yUnique.begin() - 1);
        }
    }
    return ans;
}

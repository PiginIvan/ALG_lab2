#define LAB

// Для оценки времени работы алгоритмов
#ifdef LAB
#include <iostream>
#include <vector>
#include <chrono>
#include <functional>
#include <fstream>
#include "include/dataGenerators.hpp"
#include "include/algorithms/CompleteSearch.hpp"
#include "include/algorithms/CompressionWithMap.hpp"
#include "include/algorithms/PersistentSegmentTree.hpp"

enum Alg_names {
    Complete_Search, 
    Compression_With_Map, 
    Persistent_Segment_Tree
};

ll measure_time(const std::function<void(void)>& algFunction) {
    auto start = std::chrono::high_resolution_clock::now();
    algFunction();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

int main() {
    int countOfTests = 10, countOfAlgs = 3, countOfPoints = 1000;
    auto bruteForceFirstAlg = CompleteSearch();
    auto compressionWithMapSecondAlg = MapSearch();
    auto segmentTreeThirdAlg = PersistentSegmentTree();

    std::vector<Point> pointsFixedNumber = generateAllPoints(countOfPoints);
    std::ofstream outFixedCountOfPoints("resources/resultsFixedCountOfPoints.txt", std::ios::app);
    std::ofstream outDiffCountOfPoints("resources/resultsDiffCountOfPoints.txt", std::ios::app);
    for(int n = 1; n <= 16384; n*=2) {
        std::vector<Rectangle> rectangles = generateAllRectangles(n);
        std::vector<Point> pointsDiffNumber = generateAllPoints(n);

        std::vector<ll> timePrepFixed(countOfAlgs);
        std::vector<ll> timeCountFixed(countOfAlgs);
        std::vector<ll> timePrepDiff(countOfAlgs);
        std::vector<ll> timeCountDiff(countOfAlgs);

        for(int i = 0; i < countOfTests; i++) {
            if(n <= 2048) {
                timePrepFixed[Complete_Search] += measure_time([&bruteForceFirstAlg, &rectangles]() { bruteForceFirstAlg.preprocessing(rectangles); });
                timeCountFixed[Complete_Search] += measure_time([&bruteForceFirstAlg, &pointsFixedNumber]() { bruteForceFirstAlg.countAns(pointsFixedNumber); });
                
                timePrepFixed[Compression_With_Map] += measure_time([&compressionWithMapSecondAlg, &rectangles]() { compressionWithMapSecondAlg.preprocessing(rectangles); });
                timeCountFixed[Compression_With_Map] += measure_time([&compressionWithMapSecondAlg, &pointsFixedNumber]() { compressionWithMapSecondAlg.countAns(pointsFixedNumber); });
                
                timePrepFixed[Persistent_Segment_Tree] += measure_time([&segmentTreeThirdAlg, &rectangles]() { segmentTreeThirdAlg.preprocessing(rectangles); });
                timeCountFixed[Persistent_Segment_Tree] += measure_time([&segmentTreeThirdAlg, &pointsFixedNumber]() { segmentTreeThirdAlg.countAns(pointsFixedNumber); });
            }
            timePrepDiff[Complete_Search] += measure_time([&bruteForceFirstAlg, &rectangles]() { bruteForceFirstAlg.preprocessing(rectangles); });
            timeCountDiff[Complete_Search] += measure_time([&bruteForceFirstAlg, &pointsDiffNumber]() { bruteForceFirstAlg.countAns(pointsDiffNumber); });
            if(n <= 2048) {
                timePrepDiff[Compression_With_Map] += measure_time([&compressionWithMapSecondAlg, &rectangles]() { compressionWithMapSecondAlg.preprocessing(rectangles); });
                timeCountDiff[Compression_With_Map] += measure_time([&compressionWithMapSecondAlg, &pointsDiffNumber]() { compressionWithMapSecondAlg.countAns(pointsDiffNumber); });
            }
            timePrepDiff[Persistent_Segment_Tree] += measure_time([&segmentTreeThirdAlg, &rectangles]() { segmentTreeThirdAlg.preprocessing(rectangles); });
            timeCountDiff[Persistent_Segment_Tree] += measure_time([&segmentTreeThirdAlg, &pointsDiffNumber]() { segmentTreeThirdAlg.countAns(pointsDiffNumber); });    
        }
        if(n <= 2048) {
            timePrepFixed[Complete_Search] /= countOfTests;
            timeCountFixed[Complete_Search] /= countOfTests;
        
            timePrepFixed[Compression_With_Map] /= countOfTests;
            timeCountFixed[Compression_With_Map] /= countOfTests;
       
            timePrepFixed[Persistent_Segment_Tree] /= countOfTests;
            timeCountFixed[Persistent_Segment_Tree] /= countOfTests;
        }
        if(n <= 2048) {
            outFixedCountOfPoints << n << "\n";
            outFixedCountOfPoints << timePrepFixed[Complete_Search] << " " << timeCountFixed[Complete_Search] << " " << timePrepFixed[Complete_Search] + timeCountFixed[Complete_Search] << "\n";
            
            outFixedCountOfPoints << timePrepFixed[Compression_With_Map] << " " << timeCountFixed[Compression_With_Map] << " " << timePrepFixed[Compression_With_Map] + timeCountFixed[Compression_With_Map] << "\n";

            outFixedCountOfPoints << timePrepFixed[Persistent_Segment_Tree] << " " << timeCountFixed[Persistent_Segment_Tree] << " " << timePrepFixed[Persistent_Segment_Tree] + timeCountFixed[Persistent_Segment_Tree] << "\n";
        }

        timePrepDiff[Complete_Search] /= countOfTests;
        timeCountDiff[Complete_Search] /= countOfTests;
        if(n <= 2048) {
            timePrepDiff[Compression_With_Map] /= countOfTests;
            timeCountDiff[Compression_With_Map] /= countOfTests;
        }
        timePrepDiff[Persistent_Segment_Tree] /= countOfTests;
        timeCountDiff[Persistent_Segment_Tree] /= countOfTests;

        outDiffCountOfPoints << n << "\n";
        outDiffCountOfPoints << timePrepDiff[Complete_Search] << " " << timeCountDiff[Complete_Search] << " " << timePrepDiff[Complete_Search] + timeCountDiff[Complete_Search] << "\n";
        if(n <= 2048) {
            outDiffCountOfPoints << timePrepDiff[Compression_With_Map] << " " << timeCountDiff[Compression_With_Map] << " " << timePrepDiff[Compression_With_Map] + timeCountDiff[Compression_With_Map] << "\n";
        }
        else {
            outDiffCountOfPoints << " " << "\n";
        }
        outDiffCountOfPoints << timePrepDiff[Persistent_Segment_Tree] << " " << timeCountDiff[Persistent_Segment_Tree] << " " << timePrepDiff[Persistent_Segment_Tree] + timeCountDiff[Persistent_Segment_Tree] << "\n";

    }

    return 0;
}

#endif

// Для прохождения контеста
#ifdef CONTEST

#include <iostream>
#include <vector>
#include <set>
#include <memory>
#include <algorithm>
#define ll long long

class Point {
public:
    int x, y;

    Point() : x(0), y(0) {}
    Point(int x_coord, int y_coord) : x(x_coord), y(y_coord) {}
    Point(Point& other) : Point(other.x, other.y) {}
    Point(Point const& other) : Point(other.x, other.y) {}

};

class Rectangle {
public:
    Point low_left, top_right;

    Rectangle() : low_left(0, 0), top_right(0, 0) {}
    Rectangle(Point p1, Point p2) : low_left(p1), top_right(p2) {}
    Rectangle(int x1, int y1, int x2, int y2) : low_left(x1, y1), top_right(x2, y2) {}
    Rectangle(Rectangle& other)  : low_left(other.low_left), top_right(other.top_right) {}
    Rectangle(Rectangle const& other) : low_left(other.low_left), top_right(other.top_right) {}

};

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

class PersistentSegmentTree {
private:
    std::vector<int> xUnique, yUnique;
    std::vector<std::shared_ptr<Node>> trees;

    std::shared_ptr<Node> createTree(ll l, ll r) {
        auto root = std::make_shared<Node>(l, r);
        if (l == r) {
            return root;
        }
        ll mid = (l + r) / 2;
        root->left = createTree(l, mid);
        root->right = createTree(mid + 1, r);
        return root;
    }
    std::shared_ptr<Node> modify(const std::shared_ptr<Node>& cur, int l, int r, int mod) {
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
    ll get(const std::shared_ptr<Node>& cur, ll value) {
        ll ans = 0;
        if (cur->right != nullptr && cur->right->start <= value) ans += get(cur->right, value);
        else if (cur->left != nullptr && cur->left->end >= value) ans += get(cur->left, value);
        ans += cur->mod;
        return ans;
    }
    Point compressPoint(const Point& p) {
        Point compressedPoint;
        compressedPoint.x = static_cast<int>((std::lower_bound(xUnique.begin(), xUnique.end(), p.x) - xUnique.begin()));
        compressedPoint.y = static_cast<int>((std::lower_bound(yUnique.begin(), yUnique.end(), p.y) - yUnique.begin()));
        return compressedPoint;
    }
    void selectUniqueCoords(const std::vector<Rectangle>& rectangles) {
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
    std::vector<RecMod> fillRecMods(const std::vector<Rectangle>& rectangles) {
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
    void buildTree(const std::vector<Rectangle>& rectangles) {
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

public:
    void preprocessing(const std::vector<Rectangle>& rectangles) {
        selectUniqueCoords(rectangles);
        buildTree(rectangles);
    }
    std::vector<ll> countAns(std::vector<Point> points) {
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

};

int main() {
    auto segmentTreeThirdAlg = PersistentSegmentTree();
    int n, m;
    std::vector<Rectangle> rectangles;
    std::vector<Point> points;
    std::cin >> n;
    for(int i = 0; i < n; i++) {
        Rectangle r;
        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        r.low_left = Point(x1, y1);
        r.top_right = Point(x2, y2);
        rectangles.push_back(r);
    }
    std::cin >> m;
    for(int i = 0; i < m; i++) {
        Point p;
        int x, y;
        std::cin >> x >> y;
        p.x = x;
        p.y = y;
        points.push_back(p);
    }
    segmentTreeThirdAlg.preprocessing(rectangles);
    std::vector<ll> ans = segmentTreeThirdAlg.countAns(points);
    for(int i = 0; i < ans.size(); i++) {
        std::cout << ans[i] << " ";
    }
    return 0;
}
#endif
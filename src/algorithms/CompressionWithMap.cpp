#include "../../include/algorithms/CompressionWithMap.hpp"
#include <set>

Point MapSearch::compressPoint(const Point& p) {
    Point compressedPoint;
    compressedPoint.x = static_cast<int>((std::lower_bound(xUnique.begin(), xUnique.end(), p.x) - xUnique.begin()));
    compressedPoint.y = static_cast<int>((std::lower_bound(yUnique.begin(), yUnique.end(), p.y) - yUnique.begin()));
    return compressedPoint;
}

void MapSearch::fillMap(const std::vector<Rectangle> &rectangles) {
    map = std::vector<std::vector<ll>>(yUnique.size(), std::vector<ll>(xUnique.size()));
    for (auto& r: rectangles) {
        Point left_border = compressPoint(r.low_left);
        Point right_border = compressPoint(r.top_right);
        for (auto i = left_border.y; i < right_border.y; i++) {
            for (auto j = left_border.x; j < right_border.x; j++) {
                map[i][j] += 1;
            }
        }
    }
}

void MapSearch::selectUniqueCoords(const std::vector<Rectangle>& rectangles) {
    std::set<int> x_coords, y_coords;
    for (auto& r: rectangles) {
        x_coords.insert(r.low_left.x);
        y_coords.insert(r.low_left.y);
        x_coords.insert(r.top_right.x);
        y_coords.insert(r.top_right.y);
    }
    xUnique = std::vector<int>();
    xUnique.insert(xUnique.begin(), x_coords.begin(), x_coords.end());
    yUnique = std::vector<int>();
    yUnique.insert(yUnique.begin(), y_coords.begin(), y_coords.end());
}

void MapSearch::preprocessing(const std::vector<Rectangle>& rectangles) {
    selectUniqueCoords(rectangles);
    fillMap(rectangles);
}

std::vector<ll> MapSearch::countAns(std::vector<Point> points) {
    std::vector<ll> ans(points.size());
    for (int i = 0; i < points.size(); ++i) {
        auto realXvalue = std::upper_bound(xUnique.begin(), xUnique.end(), points[i].x);
        auto realYvalue = std::upper_bound(yUnique.begin(), yUnique.end(), points[i].y);
        if (realXvalue == xUnique.end() || realXvalue == xUnique.begin() || realYvalue == yUnique.begin() || realYvalue == yUnique.end()) {
            ans[i] = 0;
        }
        else {
            ans[i] = map[realYvalue - yUnique.begin() - 1][realXvalue - xUnique.begin() - 1];
        }
    }
    return ans;
}

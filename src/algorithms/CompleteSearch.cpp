#include "../../include/algorithms/CompleteSearch.hpp"

void CompleteSearch::preprocessing(const std::vector<Rectangle>& rectangles) {
    this->rectangles = rectangles;
}

std::vector<ll> CompleteSearch::countAns(std::vector<Point> points) {
    std::vector<ll> ans(points.size());
    for (int i = 0; i < points.size(); i++) {
        ll curCount = 0;
        for (const auto& rect: rectangles) {
            if (rect.low_left.x <= points[i].x && rect.low_left.y <= points[i].y && rect.top_right.x > points[i].x && rect.top_right.y > points[i].y) {
                curCount++;
            }
        }
        ans[i] = curCount;
    }
    return ans;
}

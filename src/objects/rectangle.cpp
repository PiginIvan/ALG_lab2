#include "../../include/objects/rectangle.hpp"

Rectangle::Rectangle() : low_left(0, 0), top_right(0, 0) {}

Rectangle::Rectangle(Point p1, Point p2) : low_left(p1), top_right(p2) {}

Rectangle::Rectangle(int x1, int y1, int x2, int y2) : low_left(x1, y1), top_right(x2, y2) {}

Rectangle::Rectangle(Rectangle& other) : low_left(other.low_left), top_right(other.top_right) {}

Rectangle::Rectangle(Rectangle const& other) : low_left(other.low_left), top_right(other.top_right) {}

std::istream& operator>>(std::istream& in, Rectangle& other) { return in >> other.low_left >> other.top_right; }

std::vector<Rectangle> getAllRectangles(int n) {
    std::vector<Rectangle> rectangles(n);
    for (auto& r: rectangles) std::cin >> r;
    return rectangles;
}
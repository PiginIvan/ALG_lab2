#include "../../include/objects/point.hpp"

Point::Point() : x(0), y(0) {}

Point::Point(int x_coord, int y_coord) : x(x_coord), y(y_coord) {}

Point::Point(Point& other) : Point(other.x, other.y) {}

Point::Point(Point const& other) : Point(other.x, other.y) {}

std::istream& operator>>(std::istream& in, Point& other) { return in >> other.x >> other.y; }

std::vector<Point> getAllPoints(int n) {
    std::vector<Point> points(n);
    for (auto& p: points) std::cin >> p;
    return points;
}

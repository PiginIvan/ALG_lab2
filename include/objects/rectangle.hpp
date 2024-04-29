#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "point.hpp"

class Rectangle {
public:
    Point low_left, top_right;

    Rectangle();
    Rectangle(Point p1, Point p2);
    Rectangle(int x1, int y1, int x2, int y2);
    Rectangle(Rectangle& other);
    Rectangle(Rectangle const& other);

};

std::istream& operator>>(std::istream& in, Rectangle& other);
std::vector<Rectangle> getAllRectangles(int n);

#endif
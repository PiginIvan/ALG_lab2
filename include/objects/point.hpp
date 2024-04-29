#ifndef POINT_HPP
#define POINT_HPP
#include <iostream>
#include <vector>

class Point {
public:
    int x, y;

    Point();
    Point(int x_coord, int y_coord);
    Point(Point& other);
    Point(Point const& other);

};

std::istream& operator>>(std::istream &in, Point &p);
std::vector<Point> getAllPoints(int n);

#endif
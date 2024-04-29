#ifndef DATAGENERATORS_HPP
#define DATAGENERATORS_HPP
#include <vector>
#include "objects/rectangle.hpp"

#define ll long long
#define X_PRIME 167
#define Y_PRIME 181 

ll fastPow(ll num, ll pow, ll mod);
std::vector<Rectangle> generateAllRectangles(int n);
std::vector<Point> generateAllPoints(int m);

#endif
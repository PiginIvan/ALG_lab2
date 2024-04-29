#ifndef COMPLETESEARCH_HPP
#define COMPLETESEARCH_HPP
#include <vector>
#include "../objects/rectangle.hpp"

#define ll long long

class CompleteSearch {
private:
    std::vector<Rectangle> rectangles;

public:
    void preprocessing(const std::vector<Rectangle>& rectangles);
    std::vector<ll> countAns(std::vector<Point> points);

};


#endif
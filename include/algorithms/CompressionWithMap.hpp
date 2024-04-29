#ifndef COMPRESSIONWITHMAP_HPP
#define COMPRESSIONWITHMAP_HPP
#include <vector>
#include "../objects/rectangle.hpp"

#define ll long long

class MapSearch {
private:
    std::vector<std::vector<ll>> map;
    std::vector<int> xUnique, yUnique;

    Point compressPoint(const Point& p);
    void fillMap(const std::vector<Rectangle>& rectangles);
    void selectUniqueCoords(const std::vector<Rectangle>& rectangles);

public:
    void preprocessing(const std::vector<Rectangle>& rectangles);
    std::vector<ll> countAns(std::vector<Point> points);

};


#endif
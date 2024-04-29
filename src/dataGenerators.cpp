#include "../include/dataGenerators.hpp"
#include <fstream>

ll fastPow(ll num, ll pow, ll mod) {
    if(mod == 1) return 0;
	ll ans = 1;
	while (pow > 0) {
		if ((pow & 1) == 1) {
			ans = (ans * num) % mod;
		}
		pow = pow / 2;
		num = (num * num) % mod;
	}
	return ans;
}

std::vector<Rectangle> generateAllRectangles(int n) {
    std::ofstream out("resources/rectangles.txt", std::ios::app);
    out << n << "\n";
    std::vector<Rectangle> rectangles(n);
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        x1 = 10 * i;
        y1 = 10 * i;
        x2 = 10 * (2 * n - i);
        y2 = 10 * (2 * n - i);
        rectangles[i] = Rectangle({x1, y1}, {x2, y2});
        out << x1 << " " << y1 << " " << x2 << " " << y2 << "\n";
    }
    out.close();
    return rectangles;
}

std::vector<Point> generateAllPoints(int m) {
    std::ofstream out("resources/points.txt", std::ios::app);
    out << m << "\n";
    std::vector<Point> points(m);
    for (int i = 0; i < m; i++) {
        int x, y;
        x = static_cast<int>(fastPow(X_PRIME * i, 31, 20 * m));
        y = static_cast<int>(fastPow(Y_PRIME * i, 31, 20 * m));
        points[i] = Point(x, y);
        out << x << " " << y << "\n";
    }
    return points;
}
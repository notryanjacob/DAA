#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Point structure
struct Point {
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}

    // Comparator for sorting points based on polar angle
    static int polarOrder(const Point& p1, const Point& p2, const Point& p0) {
        int dx1 = p1.x - p0.x;
        int dy1 = p1.y - p0.y;
        int dx2 = p2.x - p0.x;
        int dy2 = p2.y - p0.y;
        int cross = dx1 * dy2 - dy1 * dx2;
        if (cross == 0) {
            return (dx1 * dx1 + dy1 * dy1) < (dx2 * dx2 + dy2 * dy2) ? -1 : 1;
        }
        return cross > 0 ? -1 : 1;
    }
};

// Find the convex hull using Jarvis March algorithm
vector<Point> jarvisMarch(vector<Point>& points) {
    int n = points.size();
    if (n < 3) {
        return points;
    }

    // Find the leftmost point
    int leftmost = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].x < points[leftmost].x || (points[i].x == points[leftmost].x && points[i].y < points[leftmost].y)) {
            leftmost = i;
        }
    }

    int p = leftmost;
    vector<Point> hull;
    do {
        hull.push_back(points[p]);
        int q = (p + 1) % n;
        for (int i = 0; i < n; i++) {
            if (Point::polarOrder(points[i], points[q], points[p]) < 0) {
                q = i;
            }
        }
        p = q;
    } while (p != leftmost);

    return hull;
}

int main() {
    vector<Point> points = {{0, 3}, {2, 2}, {1, 1}, {2, 1}, {3, 0}, {0, 0}, {3, 3}};
    vector<Point> hull = jarvisMarch(points);

    cout << "Convex Hull:" << endl;
    for (const Point& p : hull) {
        cout << "(" << p.x << ", " << p.y << ")" << endl;
    }

    return 0;
}
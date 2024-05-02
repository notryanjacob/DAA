#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Point structure
struct Point {
    int x, y;

    Point(int _x, int _y) : x(_x), y(_y) {}
};

// Comparator for sorting points based on polar angle
bool polarOrder(const Point& p1, const Point& p2, const Point& p0) {
    int dx1 = p1.x - p0.x;
    int dy1 = p1.y - p0.y;
    int dx2 = p2.x - p0.x;
    int dy2 = p2.y - p0.y;

    int cross = dx1 * dy2 - dy1 * dx2;
    if (cross == 0) {
        return (dx1 * dx1 + dy1 * dy1) < (dx2 * dx2 + dy2 * dy2);
    }

    return cross > 0;
}

// Find the convex hull using Graham Scan algorithm
vector<Point> grahamScan(vector<Point>& points) {
    int n = points.size();
    if (n < 3) {
        return points;
    }

    // Find the point with the minimum y-coordinate (leftmost)
    int minY = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].y < points[minY].y || (points[i].y == points[minY].y && points[i].x < points[minY].x)) {
            minY = i;
        }
    }

    // Swap the leftmost point to the beginning
    swap(points[0], points[minY]);

    // Sort the remaining points based on polar angle
    sort(points.begin() + 1, points.end(), [&](const Point& p1, const Point& p2) {
        return polarOrder(p1, p2, points[0]);
    });

    vector<Point> hull;
    hull.push_back(points[0]);
    hull.push_back(points[1]);

    for (int i = 2; i < n; i++) {
        while (hull.size() > 1 && !polarOrder(hull[hull.size() - 2], hull.back(), points[i])) {
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }

    return hull;
}

int main() {
    vector<Point> points = {{0, 3}, {2, 2}, {1, 1}, {2, 1}, {3, 0}, {0, 0}, {3, 3}};

    vector<Point> hull = grahamScan(points);

    cout << "Convex Hull:" << endl;
    for (const Point& p : hull) {
        cout << "(" << p.x << ", " << p.y << ")" << endl;
    }

    return 0;
}

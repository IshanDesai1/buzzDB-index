#include "common.h"
int main() {
    RTree index;
    auto points = getRandomData();

    // Insert points into index
    for (const Point& point : points) {
        index.insert(point);
    }

    const int pointID = 66;
    Point queryPoint = points[pointID];

    // Find the nearest neighbors
    int k = 3;
    std::vector<Point> nearestNeighbors = index.nearestNeighbor(queryPoint, k);

    std::cout << "The " << k << " nearest neighbors to (" << queryPoint.label << "):" << std::endl;
    printPoint(queryPoint);
    for (const Point& p : nearestNeighbors) {
        printPoint(p);
    }

    return 0;
}
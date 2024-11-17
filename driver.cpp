#include "common.h"
int main() {
    MultiHashLSHIndex index;
    auto points = getRandomData();
    auto start_time = std::chrono::system_clock::now();

    for (const Point& point : points) {
        index.insert(point);
    }
    auto index_build_time = std::chrono::system_clock::now();
    const int pointID = 66;
    Point queryPoint = points[pointID];

    int k = 3;
    std::vector<Point> nearestNeighbors = index.nearestNeighbor(queryPoint, k);
    auto query_completion_time = std::chrono::system_clock::now();

    std::cout << "The " << k << " nearest neighbors to (" << queryPoint.label << "):" << std::endl;
    printPoint(queryPoint);
    for (const Point& p : nearestNeighbors) {
        printPoint(p);
    }
    auto total_time = std::chrono::duration_cast<std::chrono::microseconds>(query_completion_time - start_time);
    auto index_time = std::chrono::duration_cast<std::chrono::microseconds>(index_build_time - start_time);
    auto query_time = std::chrono::duration_cast<std::chrono::microseconds>(query_completion_time - index_build_time);
    std::cout << "index: " << index.get_name() 
        << " data dimensionality: " << POINT_COORDINATES 
        << " num points: " << NUM_POINTS 
        << " total time: " << total_time.count() << " microseconds"
        << " index time: " << index_time.count() << " microseconds"
        << " search time: " << query_time.count() << " microseconds"
        << std::endl;
    return 0;
}
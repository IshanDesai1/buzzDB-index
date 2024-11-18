#include "common.h"
int main() {
    FlatIndex index;
    auto points = getClusteredData();
    auto start_time = std::chrono::system_clock::now();

    for (const Point& point : points) {
        index.insert(point);
    }
    auto index_build_time = std::chrono::system_clock::now();
    std::mt19937 gen(42);
    std::uniform_int_distribution<> dis(1,100000);
    const int pointID = dis(gen);
    Point queryPoint = points[pointID];

    int k = 5;
    std::vector<Point> nearestNeighbors = index.nearestNeighbor(queryPoint, k);
    auto query_completion_time = std::chrono::system_clock::now();

    std::cout << "The " << k << " nearest neighbors to (" << queryPoint.label << "):" << std::endl;
    printPoint(queryPoint);
    for (const Point& p : nearestNeighbors) {
        printPoint(p);
    }
    auto total_time = std::chrono::duration_cast<std::chrono::milliseconds>(query_completion_time - start_time);
    auto index_time = std::chrono::duration_cast<std::chrono::milliseconds>(index_build_time - start_time);
    auto query_time = std::chrono::duration_cast<std::chrono::milliseconds>(query_completion_time - index_build_time);
    std::cout << "index: " << index.get_name() 
        << " data dimensionality: " << POINT_COORDINATES 
        << " num points: " << NUM_POINTS 
        << " total time: " << total_time.count() << " milliseconds"
        << " index time: " << index_time.count() << " milliseconds"
        << " search time: " << query_time.count() << " milliseconds"
        << std::endl;
    return 0;
}
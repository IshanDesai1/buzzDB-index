#ifndef FLATINDEX_H
#define FLATINDEX_H
#include "utils.h"
#include "point.h"
#include <unordered_map>
#include <queue>
class flatIndex {
    private:
    std::vector<Point> index;
    public:
    void insert(const Point& queryPoint) {
        index.emplace_back(queryPoint);
    }
    std::vector<Point> nearestNeighbor(const Point& queryPoint, unsigned long int k) {
        std::priority_queue<std::pair<double, Point>> pq;
        for (Point entry : index) {
            double distance = getEuclideanDistance(queryPoint, entry);
            pq.emplace(distance, entry);
            if (pq.size() > k) {
                pq.pop();
            }
        }
        std::vector<Point> closest_points;
        while (!pq.empty()) {
            Point p = pq.top().second;
            closest_points.emplace_back(p);
            pq.pop();
        }
        return closest_points;
    }
};

#endif
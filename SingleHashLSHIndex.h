#ifndef SINGLEHASHLSHINDEX_H
#define SINGLEHASHLSHINDEX_H
#include "utils.h"
#include <unordered_map>
#include <queue>
class SingleHashLSHIndex {
    private:
    std::unordered_map<int, std::vector<Point>> index;
    std::vector<float> unit_vector = getRandomUnitVector();
    int gamma;
    
    int hash(const Point& queryPoint) {
        return computeDotProduct(queryPoint.coordinates, unit_vector) / gamma;
    }
    
    public:
    SingleHashLSHIndex(int gamma = static_cast<int>(std::sqrt(NUM_POINTS))) : gamma(gamma) {}

    void insert(const Point& queryPoint) {
        int bucket = hash(queryPoint);
        index[bucket].emplace_back(queryPoint);
    }

    std::vector<Point> nearestNeighbor(const Point& queryPoint, unsigned long int k) {
        int bucket = hash(queryPoint);
        return getNearestNeighbors(queryPoint, index[bucket], k);
    }
    std::string get_name() {
        return "SingleHashLSHIndex";
    }
};

#endif
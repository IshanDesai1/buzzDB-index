#ifndef FLATINDEX_H
#define FLATINDEX_H
#include "utils.h"
#include "point.h"
class FlatIndex {
    private:
    std::vector<Point> index;
    
    public:
    void insert(const Point& queryPoint) {
        index.emplace_back(queryPoint);
    }
    std::vector<Point> nearestNeighbor(const Point& queryPoint, unsigned long int k) {
        return getNearestNeighbors(queryPoint, index, k);
    }
    std::string get_name() {
        return "FlatIndex";
    }
};

#endif
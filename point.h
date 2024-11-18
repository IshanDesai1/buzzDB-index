#ifndef POINT_H
#define POINT_H
#include <iostream>
#include <vector>
#include <limits>
#include <queue>


#define POINT_COORDINATES 4096

// Define a point in N-dimensional space
struct Point {
    std::vector<float> coordinates;
    std::string label;

    Point() {}
    Point(const std::vector<float>& coords) : coordinates(coords) {}

    Point(const std::vector<float>& coords, const std::string& lbl) : coordinates(coords), label(lbl) {}

    bool operator<(const Point& other) const {
        return coordinates < other.coordinates;
    }

    bool operator==(const Point& other) const {
        return coordinates == other.coordinates;
    }
};

inline void printPoint(const Point& p) {
    std::cout << p.label << " (";
    size_t numCoordinates = p.coordinates.size();
    for (size_t i = 0; i < std::min(numCoordinates, size_t(10)); ++i) {
        std::cout << p.coordinates[i];
        if (i < std::min(numCoordinates, size_t(10)) - 1) {
            std::cout << ", ";
        }
    }
    if (numCoordinates > 10) {
        std::cout << ", ...";
    }
    std::cout << ")\n";
}


#endif
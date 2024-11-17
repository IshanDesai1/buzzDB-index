#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <random>
#include <unordered_map>
#include <queue>
#include "point.h"

#define MAX_VALUE 100
#define NUM_POINTS 100
#define VARIANCE 10

std::vector<Point> getClusteredData(int num_clusters = static_cast<int>(std::sqrt(NUM_POINTS)), int num_points = static_cast<int>(std::sqrt(NUM_POINTS))) {
    std::mt19937 gen(42);  // Fixed seed for reproducibility
    std::uniform_real_distribution<float> dis(0.0, 1.0);

    std::vector<Point> points;
    for (int cluster = 0; cluster < num_clusters; ++cluster) {
        std::vector<float> center(POINT_COORDINATES);
        for (float &val : center) {
            val = dis(gen) * MAX_VALUE;  // Center of the cluster
        }

        for (int i = 0; i < num_points; ++i) {
            std::vector<float> coordinates(POINT_COORDINATES);
            for (int j = 0; j < POINT_COORDINATES; ++j) {
                coordinates[j] = center[j] + dis(gen) * (MAX_VALUE / VARIANCE);  // Points around the center
            }
            points.emplace_back(
                coordinates, 
                "Point_" + std::to_string(cluster * 10 + i)
            );
        }
    }
    return points;
}

std::vector<Point> getRandomData(int num_points = NUM_POINTS) {
    std::mt19937 gen(42);  // Fixed seed for reproducibility
    std::uniform_real_distribution<float> dis(0.0, 1.0);
    std::vector<Point> points;
        
    for (int i = 0; i < num_points; ++i) {
        std::vector<float> coordinates(POINT_COORDINATES);
        for (int j = 0; j < POINT_COORDINATES; ++j) {
            coordinates[j] = dis(gen) * MAX_VALUE;  // random points
        }
        points.emplace_back(
            coordinates, 
            "Point_" + std::to_string(i)
        );
    }
    return points;
}

std::vector<float> getRandomUnitVector() {
    std::random_device rd;  
    std::default_random_engine gen(rd()); 

    std::uniform_real_distribution<float> dis(0.0, 1.0);
    std::vector<float> random_vector(POINT_COORDINATES);
    for (int i = 0; i < POINT_COORDINATES; i++) {
        random_vector[i] = dis(gen);
    }
    double norm = 0.0;
    for (int i = 0; i < POINT_COORDINATES; i++) {
        norm += random_vector[i] * random_vector[i];
    }
    norm = std::sqrt(norm);
    for (int i = 0; i < POINT_COORDINATES; i++) {
        random_vector[i] /= norm;
    }
    return random_vector;
}


float computeDotProduct(std::vector<float> v1, std::vector<float> v2) {
    float dot_product = 0.0;
    for (long unsigned int i = 0; i < v1.size(); i++) {
        dot_product += (v1[i]*v2[i]);
    }
    return dot_product;
}

float getEuclideanDistance(Point v1, Point v2) {
    float total = 0.0;
    for (long unsigned int i = 0; i < v1.coordinates.size(); i++) {
        total += std::pow(v1.coordinates[i] - v2.coordinates[i], 2);
    }
    return std::sqrt(total);
}
std::vector<Point> getNearestNeighbors(const Point& queryPoint, std::vector<Point> neighbors, unsigned long int k) {
    std::priority_queue<std::pair<double, Point>> pq;
    for (Point entry : neighbors) {
        double distance = getEuclideanDistance(queryPoint, entry);
        pq.emplace(std::make_pair(distance, entry));
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
#endif
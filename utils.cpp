#include "point.h"
std::vector<Point> getClusteredData(int num_clusters, int num_points) {
    std::mt19937 gen(42);  // Fixed seed for reproducibility
    std::uniform_real_distribution<float> dis(0.0, 1.0);

    std::vector<Point> points;
    for (int cluster = 0; cluster < num_clusters; ++cluster) {
        std::vector<float> center(POINT_COORDINATES);
        for (float &val : center) {
            val = dis(gen) * 100;  // Center of the cluster
        }

        for (int i = 0; i < num_points; ++i) {
            std::vector<float> coordinates(POINT_COORDINATES);
            for (int j = 0; j < POINT_COORDINATES; ++j) {
                coordinates[j] = center[j] + dis(gen) * 10;  // Points around the center
            }
            points.emplace_back(
                coordinates, 
                "Point_" + std::to_string(cluster * 10 + i)
            );
        }
    }
    return points;
}

std::vector<Point> getRandomData(int num_points) {
    std::mt19937 gen(42);  // Fixed seed for reproducibility
    std::uniform_real_distribution<float> dis(0.0, 1.0);
    std::vector<Point> points;
        
    for (int i = 0; i < num_points; ++i) {
        std::vector<float> coordinates(POINT_COORDINATES);
        for (int j = 0; j < POINT_COORDINATES; ++j) {
            coordinates[j] = dis(gen) * 100;  // random points
        }
        points.emplace_back(
            coordinates, 
            "Point_" + std::to_string(i)
        );
    }
    return points;
}

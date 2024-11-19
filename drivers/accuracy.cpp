#include "../common.h"

int main() {
    FlatIndex ground_truth_index;
    SingleHashLSHIndex other_index;
    
    auto points = getClusteredData();
    
    for (const Point& point : points) {
        ground_truth_index.insert(point);
        other_index.insert(point);
    }

    std::mt19937 gen(42);
    std::uniform_int_distribution<> dis(1, NUM_POINTS);
    int num_query_points = 20;
    int num_nearest_neighbors = 10;
    std::vector<Point> query_points(num_query_points);
    
    for (int i = 0; i < num_query_points; i++) {
        const int pointID = dis(gen);
        query_points[i] = points[pointID];
    }

    int total_comparison_points = num_nearest_neighbors * num_query_points;
    int total_hits = 0;
    for (const auto& point : query_points) {
        auto truth = ground_truth_index.nearestNeighbor(point, num_nearest_neighbors);
        auto comp = other_index.nearestNeighbor(point, num_nearest_neighbors);
        for (int i = 0; i < num_nearest_neighbors; i++) {
            total_hits += truth[i] == comp[i] ? 1 : 0;
        }
    }
    std::cout << "accuracy test for index: " << other_index.get_name() 
        << " data dimensionality: " << POINT_COORDINATES 
        << " num points: " << NUM_POINTS 
        << " accuracy: " << std::fixed << std::setprecision(2) << static_cast<float>(total_hits / total_comparison_points)
        << std::endl;
    return 0;
}
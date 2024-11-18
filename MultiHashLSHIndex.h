#ifndef MULTIHASHLSHINDEX_H
#define MULTIHASHLSHINDEX_H
#include "utils.h"

class MultiHashLSHIndex {
    private:
    std::unordered_map<std::string, std::vector<Point>> index;
    std::vector<std::vector<float>> unit_vectors;
    int gamma;
    int num_hashes;
    std::string get_bucket(const Point& queryPoint) {
        auto hashes = hash(queryPoint);
        auto bucket = concatenate(hashes);
        return bucket;
    }
    std::vector<int> hash(const Point& queryPoint) {
        std::vector<int> hashes;
        for (int i = 0; i < num_hashes; i++) {
            hashes.emplace_back(static_cast<int>(computeDotProduct(queryPoint.coordinates, unit_vectors[i]) / gamma));
        }
        return hashes;
    }
    std::string concatenate(std::vector<int> hashes) {
        std::string bucket = "";
        for (int i = 0; i < num_hashes; i++) {
            bucket += std::to_string(hashes[i]) + "-";
        }
        return bucket;
    }
    public:
    MultiHashLSHIndex(int gamma = static_cast<int>(std::sqrt(NUM_POINTS)), int num_hashes = 5) : gamma(gamma), num_hashes(num_hashes) {
        for (int i = 0; i < num_hashes; i++) {
            unit_vectors.emplace_back(getRandomUnitVector());
        }
    }
    void insert(const Point& queryPoint) {
        index[get_bucket(queryPoint)].emplace_back(queryPoint);
    }
    std::vector<Point> nearestNeighbor(const Point& queryPoint, unsigned long int k) {
        std::string bucket = get_bucket(queryPoint);
        return getNearestNeighbors(queryPoint, index[bucket], k);
    }
    std::string get_name() {
        return "MultiHashLSHIndex";
    }
};

#endif
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>


int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.precision(20);
    int64_t n;
    int64_t k;
    int64_t p;
    std::cin >> n >> k >> p;
    std::unordered_map<uint32_t, uint32_t> floor;
    std::map<int64_t, int64_t> floor_idx;
    uint32_t max_idx = p;
    std::vector<std::pair<int64_t , int64_t>> toys(p);
    std::vector<int64_t> tmp(n + 1, -1);
    int64_t operations = 0;
    for (int64_t i = 0; i < p; ++i) {
        uint32_t num;
        std::cin >> num;
        toys[i] = {num, 0};
    }
    for (int64_t j = p - 1; j >= 0; --j) {
        int64_t next_idx = tmp[toys[j].first];
        toys[j].second = (next_idx != -1) ? next_idx : (++max_idx);
        tmp[toys[j].first] = j;
    }
    int64_t i = 0;
    while (i < p) {
        // toy on the floor
        if (floor.find(toys[i].first) != floor.end()) {
            int64_t pos = floor[toys[i].first];
            floor_idx.erase(pos);
            //swap toy in the floor
        } else if (floor.size() == k) {
            operations++;
//            int64_t test =  floor_idx.rbegin()->first;
            auto erase_pair = floor_idx.extract(floor_idx.rbegin()->first);
            floor.erase(erase_pair.mapped());
            // toys on the floor fewer than max_floor_value
        } else {
            operations++;
        }
        floor[toys[i].first] = toys[i].second;
        floor_idx[toys[i].second] = toys[i].first;
        i++;
    }
    std::cout << operations;
}


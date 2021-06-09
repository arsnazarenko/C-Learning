#include <iostream>
#include <vector>
#include <set>

using u16 = int64_t;
struct row_comp {
public:
    bool operator() (std::pair<u16, u16> const& a, std::pair<u16, u16> const& b ) const {
        return a.second < b.second;
    }
};
struct col_comp {
public:
    bool operator() (std::pair<u16, u16> const& a, std::pair<u16, u16> const& b ) const {
        return a.first < b.first;
    }
};

int main() {
    u16 m, n, k;
    std::cin >> m >> n >> k;
    u16 result = 0;
    std::vector<std::set<std::pair<u16, u16>, row_comp>> rows(m + 1);
    std::vector<std::set<std::pair<u16, u16>, col_comp>> cols(n + 1);
    std::set<std::pair<u16, u16>> unit_segments;
    for (u16 i = 1; i <= m; ++i) {
        rows[i].insert({i, 0});
        rows[i].insert({i, n + 1});
    }
    for(u16 i = 1; i <= n; ++i ) {
        cols[i].insert({0, i});
        cols[i].insert({m + 1, i});
    }

    for (u16 i = 0; i < k; ++i) {
        u16 x, y;
        std::cin >> x >> y;
        rows[x].insert({x, y});
        cols[y].insert({x, y});
    }
    for (u16 i = 1; i <= m; ++i) {
        for (auto it1 = rows[i].begin(), it2 = (++rows[i].begin()); it2 != rows[i].end(); ++it1, ++it2) {
            if (it2->second - it1->second >= 2) {
                if (it2->second - it1->second == 2) {
                    unit_segments.insert({it1->first, it2->second - 1});
                } else {
                    result++;
                }
            }
        }
    }
    for (u16 i = 1; i <= n; ++i) {
        for (auto it1 = cols[i].begin(), it2 = (++cols[i].begin()); it2 != cols[i].end(); ++it1, ++it2) {
            if (it2->first - it1->first >= 2) {
                if (it2->first - it1->first == 2) {
                    if (unit_segments.find({it2->first - 1, it2->second}) != unit_segments.end()) {
                        result++;
                    }
                } else {
                    result++;
                }
            }
        }
    }
    std::cout << result;
    return 0;
}
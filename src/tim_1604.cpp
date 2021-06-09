#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int64_t types;
    std::cin >> types;
    std::vector<int64_t> signs_count(types);

    int64_t total = 0;
    for (size_t i = 0; i < types; ++i) {
        int64_t count;
        std::cin >> count;
        total+=count;
        signs_count[i] = count;
    }
    if (types == 1) {
        for (size_t i = 0; i < signs_count[0]; ++i) {
            std::cout << 1 << " ";
        }
    } else {
        std::vector<int64_t> signs_idx;
        for(size_t i = 0; i < signs_count.size(); signs_idx.push_back(i++));
        std::vector<int64_t> signs;
        std::vector<int64_t> result;
        std::stable_sort(signs_idx.begin(), signs_idx.end(),
                         [&signs_count](int64_t const& a, int64_t const& b) {
                             return signs_count[a] > signs_count[b];
                         });
        for (size_t j = 0; j < types; ++j) {
            for (size_t i = 0; i < signs_count[signs_idx[j]]; ++i) {
                signs.push_back(signs_idx[j] + 1);
            }
        }
        int64_t max_count_sign = signs_count[signs_idx[0]];
        if (max_count_sign > total - max_count_sign) {
            for (size_t i = 0; i < max_count_sign; ++i) {
                result.push_back(signs[i]);
                if (max_count_sign + i < signs.size()) {
                    result.push_back(signs[max_count_sign + i]);
                }
            }
        } else {
            for (size_t i = 0; i < max_count_sign; ++i) {
                size_t j = i;
                while (j < signs.size()) {
                    result.push_back(signs[j]);
                    j += max_count_sign;
                }
            }
        }
        for (int64_t const& s: result) {
            std::cout << s << " ";
        }
    }
    return 0;
}
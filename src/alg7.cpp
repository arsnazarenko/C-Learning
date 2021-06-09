#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int64_t> weights(26);
    std::string input;
    std::cin >> input;
    for (size_t i = 0; i < 26; ++i) {
        std::cin >> weights[i];
    }
    std::sort(input.begin(), input.end());
    std::stable_sort(input.begin(), input.end(), [&weights](char const &a, char const &b) {
        return weights[a - 97] < weights[b - 97];
    });
    std::vector<char> middle;
    std::vector<char> side_part;
    size_t i = 0;
    while (i < input.size()) {
        int64_t n = 1;
        size_t j = i;
        while (j < input.size() - 1 && input[j] == input[j + 1]) {
            n++;
            j++;
        }
        if (n > 1 && weights[input[j] - 97] != 0) {
            side_part.push_back(input[j]);
            for (size_t k = 0; k < n - 2; ++k) {
                middle.push_back(input[j]);
            }
        } else {
            for (size_t k = 0; k < n; ++k) {
                middle.push_back(input[j]);
            }
        }
        i = j + 1;
    }
    for (int64_t l = side_part.size() - 1; l >= 0; --l) {
        std::cout << side_part[l];
    }
    for (char const &a: middle) {
        std::cout << a;
    }
    for (char const &b: side_part) {
        std::cout << b;
    }
    return 0;
}
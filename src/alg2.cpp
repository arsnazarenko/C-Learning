#include <iostream>
#include <vector>
#include <string>
#include <stack>

int main() {
    int32_t animalCounter = 0;
    int32_t trapCounter = 0;
    std::string input;
    std::cin >> input;
    std::stack<std::pair<char, size_t>> pairs_stack;
    std::vector<size_t> res(input.length() / 2);
    for (char const& symbol : input) {
        const bool is_animal = islower(symbol);
        const size_t pos = is_animal ? ++animalCounter : ++trapCounter;
        if (!pairs_stack.empty()) {
            const char compare_char = islower(symbol) ? static_cast<char>(toupper(symbol)) : static_cast<char>(tolower(symbol));
            std::pair<char, size_t> const &top = pairs_stack.top();
            if (top.first == compare_char) {
                res[is_animal ? top.second - 1 : pos - 1] = is_animal ? pos : top.second;
                pairs_stack.pop();
            } else {
                pairs_stack.push(std::make_pair(symbol, pos));
            }
        } else {
            pairs_stack.push(std::make_pair(symbol, pos));
        }
    }
    if (pairs_stack.empty()) {
        std::cout << "Possible" << std::endl;
        for(size_t const& el: res) {
            std::cout << el << " ";
        }
    } else {
        std::cout << "Impossible" << std::endl;
    }
}
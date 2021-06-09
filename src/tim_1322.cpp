#include <iostream>
#include <algorithm>

void decode(std::string const& input,  const uint32_t column_num) {
    std::vector<uint32_t> first_column;
    for (uint32_t i = 0; i < input.size(); first_column.push_back(i++));
    std::stable_sort(first_column.begin(), first_column.end(),
                     [&input](uint32_t const& a, uint32_t const& b) {
                         return input[a] < input[b];
                     });
    uint32_t first_column_idx = column_num - 1; //индекс символа в строке, с которого начнается исхожное слово.
    uint32_t i = 0;
    while (i < input.size()) {
        uint32_t idx =  first_column[first_column_idx];
        std::cout << input[idx];
        first_column_idx = idx;
        i++;
    }
}
int main() {
    uint32_t column_idx;
    std::string input;
    std::cin >> column_idx >> input;
    decode(input, column_idx);
}
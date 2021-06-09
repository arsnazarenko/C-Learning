#include <iostream>
#include <algorithm>

struct encode_msg {
public:
    std::string word;
    uint32_t idx;
};


void test_bwt_decoder();

encode_msg encode(std::string const& input) {
    std::vector<std::string> table;
    uint32_t i = 0;
    while (i < input.size()) {
        std::string result;
        uint32_t k = i;
        while (k < i + input.size()){
            result += input[k % input.length()];
            k++;
        }
        table.push_back(result);
        i++;
    }
    uint32_t column_number = 0;
    std::string last_column;
    std::stable_sort(table.begin(), table.end());
    for (uint32_t k = 0; k < input.size(); ++k) {
        if (table[k] == input) {
            column_number = k + 1;
        }
        last_column += table[k][input.size() - 1];
    }
    return encode_msg{.word = last_column, .idx = column_number};
}

void decode(std::string const& input,  const uint32_t column_num) {
    std::vector<uint32_t> first_column;
    for (uint32_t i = 0; i < input.size(); first_column.push_back(i++));
    std::stable_sort(first_column.begin(), first_column.end(),
                     [&input](uint32_t const& a, uint32_t const& b) {
                         retcurn input[a] < input[b];
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
    test_bwt_decoder();
    return 0;
}

void test_bwt_decoder() {
    std::string input;
    std::cin >> input;
    encode_msg msg = encode(input);
    std::cout << msg.word << " " << msg.idx << '\n';
    decode(msg.word, msg.idx);
}


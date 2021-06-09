#include <iostream>
#include <cstdint>

int main(int argc, char** argv) {
    uint32_t n;
    std::cin >> n;
    uint32_t retry_value = 0;
    uint32_t max_length = 0;
    uint32_t start = 1;
    uint32_t retry_counter = 1;
    uint32_t start_res = 1;
    for(uint32_t i = 1; i <= n; ++i) {
        uint32_t value;
        std::cin >> value;
        if (value == retry_value) {
            if (retry_counter == 2) {
                start = i - 1;
            } else {
                retry_counter++;
            }
        } else {
            retry_value = value;
            retry_counter = 1;
        }
        if (i - start + 1 > max_length) {
            max_length = i - start + 1;
            start_res = start;
        }
//        std::cout << "start: " << start << " ,i: " << i << "; retry value: " << retry_value
//        << " ,count: " << retry_counter << " ;start_max: " << start_res << std::endl;
    }
    std::cout << start_res << " " << start_res + max_length - 1;
    return 0;
}
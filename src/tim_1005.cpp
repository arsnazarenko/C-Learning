#include <iostream>
#include <vector>
//#include <bitset>
#include <algorithm>
#include <cmath>

int main () {
    int32_t size;
    std::cin >> size;

    std::vector<int32_t> stones(size);
    for(int64_t i = 0; i < size; ++i) {
        std::cin >> stones[i];
    }
    int32_t min_diff = INT32_MAX;
    // в маске числа от 0  до 2^(n-1), такое условие сразу делает крайний (n-1) бит нулем, а значит и крайний камень из последовательности всегда в heap0
    for (int32_t mask = 0; mask < (1 << (size - 1)); ++mask) {
//        std::cout << std::bitset<32>(mask) << std::endl;
        int64_t heap0 = 0; //  сумма кучи 1
        int64_t heap1 = 0; //  сумма кучи 2
        for (int32_t i = 0; i < size; ++i) {
            if (((mask >> i) & 1) == 1 ) {
                heap1 += stones[i];
            } else {
                heap0 += stones[i];
            }
        }
//        std::cout << "< " << heap0 << " , " << heap1 << ">\n";
        min_diff = std::min(static_cast<int64_t>(min_diff), std::abs(heap1 - heap0));
    }
    std::cout << min_diff;
    return 0;


}

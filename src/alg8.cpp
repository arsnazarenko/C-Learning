#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int64_t sum = 0;
    int32_t n, k;
    std::cin >> n >> k;
    std::vector<int32_t> prices(n);
    for (int32_t& pr : prices) {
        std::cin >> pr;
        sum += pr;
    }
    std::sort(prices.begin(), prices.end());
    int32_t i = n-k;
    while (i >= 0) {
        sum-=prices[i];
        i-=k;
    }
    std::cout << sum;
    return 0;
}
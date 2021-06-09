#include <iostream>
#include <vector>
#include <algorithm>

int64_t max_sub_sum(std::vector<int64_t>  const& arr) {
    int64_t total_max_sum = 0;
    int64_t current_sub_sum = 0;

    for(size_t i = 0; i < arr.size(); ++i) {
        current_sub_sum += arr[i];
        total_max_sum = std::max(total_max_sum, current_sub_sum);
        if (current_sub_sum < 0) {
            current_sub_sum = 0;
        }
    }
    return total_max_sum;
}


int64_t max_sub_dynamic() {

}



int main() {
    int64_t n;
    std::cin >> n;
    std::vector<int64_t> arr(n);
    for(int64_t i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    std::cout << max_sub_sum(arr);
    return 0;
}
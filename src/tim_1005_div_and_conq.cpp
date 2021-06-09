#include <iostream>
#include <vector>
#include <algorithm>

int64_t max_sum_at_partition(std::vector<int64_t> const& arr, int64_t l, int64_t m, int64_t r) {
    int64_t left_total = 0;
    int64_t right_total = 0;

    int64_t left_current = 0;
    int64_t right_current = 0;

    //left of the middle
    for (int64_t i = m; i >= l; i--) {
        left_current += arr[i];
        left_total = std::max(left_total, left_current);
    }

    //left of the middle
    for (int64_t i = m+1; i <= r; ++i) {
        right_current += arr[i];
        right_total = std::max(right_total, right_current);
    }

    return right_total + left_total;
}

int64_t max_sum_subarray(std::vector<int64_t> const& arr, int64_t l, int64_t r) {
    //  если подмассив содержит элеменет 1 - возвращаем в качестве суммы подмассива этот самый элемент
    //  в случае, если он отрицателен, вернем 0
    if (l == r) {
        int64_t max_sum = arr[l];
        return max_sum < 0 ? 0 : max_sum;
    }
    int64_t m = (r + l) / 2; // находим середину
    //находим подпоследовательность с максимальной суммой, которая лежит на точке раздела
    int64_t max_sum_middle = max_sum_at_partition(arr, l, m, r);
    //подпоследовательность с максимальной суммой может лежать в трех местах:
    // в первой половине массива, во второй,
    return std::max(std::max(max_sum_subarray(arr, l, m), max_sum_subarray(arr, m + 1, r)), max_sum_middle);
}


int main () {
    size_t size;
    std::cin >> size;
    std::vector<int64_t> arr(size);
    for (size_t i = 0; i < size; ++i) {
        std::cin >> arr[i];
    }
    std::cout << max_sum_subarray(arr, 0, size - 1);
}
#include <iostream>
#include <vector>

bool can_put_cows(int32_t cows, const int64_t min_len_between, std::vector<int64_t> const& coords) {
    int64_t prev_coord = coords[0];
    int32_t cows_count = cows - 1;  //  первая уже в первом стойле
    size_t coord_size = coords.size();
    size_t idx = 1;
    while (idx < coord_size && cows_count > 0) {
        if (coords[idx] - prev_coord >= min_len_between) {
            prev_coord = coords[idx];
            cows_count--;
        }
        idx++;
    }
    if (cows_count == 0) {
        return true;
    }
    return false;
}




void cows() {
    int32_t n, k;
    std::cin >> n >> k;
    std::vector<int64_t> coord(n);
    for(int64_t& c : coord) {
        std::cin >> c;
    }
    int64_t left = 0;
    int64_t right = coord.back() - coord.front() + 1;
    while (right - left > 1) {
        int64_t mid = (left + right) / 2;
        if (can_put_cows(k, mid, coord)) {    //true - значит при расстоянии равном этому или больше коров можно разместить по стойлам
            left = mid;
            //  при таком минимальном расстоянии между коровами уже
            //  не получается уместить всех коров по стойлам, двигаем границу справа,
            //  причем это число уже не будет являться значением
        } else {
            right = mid;
        }
    }
    std::cout << left;
}


int main() {
    cows();
    return 0;
}
#include <iostream>
#include <set>
#include <list>
#include <vector>

void build(int32_t v, int32_t l, int32_t r, std::vector<std::pair<int32_t, int32_t>>& tree, int32_t& soldiers_counter) {
    if (l == r) {
        tree[v] = {1, soldiers_counter++};
        return;
    }
    int32_t m = (l + r) / 2;
    build(2 * v + 1, l , m, tree, soldiers_counter);
    build(2 * v + 2, m + 1 , r, tree, soldiers_counter);
    tree[v] = {tree[2 * v + 1].first + tree[2 * v + 2].first, -1};
}

int32_t delete_soldier(int32_t v, int32_t l, int32_t r, std::vector<std::pair<int32_t, int32_t>>& tree, int32_t soldier_idx) {
    if (l == r) {
        tree[v].first--;
        return tree[v].second;
    }
    tree[v].first--;
    int32_t m = (l + r) / 2;
    int32_t max_segment_idx = tree[2 * v + 1].first - 1;
    if (max_segment_idx >= soldier_idx) {
        return delete_soldier(2 * v + 1, l, m, tree, soldier_idx);
    }
    return delete_soldier(2 * v + 2, m + 1, r, tree, (soldier_idx - max_segment_idx) - 1);
}

int32_t get_new_soldier_idx(int32_t old_idx, int32_t k, int32_t current_size) {
    return (old_idx + k - 1) % current_size;
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.precision(20);
    int32_t n;
    int32_t k;
    std::cin >> n >> k;
    std::vector<std::pair<int32_t, int32_t>> soldiers(4 * n);
    int32_t counter = 1;
    build(0, 0, n - 1, soldiers, counter);
    int32_t current_size = n;
    int32_t idx = k - 1;
    while (current_size > 0) {
        int32_t soldier_number = delete_soldier(0 , 0, n - 1, soldiers, idx);   // 3, 1, 5, 2, 4
        std::cout << soldier_number << " ";
        current_size--;     //4, 3, 2, 1, 0
        idx = current_size != 0 ? get_new_soldier_idx(idx, k, current_size) : -1;    //0, 2, 0, 0, -1
    }
    return 0;
}
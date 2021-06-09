#include <iostream>
#include <vector>
#include <algorithm>

void build(int64_t v, int64_t l, int64_t r, std::vector<int64_t>& tree, std::vector<int64_t>& a) {
    if (l == r) {
        std::cout << v << std::endl;
        tree[v] = a[l];
        return;
    }
    int64_t m = (l + r) / 2;
    build(2 * v + 1, l, m, tree, a);
    build(2 * v + 2, m + 1, r, tree, a);
    tree[v] = std::min(tree[2 * v + 1], tree[2 * v + 2]);
    std::cout << v << std::endl;
}


int64_t request_min(int64_t v, int64_t l, int64_t r, std::vector<int64_t>& tree, int64_t ql, int64_t qr) {
    if (ql > r || qr < l) {    //  промежутки запроса не входят в промежутки данной вершины
        return INT64_MAX;
    }
    if (l >= ql && r <= qr) {   //  если отрезок полностью входит в промежуток запроса
        return tree[v];
    }
    //  иначе рекурсивно проверяем листья дерева (детей)
    int64_t m = (l + r) / 2;
    return std::min(request_min(2 * v + 1, l, m, tree, ql, qr), request_min(2 * v + 2, m + 1, r, tree, ql, qr));
}


int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.precision(20);
    int64_t n;
    int32_t k;
    std::cin >> n >> k;
    std::vector<int64_t> a(n);
    for (int64_t& l: a) {
        std::cin >> l;
    }
    std::vector<int64_t> tree(4 * n);
    build(0, 0, n - 1, tree, a);
    int64_t ql = 0;
    int64_t qr = k - 1;
    while (ql < (n - k + 1)) {
        std::cout << request_min(0, 0, n - 1, tree, ql, qr) << " ";
        ql++;
        qr++;
    }
    return 0;
}
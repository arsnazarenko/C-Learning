#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>

const uint32_t inf = 1e9;

void dijkstra_queue(const uint16_t n, const uint16_t s, const uint16_t f, const std::vector<std::vector<std::pair<uint16_t, uint64_t>>> &graph) {
    std::vector<uint64_t> distance(n, inf);
    std::vector<int32_t> pr(n, -1);
    distance[s] = 0;
    std::priority_queue<std::pair<int64_t, uint16_t>> q;
    q.emplace(0, s);
    while (!q.empty()) {
        int64_t len = -(q.top().first);
        uint16_t v = q.top().second;
        q.pop();
        //  в очереди мгут быть фиктивные вершины из-за отсутствия операции обновления ключа,
        //  поэтому требуется проверка
        if (len > distance[v]) continue;
        if (v == f) break;
        for (auto& i : graph[v]) {
            uint16_t to = i.first;
            uint64_t length = i.second;
            if (distance[to] > distance[v] + length) {
                distance[to] = distance[v] + length;
                pr[to] = v;
                q.push(std::make_pair(-(distance[to]), to));
            }
        }
    }
    if (distance[f] == inf) {
        std::cout << "-1";
    } else {
        std::cout << distance[f] << "\n";
        std::vector<uint16_t> path;
        int32_t cur = f;
        path.push_back(f);
        while (pr[cur] != -1) {
            cur = pr[cur];
            path.push_back(cur);
        }
        std::reverse(path.begin(), path.end());
        std::cout << path.size() << "\n";
        for (int64_t v: path) {
            std::cout << v + 1 << " ";
        }
    }
}


void to_graph(const uint64_t a, const uint16_t u,
                  std::unordered_map<uint64_t,uint16_t>& nums,
                  std::vector<uint16_t> const& times,
                  std::vector<std::vector<std::pair<uint16_t, uint64_t>>>& g) {
    uint16_t idx = 0;
    for (uint64_t i = 1000000000; i >= 1; i /= 10) {
        uint64_t deleted = (a - (a - (a % i)) % (i * 10));
        uint64_t tmp = i;
        for (int j = 0; j < 10; ++j) {
            uint64_t req = (tmp * j) + deleted;
            if (nums.find(req) != nums.end()) {
                uint16_t v = nums[req];
                uint16_t w = times[idx];
                g[v].emplace_back(u, w);
                g[u].emplace_back(v, w);
            }
        }
        idx++;
    }
    idx = 0;
    for (uint64_t i = 1000000000; i >= 10; i /= 10) {
        for (uint64_t j = i / 10; j >= 1; j /= 10) {
            uint64_t deleted = (a - (a % i)) % (i * 10);
            uint64_t deleted2 = (a - (a % j)) % (j * 10);
            uint64_t tmp = (a - deleted2 - deleted);
            uint64_t added = (deleted / i) * j;
            uint64_t added2 = (deleted2 / j) * i;
            uint64_t req = (tmp + added2 + added);
            if (nums.find(req) != nums.end()) {
                uint16_t v = nums[req];
                uint16_t w = times[idx];
                g[v].emplace_back(u, w);
                g[u].emplace_back(v, w);
            }
        }
        idx++;
    }
}


int main() {

    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    uint16_t n;
    std::cin >> n;
    std::vector<uint16_t> times(10);
    std::unordered_map<uint64_t, uint16_t> nums;
    std::vector<std::vector<std::pair<uint16_t, uint64_t>>> g(n);
    for (uint16_t i = 0; i < 10; ++i) {
        std::cin >> times[i];
    }
    uint64_t num;
    std::cin >> num;
    nums[num] = 0;
    for (uint16_t i = 1; i < n; ++i) {
        std::cin >> num;
        to_graph(num, i, nums, times, g);
        nums[num] = i;
    }
    dijkstra_queue(n, 0, n-1, g);
    return 0;
}
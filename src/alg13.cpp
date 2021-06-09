#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

int32_t get_distance(int32_t x, int32_t y, std::vector<std::vector<char>> const& map) {
    if (y < 0 || y > map.size() - 1 || x < 0 || x > (map[0].size() - 1) || map[y][x] == '#') return -1;
    else if (map[y][x] == 'W') return 2;
    else return 1;
}
//  влево
std::pair<int32_t, int32_t> on_west(int32_t x, int32_t y) {
    return {x - 1, y};
}
// вверх
std::pair<int32_t, int32_t> on_north(int32_t x, int32_t y) {
    return {x, y - 1};
}
//  вправо
std::pair<int32_t, int32_t> on_east(int32_t x, int32_t y) {
    return {x + 1, y};

}
// вниз
std::pair<int32_t, int32_t> on_south(int32_t x, int32_t y) {
    return {x, y + 1};
}

typedef std::pair<int32_t, int32_t> (*move_fn)(int32_t, int32_t);
move_fn fn[4] = {on_west, on_north, on_east, on_south};

const int32_t inf = 1e9;
struct node {
    int32_t x;
    int32_t y;
    int32_t dist;
    node(int32_t x, int32_t y, int32_t dist) : x(x), y(y), dist(dist) {}
    friend bool operator < (node const& a, node const& b) {
        return a.dist > b.dist;
    }
};

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.precision(20);
    size_t n;
    size_t m;
    int32_t x_start;
    int32_t y_start;
    int32_t x_fin;
    int32_t y_fin;
    std::cin >> n >> m >> y_start >> x_start >> y_fin >> x_fin;
    x_start--;
    y_start--;
    x_fin--;
    y_fin--;
    std::vector<std::vector<char>> map(n);
    std::vector<std::vector<int32_t>> distance(n, std::vector<int32_t>(m, inf));
    std::vector<std::vector<int32_t>> prev(n, std::vector<int32_t>(m, -1));
    for (auto& it : map) {
        std::string row;
        std::cin >> row;
        it = {row.data(), row.data() + row.size()};
    }
    std::priority_queue<node> q;
    std::vector<std::vector<std::pair<int32_t, int32_t>>> pr(n, std::vector<std::pair<int32_t, int32_t>>(m, {-1, -1}));
    q.emplace(x_start, y_start, 0);
    distance[y_start][x_start] = 0;
    while (!q.empty()) {
        node cur = q.top();
        q.pop();
        //  это фиктивное значение длины до вершины,
        //  из-за того, что из очереди мы не удаляем, поэтому нужно проверить
        if (cur.dist > distance[cur.y][cur.x]) continue;
        //  наименьший путь получен
        if (cur.x == x_fin && cur.y == y_fin) break;
        //  иначе это значение кратчайшего пути из источника до этой вершины
        for (move_fn f: fn) {
            //  координата соседней клетки
            const std::pair<int32_t, int32_t> coord = f(cur.x, cur.y);
            int32_t nx = coord.first;
            int32_t ny = coord.second;
            int32_t len = get_distance(nx, ny, map);
            //  проверяем, можем ли мы дойти до этой вершины
            if (len > 0) {
                //  обновляем значения путь для этой вершины, добавляем в очередь
                if (distance[ny][nx] > distance[cur.y][cur.x] + len) {
                    distance[ny][nx] = distance[cur.y][cur.x] + len;
                    pr[ny][nx] = {cur.x, cur.y};
                    q.emplace(nx, ny, distance[ny][nx]);
                }
            }
        }
    }
    if (distance[y_fin][x_fin] == inf) {
        std::cout << -1 << "\n";
    } else {
        std::cout << distance[y_fin][x_fin] << "\n";
        std::vector<std::pair<int32_t, int32_t>> path;
        std::pair<int32_t, int32_t> cur = {x_fin, y_fin};
        path.push_back(cur);
        while (pr[cur.second][cur.first].first != -1 || pr[cur.second][cur.first].second != -1) {
            cur = pr[cur.second][cur.first];
            path.push_back(cur);
        }
        std::reverse(path.begin(), path.end());
        for (int i = 0; i < path.size() - 1; ++i) {
            if (path[i + 1].first == path[i].first + 1) {
                std::cout << "E";
            } else if (path[i + 1].first == path[i].first - 1) {
                std::cout << "W";
            } else if (path[i + 1].second == path[i].second + 1) {
                std::cout << "S";
            } else {
                std::cout << "N";
            }
        }
    }
    return 0;
}
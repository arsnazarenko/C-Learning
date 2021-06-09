#include <iostream>
#include <vector>

void dfs(int32_t v, std::vector<std::vector<int32_t>> const &graph, std::vector<char> &color, int32_t& cycle_counter) {
    //  красим в серый при входе в вершину
    color[v] = 1;
    //  пробегаясь по каждой смежной вершине к текущей
    for (int32_t u: graph[v]) {
        if (color[u] == 1) {
            // если вершина серая => найден цикл
            cycle_counter++;
            //  иначе она белая, начинаем обход с нее
        } else if (color[u] == 0)   {
            dfs(u, graph, color, cycle_counter);
        }
    }
    //  все смежные вершины обработаны, красим в черный
    color[v] = 2;
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.precision(20);
    int32_t n;
    std::cin >> n;
    std::vector<std::vector<int32_t>> graph(n);
    std::vector<char> colors(n, 0);
    for (int32_t i = 0; i < n; ++i) {
        int32_t v;
        std::cin >> v;
        graph[v - 1].push_back(i);
    }
    int32_t counter = 0;
    for (int i = 0; i < n; ++i) {
        if (colors[i] == 0) {
            dfs(i, graph, colors, counter);
        }
    }
    std::cout << counter;
    return 0;
}
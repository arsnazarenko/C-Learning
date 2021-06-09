#include <iostream>
#include <vector>

char change_color(char color) {
    return char(((color == 1) ? 2 : 1));
}

bool dfs(int v, std::vector<std::vector<int>> const& graph, std::vector<char>& colors, char color) {
    colors[v] = color;
    for (int u: graph[v]) {
        if (colors[u] == 0) {
            if (!dfs(u, graph, colors, change_color(color))) {
                return false;
            }
        } else if (colors[u] == color) {
            return false;
        }
    }
    return true;
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.precision(20);
    int n;
    int m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> graph(n);
    std::vector<char> colors(n, 0);
    for (int i = 0; i < m; ++i) {
        int v, u;
        std::cin >> v >> u;
        v--;
        u--;
        graph[v].push_back(u);
        graph[u].push_back(v);
    }
    bool res = dfs(0, graph, colors, 1);
    for (int i = 0; i < n; ++i) {
        if (colors[i] == 0 && res) {
            res = (res & dfs(i, graph, colors, 1));
        }
    }
    std::cout << (res ? "YES" : "NO");
}
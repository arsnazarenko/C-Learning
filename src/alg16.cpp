#include <iostream>
#include <vector>
//  Дерево - это связный граф, в котором нет простых циклов!
//  Простой цикл - это цикл, в котором ребра не повторяется
//   A        B
//  0--------0
//   \        \
//    \        \
//     \ C      \ D
//      0--------0
//  Простой цикл - ABCD


using ui32 = int64_t;
using Graph = std::vector<std::vector<ui32>>;
using Colors = std::vector<char>;
const ui32 inf = 1e9;

void dfs(const ui32 v, Graph const& graph, Colors& colors, const bool reverse, const ui32 len, ui32& counter) {
    colors[v] = 1;
    //  количество закрашенных
    counter++;
    for (size_t i = 0; i < graph.size(); ++i) {
        ui32 adjacent_vert_len = (reverse ? graph[i][v] : graph[v][i]);
        if (adjacent_vert_len <= len && colors[i] == 0) {
            dfs(i, graph, colors, reverse, len, counter);
        }
    }
}


bool is_fully_connected_graph(ui32 len, const ui32 n, Graph const& graph) {
    ui32 counter = 0;
    ui32 counter_reverse = 0;
    Colors colors(n, 0);
    Colors colors_reverse(n, 0);
    dfs(0, graph, colors, false, len, counter);
    if (counter == n) {
        dfs(0, graph, colors_reverse, true, len, counter_reverse);
        return (counter_reverse == counter);
    }
    return false;
}



int main() {
    //  необходимо сформировать полносвязный орграф с минимальным путем из любой вершины в любые другие
    //  оргаф полносвязан если:
    //  из вершины v существует путь во все остальные
    //  и одновременно из всех вершин есть путь в v
    //  обратный граф - это исходный граф, ребра которого
    //  направлены в противоположную сторону
    //  Условие полносвязности графа:
    //  1. Если в исходном графе начиная из вершины v можно добраться до всех остальных
    //  2. В обратном графе начиная обход из v можно обойти все остальные
    //  вершины <=> из всех вершин графа есть путь в вершину v
    ui32 min_len = inf;
    ui32 n;
    std::cin >> n;
    Graph graph(n, std::vector<ui32>(n));
    for (std::vector<ui32> &row : graph) {
        for (ui32 &v : row) {
            std::cin >> v;
            min_len = std::min(min_len, v);
        }
    }
    //  слева значение, которое точно не может быть решением
    ui32 left = min_len - 1;
    //  справа максимально возможное значение
    ui32 right = inf - 1;
    while (right - left > 1) {
        ui32 mid = (left + right) / 2;
        //  при таком размере бака можно долететь до всех точек на карте
        if (is_fully_connected_graph(mid, n, graph)) {
            right = mid;
        } else {
            //  при таком значении долететь до всех городов еще не удается,
            //  рассматриваем все значения правее этого
            left = mid;
        }
    }
    //      результат окажется в правой границе
    std::cout << right;
    return 0;
}



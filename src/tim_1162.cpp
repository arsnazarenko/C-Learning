#include <iostream>
#include <vector>
#include <algorithm>

using i32 = int32_t;
const i32 inf = 1e4;

struct edge {
    i32 a, b;
    double rab, cab;

    edge(const i32 a, const i32 b,const double rab,const double cab)
    : a(a), b(b), rab(rab), cab(cab) {}

    double exchange(double sum) const {
        return (sum - cab) * rab;
    }
};
using Edges = std::vector<edge>;
bool algo_cycle(int n, int m, int v, Edges const& e, std::vector<double>& money, double start_sum) {
    money[v] = start_sum;
    // делаем бесконечный цикл, т.к в зависимости от порядка обхода вершин,
// алгоритм может дать верный ответ меньше , чем за n-1 фазу,
// поэтому если на одной из фаз не произошло никаких
// релаксаций, то можно вызодить из цикла
    bool relax;
    for(int k = 0; k < n; ++k) {
        relax = false;
        for (int j = 0; j < m; ++j) {
            //  отрицательные ребра могут улучшить путь до недостежимыъ вершин
            //  к примеру, путь будет (inf - 1), поэтому не будем улучшать такие ребра
            //  если вершина достижима
            if (money[e[j].a] > -0.1) {
                if (money[e[j].b] < e[j].exchange(money[e[j].a])) {
                    money[e[j].b] = e[j].exchange(money[e[j].a]);
                    relax = true;
                }
            }
        }
    }
    if (relax) return true;
    return false;
}

int main() {
    i32 n, m, s;
    double v;
    std::string str_v;
    std::cin >> n >> m >> s >> str_v;
    s--;
    std::replace( str_v.begin(), str_v.end(), ',', '.');
    v = std::stod(str_v);
    Edges edges;
    std::vector<double> money(n, -0.1);
    for (i32 i = 0; i < m; ++i) {
        i32 a, b;
        std::string rab, cab, rba, cba;
        std::cin >> a >> b >> rab >> cab >> rba >> cba;
        std::replace( rab.begin(), rab.end(), ',', '.');
        std::replace( cab.begin(), cab.end(), ',', '.');
        std::replace( rba.begin(), rba.end(), ',', '.');
        std::replace( cba.begin(), cba.end(), ',', '.');
        a--;
        b--;
        edges.emplace_back(a, b, std::stod(rab), std::stod(cab));
        edges.emplace_back(b, a, std::stod(rba), std::stod(cba));
    }
    std::cout << (algo_cycle(n, 2 * m, s, edges, money, v) ? "YES" : "NO");
    return 0;
}
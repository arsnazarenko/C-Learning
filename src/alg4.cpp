#include <iostream>

void chaos_start() {
    size_t a;
    int64_t b;
    int64_t c;
    int64_t d;
    size_t k;
    std::cin >> a >> b >> c >> d >> k;

    while (k > 0) {
        int64_t tmp = a * b - c;
        if (tmp <= 0) {
            a = 0;
            break;
        } else if (tmp >= d && tmp * b - c >= d) {
            a = d;
            break;
        } else if (tmp == a && a < d) {
            a = a;
            break;
        } else {
            a = tmp > d ? d : tmp;
        }
        k--;
    }
    std::cout << a;
}

int main() {
    chaos_start();
    return 0;
}
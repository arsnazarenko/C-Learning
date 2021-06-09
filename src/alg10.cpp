#include <iostream>
#include <list>
#include <deque>


struct my_queue{
private:
    uint32_t l;
    uint32_t r;
    std::deque<std::string> left;
    std::deque<std::string> right;

public:
    my_queue() : l(0), r(0)   {
    }

    void push_back(std::string const& s) {
        right.push_back(s);
        if (r < l) {
            r++;    // l == r
        } else {
            left.push_back(right.front());
            right.pop_front();
            l++;    // l > r
        }
    }

    void push_middle(std::string const& s) {
        if (l == r) {   // четное
            left.push_back(s);
            l++;    // l > r
        } else {    //  нечетное, после центра вставка
            right.push_front(s);
            r++;    //  l == r
        }
    }

    void pop_front() {
        std::cout << left.front() << '\n';
        left.pop_front();
        if (r < l) {
            l--;
        } else {    // во второй очереди гарантированно остается 1 элемент
            left.push_back(right.front());
            right.pop_front();
            r--;
        }
    }
};



int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.precision(20);
    uint32_t n;
    std::cin >> n;
    std::cin.ignore();
    my_queue goblins_q;
    for (uint32_t i = 0; i < n; ++i) {
        std::string str;
        std::getline(std::cin, str);
        if (str[0] == '-') {
            goblins_q.pop_front();
        } else {
            std::string val = str.substr(2);
            if (str[0] == '+') {
                goblins_q.push_back(std::move(val));
            } else {
                goblins_q.push_middle(std::move(val));
            }
        }
    }
    return 0;
}
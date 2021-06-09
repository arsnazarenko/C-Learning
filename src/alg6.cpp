#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

bool comp(std::string const& a, std::string const& b) {
    size_t min_length = std::min(a.length(), b.length());
    if (a.substr(0, min_length) == b.substr(0, min_length) && a.length() != b.length()) {
        if ( (a + b) < (b + a)) {
            return true;
        }
        return false;
    }
    return a < b;
}

int main() {
    std::string line;
    std::vector<std::string> lines;
    while(std::cin >> line) {
        lines.push_back(line);
    }
    if (lines.size() == 1) {
        std::cout << lines[0];
    } else {
        std::sort(lines.begin(), lines.end(), comp);
        for(int64_t i = lines.size() - 1; i > -1; i--) {
            std::cout << lines[i] << " ";
        }
    }
    return 0;
}
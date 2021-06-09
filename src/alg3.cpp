#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>

std::string get_by_key(std::unordered_map<std::string, std::vector<std::string>> const& map, const std::string& key) {
    auto it = map.find(key);
    if (it != map.end()) {
        if (!it->second.empty()) {
            return it->second.back();
        }
    }
    return "0";
}

void insert_by_key(std::unordered_map<std::string, std::vector<std::string>>& map, const std::string& key, const std::string& value) {
    auto it = map.find(key);
    if (it != map.end()) {
        it->second.push_back(value);
    } else {
        std::pair<std::string, std::vector<std::string>> pair (key, std::vector<std::string>(1, value));
        map.insert(pair);
    }
}




bool str_is_digit(std::string const& str) {
    for (char const& ch: str ) {
        if (!isdigit(ch) && (ch != '-')) return false;
    }
    return true;
}

void clear_by_key(std::unordered_map<std::string, std::vector<std::string>>& map, const std::string& key) {
    map[key].pop_back();
}

void parser_start() {
    size_t unit_counter = 0;
    std::stack<std::vector<std::string>> stack;
    std::unordered_map<std::string, std::vector<std::string>> variables;
    const std::string UNIT_START = "{";
    const std::string UNIT_END = "}";
    std::string input;
    while ((std::getline(std::cin, input))) {
        if (input == UNIT_START) {
            unit_counter++;
            if (unit_counter > 0) {
                stack.push(std::vector<std::string>());
            }
        } else if (input == UNIT_END) {
            unit_counter--;
            for(std::string const& var: stack.top()) {
                clear_by_key(variables, var);
            }
            stack.pop();
        } else {
            size_t idx = input.find('=');
            const std::string variable_name = input.substr(0, idx);
            const std::string variable_value = input.substr(idx + 1);
            std::string new_value;
            if (str_is_digit(variable_value)) { // is digit
                new_value = variable_value;
            } else {    //  is other variable
                new_value = get_by_key(variables, variable_value);
                std::cout << new_value << std::endl;
            }
            insert_by_key(variables, variable_name, new_value);
            if (unit_counter > 0) {
                stack.top().push_back(variable_name);
            }

        }
    }

}

int main () {
    parser_start();
}


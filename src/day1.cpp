#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <sys/types.h>
#include <vector>
#include "../include/input_reader.h"
#include <stdlib.h>

int main() {
    std::vector<std::string> input_lines{};
    try {
        // Reading input from the text file
        input_lines = input_reader::read_lines("input/day1.txt");
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    std::vector<int> l1;
    std::vector<int> l2;
    for (auto &line : input_lines) {
        std::string delimiter = "   ";
        auto el = line.substr(0, line.find(delimiter));
        /* std::cout << line << std::endl; */
        l1.push_back(std::stoi(el));    
        auto pos = el.length() + delimiter.length();
        el = line.substr(pos, line.length() - pos);
        l2.push_back(std::stoi(el));    
    }
    std::sort(l1.begin(), l1.end());
    std::sort(l2.begin(), l2.end());

    auto it1 = l1.begin();
    auto it2 = l2.begin();

    int sum = 0;
    for(; it1 != l1.end() && it2 != l2.end(); ++it1, ++it2){
        sum += abs(*it1 - *it2);
    }
    printf("Part 1: %d\n", sum);

    // Part 2 
    std::map<int, int> lookup{};
    for (auto &val : l1){
        auto c = std::count(l2.begin(), l2.end(), val);
        lookup[val] = c;
    }

    int sum2 = 0;
    for(auto &val : l1){
        sum2 += val * lookup[val];
    }
    printf("Part 2: %d\n", sum2);

    return 0;
}

#include "../include/input_reader.h"
#include <functional>
#include <iterator>
#include <stdlib.h>
#include <numeric>
#include <algorithm>
#include <sstream>
#include <string>

int main() {
    std::vector<std::string> input_lines{};
    try {
        // Reading input from the text file
        input_lines = input_reader::read_lines("input/day2.txt");
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    std::vector<std::vector<int>> reports;
    for(auto &line : input_lines){
        reports.emplace_back();
        std::string token;
        std::stringstream ss(line);
        while(std::getline(ss, token, ' ')){
            reports.back().push_back(stoi(token));
        }
    }

    std::vector<int> diffs(reports.size());
    std::transform(reports.begin(), reports.end(), diffs.begin(), [](std::vector<int> &a) -> int{
        std::vector<int> bar;
        std::vector<int> reverse(a.size());
        std::reverse_copy(a.begin(), a.end(), reverse.begin());

        if(!std::is_sorted(a.begin(), a.end()) && !std::is_sorted(reverse.begin(), reverse.end())) return -1;
        std::vector<int> foo(a.size());
        std::adjacent_difference(a.begin(), a.end(), foo.begin());
        int i = std::count_if(foo.begin()+1, foo.end(), [](int b){
                return abs(b) < 1 || abs(b) > 3;
        });
        return i;
    });

    int result = std::count_if(diffs.begin(), diffs.end(), [](int a){return a == 0;});
    printf("Part 1: %d\n", result);

    std::vector<bool> diffs2(reports.size());
    std::transform(reports.begin(), reports.end(), diffs2.begin(), [](std::vector<int> &report){
        bool flag = false;
        for(uint rm = 0; rm < report.size()+1; rm++){
            std::vector<int> a(report);
            if(rm < report.size()) a.erase(a.begin() + rm);

            std::vector<int> bar;
            std::vector<int> reverse(a.size());
            std::reverse_copy(a.begin(), a.end(), reverse.begin());

            if(!std::is_sorted(a.begin(), a.end()) && !std::is_sorted(reverse.begin(), reverse.end())){
                continue;
            }

            std::vector<int> foo(a.size());
            std::adjacent_difference(a.begin(), a.end(), foo.begin());
            int i = std::count_if(foo.begin()+1, foo.end(), [](int b){
                    return abs(b) < 1 || abs(b) > 3;
            });
            if(i > 0){
                continue;
            };
            flag = true;
            break;
        }
        return flag;
    });

    int result2 = std::count_if(diffs2.begin(), diffs2.end(), [](bool a){return a;});
    printf("Part 2: %d\n", result2);

    return 0;
}

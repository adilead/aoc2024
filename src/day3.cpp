#include "../include/input_reader.h"
#include <bits/stdc++.h>
#include <cstdio>
#include <iostream>
#include <regex>
#include <stdlib.h>
#include <string>

int main() {
    std::vector<std::string> input_lines{};
    try {
        // Reading input from the text file
        input_lines = input_reader::read_lines("input/day3.txt");
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    std::regex mul_rgx("mul\\((\\d+),(\\d+)\\)");
    int sum = 0;
    for(auto &line : input_lines){
        std::string s = line;
        for (std::smatch sm; regex_search(s, sm, mul_rgx); s = sm.suffix()){
            sum += std::stoi(sm[1]) * std::stoi(sm[2]);
        }
    }

    printf("Part 1: %d\n", sum);

    int sum2 = 0;
    std::string prog;
    for(const auto &line: input_lines) prog += line;
    std::regex do_rgx("do\\(\\)");
    std::regex dont_rgx("don't\\(\\)");
    std::vector<std::smatch> muls;
    std::vector<int> dos;
    std::vector<int> donts;

    std::string s = prog;
    /* for (std::smatch sm; regex_search(s, sm, mul_rgx); s = sm.suffix()){ */
    for (std::sregex_iterator it = std::sregex_iterator(s.begin(), s.end(), mul_rgx); it != std::sregex_iterator(); it++) {
        std::smatch sm;
        sm = *it;
        muls.push_back(sm);
    }

    s = prog;
    for (std::sregex_iterator it = std::sregex_iterator(s.begin(), s.end(), do_rgx); it != std::sregex_iterator(); it++) {
        std::smatch sm;
        sm = *it;
        dos.push_back(sm.position());
    }

    s = prog;
    for (std::sregex_iterator it = std::sregex_iterator(s.begin(), s.end(), dont_rgx); it != std::sregex_iterator(); it++) {
        std::smatch sm;
        sm = *it;
        donts.push_back(sm.position());
    }


    std::vector<std::smatch> ok;
    for(const auto &mul: muls){
        int max_doo = -1;
        for(const auto &doo: dos){
            if(doo > mul.position()) break;
            if(doo > max_doo) max_doo = doo;
        }
        int max_dont = -1;
        for(const auto &dont: donts){
            if(dont > mul.position()) break;
            if(dont > max_dont) max_dont = dont;
        }
        if(max_doo > max_dont || max_dont < 0){
            sum2 += std::stoi(mul[1]) * std::stoi(mul[2]);
        }
    }

    printf("Part 2: %d\n", sum2);
    return 0;
}

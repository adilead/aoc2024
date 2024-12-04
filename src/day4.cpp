#include "../include/input_reader.h"
#include <bits/stdc++.h>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <regex>
#include <sstream>
#include <stdlib.h>
#include <string>

int search_at(std::vector<std::string> field, int x, int y, int v, int h){
    if((v == -1 && y < 3) || (h == -1 && x < 3)) return 0;
    if((v == 1 && y > field.size()-4) || (h == 1 && x > field[0].size()-4)) return 0;
    std::stringstream ss;
    for(int i =0; i<4; i++){
        ss << field[y+v*i][x+h*i];
    }
    if(ss.str().compare("XMAS") == 0) return 1;
    return 0;
}

bool search_X_MAS(std::vector<std::string> field, int x, int y, int v, int h, std::string pattern){
    if((v == -1 && y < 1) || (h == -1 && x < 1)) return false;
    if((v == 1 && y > field.size()-2) || (h == 1 && x > field[0].size()-2)) return false;
    std::stringstream ss;
    for(int i =0; i<2; i++){
        ss << field[y+v*i][x+h*i];
    }
    if(ss.str().compare(pattern) == 0) return true;
    return false;
}

int main() {
    std::vector<std::string> input_lines{};
    try {
        // Reading input from the text file
        input_lines = input_reader::read_lines("input/day4.txt");
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    int sum = 0;
    for(size_t i = 0; i < input_lines.size(); i++){
        for(size_t j = 0; j < input_lines[i].size(); j++){
            sum += search_at(input_lines, j, i, -1, 0);
            sum += search_at(input_lines, j, i, -1, -1);
            sum += search_at(input_lines, j, i, 0, -1);
            sum += search_at(input_lines, j, i, 1, -1);
            sum += search_at(input_lines, j, i, 1, 0);
            sum += search_at(input_lines, j, i, 1, 1);
            sum += search_at(input_lines, j, i, 0, 1);
            sum += search_at(input_lines, j, i, -1, 1);
        }
    }

    int sum2 = 0;
    for(size_t i = 0; i < input_lines.size(); i++){
        for(size_t j = 0; j < input_lines[i].size(); j++){
            bool diag1 = (search_X_MAS(input_lines, j, i, -1, -1, "AS") &&
            search_X_MAS(input_lines, j, i, 1, 1, "AM")) ||
            (search_X_MAS(input_lines, j, i, -1, -1, "AM") &&
            search_X_MAS(input_lines, j, i, 1, 1, "AS"));

            bool diag2 = (search_X_MAS(input_lines, j, i, -1, 1, "AS") &&
            search_X_MAS(input_lines, j, i, 1, -1, "AM")) ||
            (search_X_MAS(input_lines, j, i, -1, 1, "AM") &&
            search_X_MAS(input_lines, j, i, 1, -1, "AS"));

            if(diag1 && diag2) sum2++;
        }
    }

    printf("Part 1: %d\n", sum);
    printf("Part 2: %d\n", sum2);
}

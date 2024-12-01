#pragma once
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>

namespace input_reader {
    // Function to read the content of a file into a vector of strings (one per line)
    std::vector<std::string> read_lines(const std::string& filename) {
        std::ifstream file(filename);
        std::vector<std::string> lines;

        if (!file) {
            throw std::runtime_error("Could not open the file: " + filename);
        }

        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        if(lines[lines.size()-1] == "") {
            lines.pop_back();
        }

        file.close();
        return lines;
    }
}

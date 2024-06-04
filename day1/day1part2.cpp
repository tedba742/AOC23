#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <cctype>

std::pair<std::string, std::string> find_first_and_last_matches(const std::string &line, const std::vector<std::string> &matches) {
    std::string first_match;
    std::string last_match;
    size_t first_pos = std::string::npos;
    size_t last_pos = std::string::npos;

    for (const auto &match : matches) {
        size_t pos = line.find(match);
        while (pos != std::string::npos) {
            if (first_pos == std::string::npos || pos < first_pos) {
                first_pos = pos;
                first_match = match;
            }
            if (last_pos == std::string::npos || pos > last_pos) {
                last_pos = pos;
                last_match = match;
            }
            pos = line.find(match, pos + 1);
        }
    }
    
    return std::make_pair(first_match, last_match);
}

int main() {
    std::fstream file("Input.txt");
    std::string line;
    int sum = 0;
    std::map<std::string, int> valueMap = { 
        { "one", 1 }, { "two", 2 }, { "three", 3 }, { "four", 4 }, { "five", 5 },
        { "six", 6 }, { "seven", 7 }, { "eight", 8 }, { "nine", 9 }, 
        { "1", 1 }, { "2", 2 }, { "3", 3 }, { "4", 4 }, { "5", 5 },
        { "6", 6 }, { "7", 7 }, { "8", 8 }, { "9", 9 }
    };
    std::vector<std::string> matches = {
        "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", 
        "1", "2", "3", "4", "5", "6", "7", "8", "9"
    };

    while (std::getline(file, line)) {

        auto result = find_first_and_last_matches(line, matches);
        std::string first_digit = result.first;
        std::string last_digit = result.second;

        if (!first_digit.empty() && !last_digit.empty()) {
            int first_value = valueMap[first_digit];
            int last_value = valueMap[last_digit];
            
            int calibration_value = first_value * 10 + last_value;
            
            sum += calibration_value;
        }
    }
    std::cout << "Sum of all calibration values: " << sum << std::endl;
    return 0;
}

#include <vector>
#include <iostream>
#include <fstream>
#include <regex>

struct pos_t {
    int x, y;
};

struct part_t {
    pos_t pos;
    std::string name;
};

struct grid {
    std::vector<part_t> numbers;
    std::vector<part_t> specialCharacters;
};

bool is_number(const std::string& str) {
    return std::all_of(str.begin(), str.end(), ::isdigit);
}

grid readFile(const std::string& file) {
    grid ret;
    std::ifstream fs(file);
    std::string line;
    int y = 0;
    while (std::getline(fs, line)) {
        std::regex word_regex("[\\w]+|[^.]");
        for (auto it = std::sregex_iterator(line.begin(), line.end(), word_regex); it != std::sregex_iterator(); it++) {
            if (is_number(it->str())) {
                ret.numbers.push_back({ {(int)it->position(),y}, it->str() });
            }
            else {
                ret.specialCharacters.push_back({ {(int)it->position(),y}, it->str() });
            }
        }
        y++;
    }
    return ret;
}

bool IsAdjacent(part_t& number, const part_t& specialCharacter) {
    for (int i = 0; i < number.name.size(); ++i) {
        int xdist = abs(specialCharacter.pos.x - (number.pos.x + i));
        int ydist = abs(specialCharacter.pos.y - number.pos.y);
        if ((xdist == 1 && ydist == 1) || (xdist == 0 && ydist == 1) || (xdist == 1 && ydist == 0)) {
            return true;
        }
    }
    return false;
}

int Count(grid& grid) {
    auto find = [&](auto& digits) {
        for (auto& symbol : grid.specialCharacters) {
            if (IsAdjacent(digits, symbol)) {
                return true;
            }
        }
        return false;
        };

    int sum = 0;
    for (auto& number : grid.numbers) {
        if (find(number)) {
            sum += std::stoi(number.name);
        }
    }

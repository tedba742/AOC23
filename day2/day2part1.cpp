#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>

bool is_game_possible(const std::string& game, int max_red, int max_green, int max_blue) {
    std::regex re("(\\d+) (red|green|blue)");
    std::smatch match;
    std::stringstream ss(game);
    std::string segment;
    while (std::getline(ss, segment, ';')) {
        std::string::const_iterator search_start(segment.cbegin());
        while (std::regex_search(search_start, segment.cend(), match, re)) {
            int count = std::stoi(match[1]);
            std::string color = match[2];
            if (color == "red" && count > max_red) return false;
            if (color == "green" && count > max_green) return false;
            if (color == "blue" && count > max_blue) return false;
            search_start = match.suffix().first;
        }
    }
    return true;
}

int main() {
    std::ifstream file{"Input.txt"};
    int max_red{12};
    int max_green{13};
    int max_blue{14};

    std::string line{""};
    int sum_of_ids{0};

    while (std::getline(file, line)) {
        std::regex re("Game (\\d+): (.*)");
        std::smatch match;
        if (std::regex_search(line, match, re)) {
            int game_id = std::stoi(match[1]);
            std::string game_details = match[2];
            if (is_game_possible(game_details, max_red, max_green, max_blue)) {
                sum_of_ids += game_id;
            }
        }
    }

    std::cout << "Sum of all possible game IDs: " << sum_of_ids << std::endl;
}

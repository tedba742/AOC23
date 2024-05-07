#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

void readFile(const std::string& filename, std::vector<std::string>& lines) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();
}

int main() {
    std::vector<std::string> lines;
    readFile("text.txt", lines);

    std::vector<std::vector<std::string>> gameData;

    for (const auto& line : lines) {
        size_t colonPos = line.find(':');
        if (colonPos != std::string::npos) {
            // Extract game data after the colon
            std::string gameDataStr = line.substr(colonPos + 1);

            std::stringstream ss(gameDataStr);
            std::string token;
            std::vector<std::string> tokens;
            while (std::getline(ss, token, ';')) {
                tokens.push_back(token);
            }

            // Store the game data
            gameData.push_back(tokens);
        }
    }

    int sumOfPossibleGames = 0;
    std::map<std::string, int> colorMap = {
        {"red,", 12}, {"green,", 13}, {"blue,", 14}, {"red", 12}, {"green", 13}, {"blue", 14},
        {"red;", 12}, {"green;", 13}, {"blue;", 14}
    };

    for (const auto& data : gameData) {
        bool validGame = true; // Reset the flag for each game
        for (const auto& item : data) {
            std::istringstream iss(item);
            int value;
            std::string color;

            while (iss >> value >> color) {
                auto it = colorMap.find(color);
                if (it != colorMap.end() && value > it->second) {
                    validGame = false;
                    break; // No need to check further if game is already invalid
                }
            }
        
            if (!validGame) {
                break;
            }
        }
        
        if (validGame) {
            sumOfPossibleGames++;
        }
    }

    std::cout << "Number of valid games: " << sumOfPossibleGames << std::endl;

    return 0;
}

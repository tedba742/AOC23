
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
            std::string gameDataStr = line.substr(colonPos + 1);

            std::stringstream ss(gameDataStr);
            std::string token;
            std::vector<std::string> tokens;
            while (std::getline(ss, token, ';')) {
                tokens.push_back(token);
            }

            gameData.push_back(tokens);
        }
    }

    int sumOfPossibleGames = 0;
    bool validGame = true;
    std::map<std::string, int> colorMap = {
      {"red,", 0}, {"green,", 0}, {"blue,", 0}, {"red,", 0}, {"green,", 0}, {"blue,", 0}, {" red", 0}, {"green", 0}, {"blue", 0},
      {"red;", 0}, {"green;", 0}, {"blue;", 0}, {" red, ", 0}, {" green,", 0}, {" blue,", 0}
    };

    int totalCount{ 0 };
    // 12 i fall av 5.
    std::map<std::string, int> redMap = {};
    std::map<std::string, int> greenMap = {};
    std::map<std::string, int> blueMap = {};

    for (const auto& data : gameData) {
        validGame = true; 

        for (const auto& item : data) {
            std::istringstream iss(item);
            int value;
            std::string color;

            while (iss >> value >> color) {
                std::cout << color << " " << value;
                colorMap[color] = value;
            }
        }

        for (const auto& pair : colorMap) {
            if (pair.first == "red" || pair.first == "red," || pair.first == "red;" || pair.first == " red," || pair.first == "red") {
              
                redMap[pair.first] = pair.second;
            
            }
            if (pair.first == "blue" || pair.first == "blue," || pair.first == "blue;" || pair.first == " blue,") {
                blueMap[pair.first] = pair.second;

            }
            if (pair.first == "green" || pair.first == "green," || pair.first == "green;" || pair.first == " green,") {
                greenMap[pair.first] = pair.second;

            }
        }

        int maxGreenValue, maxBlueValue, maxRedValue;
        auto maxGreenIter = std::max_element(greenMap.begin(), greenMap.end(),
            [](const auto& a, const auto& b) {
                return a.second < b.second; 
            });

        if (maxGreenIter != greenMap.end()) {
             maxGreenValue = maxGreenIter->second; 
        }

        auto maxRedIter = std::max_element(redMap.begin(), redMap.end(),
            [](const auto& a, const auto& b) {
                return a.second < b.second;
            });

        if (maxRedIter != redMap.end()) {
             maxGreenValue = maxGreenIter->second; 
          
        }

        auto maxBlueIter = std::max_element(blueMap.begin(), blueMap.end(),
            [](const auto& a, const auto& b) {
                return a.second < b.second; 
            });

        if (maxBlueIter != blueMap.end()) {
             maxBlueValue = maxBlueIter->second;
        }

        totalCount = totalCount + (maxGreenValue * maxBlueValue * maxRedValue);
        maxGreenValue = 1;
        maxBlueValue = 1;
        maxRedValue = 1;
        for (auto& pair : colorMap) {
            pair.second = 0;
        }
    }
    std::cout << "Number of valid games: " << totalCount << std::endl;

    return 0;
}


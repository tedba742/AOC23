#include <vector>
#include <iostream>
#include <fstream>
#include <regex>
#include <algorithm>
#include <map>
#include <tuple>
#include <string>

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


void mapValuesInsert(const std::vector<std::string>& lines, std::map<std::string, std::tuple<std::string, std::string>>& mapValues) {
    for (int i = 2; i < lines.size(); i++) {
        std::string key = lines[i].substr(0, 3);
        std::string firstValue = lines[i].substr(7, 3);
        std::string secondValue = lines[i].substr(12, 3);
        mapValues.insert({ key, std::make_tuple(firstValue, secondValue) });
    }
}



int findPath(const std::map<std::string, std::tuple<std::string, std::string>>& mapValues, const std::string& leftOrRight) {
     std::string searchKey = "AAA";
    int charIndex = 0;

    while (searchKey != "ZZZ") {
        if (leftOrRight[charIndex] == 'L') {
            searchKey = std::get<0>(mapValues.at(searchKey));
        }
        else {
            searchKey = std::get<1>(mapValues.at(searchKey));
        }
        charIndex++;
        count++;
        if (charIndex == leftOrRight.size()) {
            charIndex = 0;
        }
    }

    return count;
}


int main() {
    std::string leftOrRight;
    std::map<std::string, std::tuple<std::string, std::string>> mapValues;
    std::vector<std::string> lines;

    readFile("text.txt", lines);
    leftOrRight = lines[0] + lines[1];
    std::cout << leftOrRight << std::endl;
    mapValuesInsert(lines, mapValues);
    std::cout << "LR size: " << leftOrRight.size() << std::endl;

    std::cout << "path iterations: " << findPath(mapValues, leftOrRight) << std::endl;




    return 0;
}

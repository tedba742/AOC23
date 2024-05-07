#include <vector>
#include <iostream>
#include <fstream>
#include <regex>
#include <algorithm>
#include <map>

std::vector<std::string> dealtHandVector;
std::vector<std::string> bidVector;

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

void splitArray(std::vector<std::string>& lines, std::vector<std::string>& dealtHandVector, std::vector<std::string>& bidVector) {
    for (const auto& line : lines) {
        dealtHandVector.push_back(line.substr(0, 5));
        bidVector.push_back(line.substr(6));
    }
}

void getAmountOfCardsOfOneType(const std::string& currentHand, std::map<char, int>& handValues) {
    for (char card : currentHand) {
        handValues[card]++;
    }
}

int getWhatKindOfHand(std::map<char, int> handValues) {
    int maxValue = 0;
    for (const auto& pair : handValues) {
        if (pair.second > maxValue) {
            maxValue = pair.second;
        }
    }
    int valueOfTheHand{ 0 };
    switch (handValues.size()) {
    case 1:
        valueOfTheHand = 7;
        break;
    case 2:
        if (maxValue >= 4) {
            valueOfTheHand = 6;
        }
        else {
            valueOfTheHand = 5;
        }
        break;
    case 3:
        if (maxValue == 3) {
            valueOfTheHand = 4;
        }
        else {
            valueOfTheHand = 3;
        }
        break;
    case 4:
        if (maxValue == 2) {
            valueOfTheHand = 2;
        }
        break;
    case 5:
        valueOfTheHand = 1;
        break;
    default:
        break;
    }
    return valueOfTheHand;
}

bool getCardValue(std::string a, std::string b, std::map<char, int> cardValues) {
    for (int i = 0; i < a.length(); i++) {
        char aVal = a[i];
        char bVal = b[i];
        if (cardValues[aVal] > cardValues[bVal]) {
            return true;
        }
        else if (cardValues[aVal] < cardValues[bVal]) {
            return false;
        }
    }
    return false;
}

int main() {
    std::map<char, int> handValuesMap;

    std::vector<std::string> lines;
    readFile("text.txt", lines);
    splitArray(lines, dealtHandVector, bidVector);

    std::map<std::string, std::tuple<int, int>> handBidValueMap;

    for (int i = 0; i < dealtHandVector.size(); i++) {
        getAmountOfCardsOfOneType(dealtHandVector[i], handValuesMap);
        handBidValueMap[dealtHandVector[i]] = std::make_tuple(getWhatKindOfHand(handValuesMap), std::stoi(bidVector[i]));
        handValuesMap.clear();
    }

    std::map<char, int> cardValues{ {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9},
                                     {'T', 10}, {'J', 11}, {'Q', 12}, {'K', 13}, {'A', 14} };

    auto cmp = [&cardValues](const auto& a, const auto& b) {
        if (std::get<0>(a.second) != std::get<0>(b.second)) {
            return std::get<0>(a.second) > std::get<0>(b.second);
        }
        std::string str1 = a.first;
        std::string str2 = b.first;
        return getCardValue(str1, str2, cardValues);
        };

    std::vector<std::pair<std::string, std::tuple<int, int>>> sorted(handBidValueMap.begin(), handBidValueMap.end());
    std::sort(sorted.begin(), sorted.end(), cmp);

    long long totalCount{ 0 };
    long long rank{ static_cast<long long>(sorted.size()) };
    for (const auto& pair : sorted) {
        std::cout << pair.first << std::endl;
        long long tmp = std::get<1>(pair.second) * rank;
        totalCount += tmp;
        rank--;
    }

    std::cout << totalCount << std::endl;
    return 0;
}
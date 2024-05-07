#include <vector>
#include <iostream>
#include <fstream>
#include <regex>
#include <map>
#include <algorithm>



size_t getAmountOfWinningTickets(const std::vector<int>& numbers, const std::vector<int>& winningNumbers) {
    std::vector<int> sortedNumbers = numbers;
    std::vector<int> sortedWinningNumbers = winningNumbers;

    std::sort(sortedNumbers.begin(), sortedNumbers.end());
    std::sort(sortedWinningNumbers.begin(), sortedWinningNumbers.end());

    std::vector<int> result(std::min(sortedNumbers.size(), sortedWinningNumbers.size()));

    auto it = std::set_intersection(sortedNumbers.begin(), sortedNumbers.end(), sortedWinningNumbers.begin(), sortedWinningNumbers.end(), result.begin());
    result.resize(it - result.begin());

    return result.size();
}

void load_input(const std::string& file) {
    std::ifstream fs(file);
    std::string line;
    int lineNumber{ 0 };
    int totalCount{ 0 };
    while (std::getline(fs, line)) {
        std::regex word_regex("[\\d]+|[|]|[:]");
        bool readingMyNumbers = false;
        bool readingWinningNumbers = false;

        std::vector<int> numbers;
        std::vector<int> winningNumbers;

        for (auto it = std::sregex_iterator(line.begin(), line.end(), word_regex); it != std::sregex_iterator(); it++) {
            if (it->str() == ":") {
                readingMyNumbers = true;
            }
            else if (it->str() == "|") {
                readingWinningNumbers = true;
                readingMyNumbers = false;
            }
            else if (readingWinningNumbers) {
                winningNumbers.push_back(std::stoi(it->str()));
            }
            else if (readingMyNumbers) {
                numbers.push_back(std::stoi(it->str()));
            }
        }
        int multiplyWinningGameTickets{ 1 };

        size_t amountOfWinningTickets = getAmountOfWinningTickets(numbers, winningNumbers);
        if (amountOfWinningTickets >1){
            for (int i = 1; i < amountOfWinningTickets; i++) {
                multiplyWinningGameTickets *= 2;

            }
            totalCount += multiplyWinningGameTickets;

        }
        else if (amountOfWinningTickets == 1) {

            totalCount++;
        }
        lineNumber++;
    }
    std::cout << "result: " << totalCount << std::endl;
}



int main() {
    load_input("text.txt");

    return 0;
}
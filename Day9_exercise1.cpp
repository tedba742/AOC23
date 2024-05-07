#include <algorithm>
#include <numeric>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>

int getNext(std::vector<int>& value_sequence) {

    if (value_sequence.size() == 1) {
        value_sequence.push_back(value_sequence.back());
        return value_sequence.back();
    }
    std::vector<int> new_value_sequence;
    new_value_sequence.reserve(value_sequence.size() - 1);
    for (int i = 0; i < value_sequence.size() - 1; i++) {
        new_value_sequence.push_back(value_sequence[i + 1] - value_sequence[i]);
    }

    if (std::any_of(value_sequence.begin(), value_sequence.end(), [](const auto& ele) {
        return ele != 0; })) {
        const auto value_to_add = getNext(new_value_sequence);
        value_sequence.push_back(value_sequence.back() + value_to_add);
        return value_sequence.back();
    }
    value_sequence.push_back(value_sequence.back());
    return value_sequence.back();
}

std::vector<int> readLine(const std::string& s) {
    std::vector<int> numbers;
    int value;
    std::istringstream iss(s);
    while (iss >> value) {
        numbers.push_back(value);
    }

    return numbers;
}

int main(int argc, char* argv[]) {
    std::string input = "text.txt";
    if (argc > 1) {
        input = argv[1];
    }

    std::string line;
    std::fstream file(input);
    std::vector<std::vector<int>> value_sequences;
    while (std::getline(file, line)) {
        value_sequences.push_back(readLine(line));
    }
    int total = 0;
    for (auto& value_sequence : value_sequences) {
        int new_value = getNext(value_sequence);
        total += new_value;
    }
    std::cout << total << std::endl;
    return 0;
}

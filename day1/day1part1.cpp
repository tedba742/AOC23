#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

int main(){
    std::fstream file{"Input.txt"};
    std::string line{""};
    int sum{0};
    while (getline(file, line))
    {
        char fromLeft = line[line.find_first_of("123456789")];
        std::reverse(line.begin(), line.end());
        char fromRight = line[line.find_first_of("123456789")];
        auto result = std::string(1, fromLeft)+ fromRight;
        std::cout << "from left" <<  fromLeft << "from right: " << fromRight << std::endl;
        sum += std::stoi(result); 
    }
    std::cout << sum << std::endl;
}
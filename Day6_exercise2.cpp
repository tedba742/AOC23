#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

std::vector<long long> distanceVector;
std::vector<long long> timeVector;

long long  getCombinations(long long time, long long distance) {
	long long result = 0;
	long long distanceTraveled = 0;
	for (long long i = 1; i < time; i++) {
		distanceTraveled = (i * (time - i));

		if (distanceTraveled > distance) {
			result++;
		}
	}

	return result;
}
int main() {
	std::vector<long long> timeVector{ 53897698 };
	std::vector<long long> distanceVector{ 313109012141201 };
	std::vector<long long> resultVector{};

	for (size_t i = 0; i < distanceVector.size(); ++i) {
		resultVector.push_back(getCombinations(timeVector[i], distanceVector[i]));
		//int distanceTemp = distanceVector[i];

		//std::cout << "timeTemp: " << timeTemp << std::endl;

	
	}
	long long tmp = 1;
	for (size_t i = 0; i < resultVector.size(); i++) {
		tmp *= resultVector[i];

	}
	std::cout << "result:" << tmp << std::endl;
}
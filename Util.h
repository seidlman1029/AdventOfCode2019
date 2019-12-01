#pragma once
#include <vector>
#include <string>
#include <fstream>


namespace AOC {

std::vector<int> ReadLines(const char* file_name)
{
	std::ifstream input{file_name};
	if (!input.is_open())
		throw std::exception("reeeeeeeeeeeeeeeeeeeeeeeeeeeeee");

	std::vector<int> ints;
	for (std::string line; std::getline(input, line); )
		ints.emplace_back(std::stoi(line));
	return ints;
}

}

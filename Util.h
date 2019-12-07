#pragma once
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>


namespace AOC {

// pos == 0  corresponds to least significant digit of number
inline int GetDigitAtPos(int number, int pos)
{
	const auto modval = static_cast<int>(std::pow(10, pos + 1));
	const auto divval = static_cast<int>(std::pow(10, pos));

	return (number % modval) / divval;
}

std::vector<std::string> ReadLinesStrings(const char* file_name)
{
	std::ifstream input{file_name};
	if (!input.is_open())
		throw std::exception("aaaaaaaaaaaaaaa");

	std::vector<std::string> lines;
	for (std::string line; std::getline(input, line); )
		lines.emplace_back(line);
	return lines;
}

std::vector<int> ReadLinesInts(const char* file_name)
{
	std::ifstream input{file_name};
	if (!input.is_open())
		throw std::exception("aaaaaaaaaaaaaaa");

	std::vector<int> ints;
	for (std::string line; std::getline(input, line); )
		ints.emplace_back(std::stoi(line));
	return ints;
}

std::vector<int> ReadCommaSepInts(const char* file_name)
{
	std::ifstream input{file_name};
	if (!input.is_open())
		throw std::exception("aaaaaaaaaaaaaaa");

	std::vector<int> ints;
	for (std::string line; std::getline(input, line); ) {

		char* token = std::strtok(line.data(), ",");
		while (token != nullptr) {
			ints.emplace_back(std::stoi(token));
			token = std::strtok(nullptr, ",");
		}
	}

	return ints;
}

}

#pragma once
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>


namespace AOC {

// pos == 0  corresponds to least significant digit of number
inline int64_t GetDigitAtPos(int64_t number, int64_t pos)
{
	const auto modval = static_cast<int64_t>(std::pow(10, pos + 1));
	const auto divval = static_cast<int64_t>(std::pow(10, pos));

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

std::vector<int64_t> ReadLinesInts(const char* file_name)
{
	std::ifstream input{file_name};
	if (!input.is_open())
		throw std::exception("aaaaaaaaaaaaaaa");

	std::vector<int64_t> int64_ts;
	for (std::string line; std::getline(input, line); )
		int64_ts.emplace_back(std::stoi(line));
	return int64_ts;
}

std::vector<int64_t> ReadCommaSepInts(const char* file_name)
{
	std::ifstream input{file_name};
	if (!input.is_open())
		throw std::exception("aaaaaaaaaaaaaaa");

	std::vector<int64_t> ints;
	for (std::string line; std::getline(input, line); ) {

		char* token = std::strtok(line.data(), ",");
		while (token != nullptr) {
			ints.emplace_back(std::stoll(token));
			token = std::strtok(nullptr, ",");
		}
	}

	return ints;
}

}

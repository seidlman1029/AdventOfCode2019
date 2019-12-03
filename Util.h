#pragma once
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>


namespace AOC {

std::vector<int> ReadLines(const char* file_name)
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

#pragma once
#include <string>
#include <vector>
#include "Util.h"

namespace AOC {

struct Planet {
	std::string name;
	std::vector<Planet> orbits;
};

inline void Part1()
{
	std::vector<std::string> lines = ReadLinesStrings("./Inputs/day6.txt");

	for (const auto& line : lines)
		std::cout << line << std::endl;



}



}

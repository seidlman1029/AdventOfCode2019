#pragma once
#include <iostream>
#include <vector>
#include "Util.h"
#include "IntcodeComputer.h"


namespace AOC {

void Part1()
{
	const auto memory = ReadCommaSepInts("Inputs/day2.txt");
	std::cout << IntcodeComputer::Run(memory, 12, 2) << std::endl;
}

void Part2()
{
	const auto memory = ReadCommaSepInts("Inputs/day2.txt");
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			if (IntcodeComputer::Run(memory, i, j) == 19690720) {
				std::cout << 100 * i + j << std::endl;
				return;
			}
}

}

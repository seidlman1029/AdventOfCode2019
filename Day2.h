#pragma once
#include <iostream>
#include <vector>
#include "Util.h"
#include "IntcodeComputer.h"

namespace AOC {

void Part1()
{
	auto memory = ReadCommaSepInts("Inputs/day2.txt");
	memory[1] = 12;
	memory[2] = 2;
	std::cout << IntcodeComputer::Run(memory, 0) << std::endl;
}

void Part2()
{
	auto memory = ReadCommaSepInts("Inputs/day2.txt");
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			memory[1] = i;
			memory[2] = j;
			if (IntcodeComputer::Run(memory, 0) == 19690720) {
				std::cout << 100 * i + j << std::endl;
				return;
			}
		}
	}
}

}

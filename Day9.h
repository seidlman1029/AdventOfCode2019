#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include "Util.h"
#include "IntcodeComputer.h"

namespace AOC {

void Part1()
{
	auto memory = ReadCommaSepInts("Inputs/day9.txt");
	memory.resize(100000000);

	auto inputs = std::make_shared<std::queue<int64_t>>();
	inputs->emplace(1);

	auto outputs = std::make_shared<std::queue<int64_t>>();

	auto comp = IntcodeComputer{memory, inputs, outputs};
	comp.Run();

	while (!outputs->empty()) {
		std::cout << outputs->front() << std::endl;
		outputs->pop();
	}
}

void Part2()
{
	auto memory = ReadCommaSepInts("Inputs/day9.txt");
	memory.resize(100000000);

	auto inputs = std::make_shared<std::queue<int64_t>>();
	inputs->emplace(2);

	auto outputs = std::make_shared<std::queue<int64_t>>();

	auto comp = IntcodeComputer{memory, inputs, outputs};
	comp.Run();

	while (!outputs->empty()) {
		std::cout << outputs->front() << std::endl;
		outputs->pop();
	}
}


}

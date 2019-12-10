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
	auto program = ReadCommaSepInts("Inputs/day7.txt");
	int max = 0;

	// fuck it im lazy
	for (int i = 0; i < 5; i++) {
	for (int j = 0; j < 5; j++) {
	for (int k = 0; k < 5; k++) {
	for (int l = 0; l < 5; l++) {
	for (int m = 0; m < 5; m++) {
		std::unordered_set<int> phases{i, j, k, l, m};
		if (phases.size() != 5)
			continue;

		auto queue40 = std::make_shared<std::queue<int>>();
		auto queue01 = std::make_shared<std::queue<int>>();
		auto queue12 = std::make_shared<std::queue<int>>();
		auto queue23 = std::make_shared<std::queue<int>>();
		auto queue34 = std::make_shared<std::queue<int>>();

		queue40->emplace(i);
		queue01->emplace(j);
		queue12->emplace(k);
		queue23->emplace(l);
		queue34->emplace(m);

		queue40->emplace(0);

		auto cp0 = IntcodeComputer{program, queue40, queue01};
		auto cp1 = IntcodeComputer{program, queue01, queue12};
		auto cp2 = IntcodeComputer{program, queue12, queue23};
		auto cp3 = IntcodeComputer{program, queue23, queue34};
		auto cp4 = IntcodeComputer{program, queue34, queue40};

		while (!cp0.IsTerminated() ||
		       !cp1.IsTerminated() ||
		       !cp2.IsTerminated() ||
		       !cp3.IsTerminated() ||
		       !cp4.IsTerminated()) {
			       cp0.Run();
			       cp1.Run();
			       cp2.Run();
			       cp3.Run();
			       cp4.Run();
		}

		int out = queue40->front();
		max = out > max ? out : max;
	}
	}
	}
	}
	}


	std::cout << "max: " << max << std::endl;
}

void Part2()
{
	auto program = ReadCommaSepInts("Inputs/day7.txt");
	int max = 0;

	// fuck it im lazy
	for (int i = 5; i < 10; i++) {
	for (int j = 5; j < 10; j++) {
	for (int k = 5; k < 10; k++) {
	for (int l = 5; l < 10; l++) {
	for (int m = 5; m < 10; m++) {
		std::unordered_set<int> phases{i, j, k, l, m};
		if (phases.size() != 5)
			continue;

		auto queue40 = std::make_shared<std::queue<int>>();
		auto queue01 = std::make_shared<std::queue<int>>();
		auto queue12 = std::make_shared<std::queue<int>>();
		auto queue23 = std::make_shared<std::queue<int>>();
		auto queue34 = std::make_shared<std::queue<int>>();

		queue40->emplace(i);
		queue01->emplace(j);
		queue12->emplace(k);
		queue23->emplace(l);
		queue34->emplace(m);

		queue40->emplace(0);

		auto cp0 = IntcodeComputer{program, queue40, queue01};
		auto cp1 = IntcodeComputer{program, queue01, queue12};
		auto cp2 = IntcodeComputer{program, queue12, queue23};
		auto cp3 = IntcodeComputer{program, queue23, queue34};
		auto cp4 = IntcodeComputer{program, queue34, queue40};

		while (!cp0.IsTerminated() ||
		       !cp1.IsTerminated() ||
		       !cp2.IsTerminated() ||
		       !cp3.IsTerminated() ||
		       !cp4.IsTerminated()) {
			       cp0.Run();
			       cp1.Run();
			       cp2.Run();
			       cp3.Run();
			       cp4.Run();
		}

		int out = queue40->front();
		max = out > max ? out : max;
	}
	}
	}
	}
	}


	std::cout << "max: " << max << std::endl;
}


}

#pragma once
#include <iostream>
#include "Util.h"

namespace AOC {

void Part1()
{
	const auto masses = ReadLines("Inputs/day1pt1.txt");
	int fuel = 0;

	for (const int& mass : masses)
		fuel += (mass / 3) - 2;

	std::cout << fuel << std::endl;
}

void Part2()
{
	const auto masses = ReadLines("Inputs/day1pt1.txt");
	int total_fuel = 0;

	for (const int& mass : masses) {
		int module_fuel = (mass / 3) - 2;
		int fuel_fuel = (module_fuel / 3) - 2;

		while (fuel_fuel > 0) {
			module_fuel += fuel_fuel;
			fuel_fuel = (fuel_fuel / 3) - 2;
		}

		total_fuel += module_fuel;
	}

	std::cout << total_fuel << std::endl;
}

}

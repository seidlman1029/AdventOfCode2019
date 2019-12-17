#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <queue>
#include <unordered_set>
#include "Util.h"
#include "IntcodeComputer.h"

namespace AOC {

constexpr int64_t Empty = 0;
constexpr int64_t Wall = 1;
constexpr int64_t Block = 2;
constexpr int64_t Paddle = 3;
constexpr int64_t Ball = 4;

struct Tile {
	int64_t x;
	int64_t y;
	int64_t id;

	Tile(int64_t a, int64_t b, int64_t c) : x{a}, y{b}, id{c}{}

	// id purposely excluded from equality checks for hash set stuff
	bool operator==(const Tile& t) const
	{
		return this->x == t.x && this->y == t.y;
	}

	bool operator!=(const Tile& t) const
	{
		return this->x != t.x || this->y != t.y;
	}
};

class TileHash {
public:
	int64_t operator()(const Tile& t) const
	{
		return t.x * t.y;
	}
};



void Part1()
{
	auto program = ReadCommaSepInts("Inputs/day13.txt");
	program.resize(100000000);

	std::unordered_set<Tile, TileHash> tiles;

	auto inputs = std::make_shared<std::queue<int64_t>>();
	auto outputs = std::make_shared<std::queue<int64_t>>();
	auto comp = IntcodeComputer{program, inputs, outputs};

	while (!comp.IsTerminated()) {
		comp.Run();
	}

	int block_count = 0;
	while (!outputs->empty()) {
		auto x = outputs->front();
		outputs->pop();
		auto y = outputs->front();
		outputs->pop();
		auto id = outputs->front();
		outputs->pop();

		tiles.emplace(x, y, id);

		if (id == Block)
			block_count++;
	}

	std::cout << block_count << std::endl;
}

void Part2()
{
}


}

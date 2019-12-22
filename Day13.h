#pragma once
#include <iostream>
#include <conio.h>
#include <vector>
#include <sstream>
#include <queue>
#include <unordered_set>
#include "Util.h"
#include "IntcodeComputer.h"

namespace AOC {

constexpr int64_t OOB = -9001;
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

struct GameState {
	int64_t score{0};
	int64_t screen[200][200]{}; // [y][x] format

	GameState()
	{
		for (int i = 0; i < 200; i++)
			for (int j = 0; j < 200; j++)
				screen[i][j] = OOB;
	}
};

inline void PrintGameScreen(const GameState& game,
                            int minx,
                            int miny,
                            int maxx,
                            int maxy)
{
	for (int i = 0; i < 100; i++)
		std::cout << std::endl;


	for (int y = miny; y <= maxy; y++) {
		for (int x = minx; x <= maxx; x++) {
			switch (game.screen[y][x]) {
			case Empty:
				std::cout << " ";
				break;
			case Wall:
				std::cout << "|";
				break;
			case Block:
				std::cout << "B";
				break;
			case Paddle:
				std::cout << "=";
				break;
			case Ball:
				std::cout << "O";
				break;
			}
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
}

inline void Part2()
{
	auto program = ReadCommaSepInts("Inputs/day13.txt");
	program.resize(100000);
	program[0] = 2;

	GameState game;

	auto inputs = std::make_shared<std::queue<int64_t>>();
	auto outputs = std::make_shared<std::queue<int64_t>>();
	auto comp = IntcodeComputer{program, inputs, outputs};

	while (!comp.IsTerminated()) {
		comp.Run();

		int xball = -99999;
		int xpaddle = -999999;
		while (!outputs->empty()) {
			auto x = outputs->front();
			outputs->pop();
			auto y = outputs->front();
			outputs->pop();
			auto id = outputs->front();
			outputs->pop();

			if (x == -1 && y == 0) {
				game.score = id;
				continue;
			}

			if (id == Ball)
				xball = x;

			if (id == Paddle)
				xpaddle = x;


			game.screen[y][x] = id;
		}

		int input = 0;
		if (xball > xpaddle)
			input = 1;
		if (xball < xpaddle)
			input = -1;

		inputs->push(input);
	}

	PrintGameScreen(game, 0, 0, 50, 25);
	std::cout << "Score: " << game.score << std::endl;

}


}

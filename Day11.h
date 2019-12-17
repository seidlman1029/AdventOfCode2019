#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <queue>
#include <unordered_set>
#include "Util.h"
#include "IntcodeComputer.h"

namespace AOC {

class Robot {
private:
	constexpr static int64_t North = 0;
	constexpr static int64_t East = 1;
	constexpr static int64_t South = 2;
	constexpr static int64_t West = 3;

	int64_t direction_ = North;


	// origin is top-left corner. x increases to the right, y increases downward
	int64_t x_ = 0;
	int64_t y_ = 0;

public:
	int64_t X() { return x_; }
	int64_t Y() { return y_; }

	void TurnRight()
	{
		direction_ = (direction_ + 1) % 4;
	}

	void TurnLeft()
	{
		direction_--;
		if (direction_ < 0)
			direction_ = West;
	}

	void MoveOne()
	{
		switch (direction_) {
		case North:
			y_--;
			break;
		case East:
			x_++;
			break;
		case South:
			y_++;
			break;
		case West:
			x_--;
			break;
		default:
			throw std::exception("Aaaaaaaaaaaaaaaaaaaa");
		}
	}
};

constexpr int64_t Black = 0;
constexpr int64_t White = 1;
constexpr int64_t Undefined = -1;

struct Panel {
	int64_t x;
	int64_t y;
	int64_t color = Undefined;

	Panel(int64_t a, int64_t b, int64_t c) : x{a}, y{b}, color{c}{}

	// color purposely excluded from equality checks for hash set stuff
	bool operator==(const Panel& a) const
	{
		return this->x == a.x && this->y == a.y;
	}

	bool operator!=(const Panel& a) const
	{
		return this->x != a.x || this->y != a.y;
	}
};

class PanelHash {
public:
	int64_t operator()(const Panel& a) const
	{
		return a.x * a.y;
	}
};



void Part1()
{
	auto program = ReadCommaSepInts("Inputs/day11.txt");
	program.resize(100000000);

	std::unordered_set<Panel, PanelHash> painted_panels;

	auto inputs = std::make_shared<std::queue<int64_t>>();
	inputs->emplace(Black);

	auto outputs = std::make_shared<std::queue<int64_t>>();

	Robot robot{};
	auto comp = IntcodeComputer{program, inputs, outputs};

	while (!comp.IsTerminated()) {
		comp.Run();

		auto color_to_paint = outputs->front();
		outputs->pop();

		Panel panel{robot.X(), robot.Y(), color_to_paint};
		if (painted_panels.count(panel) == 1)
			painted_panels.erase(panel);
		painted_panels.insert(panel);

		auto direction_to_turn = outputs->front();
		outputs->pop();
		switch (direction_to_turn) {
		case 0:
			robot.TurnLeft();
			break;
		case 1:
			robot.TurnRight();
			break;
		default:
			throw std::exception("blarg");
		}

		robot.MoveOne();

		Panel next_panel{robot.X(), robot.Y(), Undefined};
		auto panel_search = painted_panels.find(next_panel);

		if (panel_search != painted_panels.end())
			inputs->emplace((*panel_search).color);
		else
			inputs->emplace(Black);
	}

	std::cout << painted_panels.size() << std::endl;
}

void Part2()
{
	auto program = ReadCommaSepInts("Inputs/day11.txt");
	program.resize(100000000);

	std::unordered_set<Panel, PanelHash> painted_panels;

	auto inputs = std::make_shared<std::queue<int64_t>>();
	inputs->emplace(White);

	auto outputs = std::make_shared<std::queue<int64_t>>();

	Robot robot{};
	auto comp = IntcodeComputer{program, inputs, outputs};

	while (!comp.IsTerminated()) {
		comp.Run();

		auto color_to_paint = outputs->front();
		outputs->pop();

		Panel panel{robot.X(), robot.Y(), color_to_paint};
		if (painted_panels.count(panel) == 1)
			painted_panels.erase(panel);
		painted_panels.insert(panel);

		auto direction_to_turn = outputs->front();
		outputs->pop();
		switch (direction_to_turn) {
		case 0:
			robot.TurnLeft();
			break;
		case 1:
			robot.TurnRight();
			break;
		default:
			throw std::exception("blarg");
		}

		robot.MoveOne();

		Panel next_panel{robot.X(), robot.Y(), Undefined};
		auto panel_search = painted_panels.find(next_panel);

		if (panel_search != painted_panels.end())
			inputs->emplace((*panel_search).color);
		else
			inputs->emplace(Black);
	}



	int64_t minx = 999999999;
	int64_t miny = 999999999;
	int64_t maxx = -9999999999;
	int64_t maxy = -9999999999;

	for (const auto& panel : painted_panels) {
		if (panel.x < minx)
			minx = panel.x;
		if (panel.y < miny)
			miny = panel.y;
		if (panel.x > maxx)
			maxx = panel.x;
		if (panel.y > maxy)
			maxy = panel.y;
	}

	for (int64_t y = miny; y <= maxy; y++) {
		for (int64_t x = minx; x <= maxx; x++) {
			int64_t color = Undefined;
			Panel panel{x, y, color};
			auto panel_search = painted_panels.find(panel);

			if (panel_search != painted_panels.end())
				color = ((*panel_search).color);
			else
				color = Black;

			if (color == Black)
				std::cout << "O";
			else
				std::cout << "X";

		}
		std::cout << std::endl;
	}

}


}

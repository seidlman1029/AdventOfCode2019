#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <numeric>
#include "Util.h"
#include "IntcodeComputer.h"

namespace AOC {

struct Asteroid {
	int x;
	int y;

	Asteroid(int a, int b) : x{a}, y{b}{}

	bool operator==(const Asteroid& a) const
	{
		return this->x == a.x && this->y == a.y;
	}

	bool operator!=(const Asteroid& a) const
	{
		return this->x != a.x || this->y != a.y;
	}

	std::string ToStr()
	{
		std::stringstream ss;
		ss << "x: " << this->x << ", y: " << this->y;
		return ss.str();
	}
};

class AsteroidHash {
public:
	int operator()(const Asteroid& a) const
	{
		return a.x * a.y;
	}
};

inline bool HasLOS(Asteroid a0,
                   const Asteroid& a1,
                   const std::unordered_set<Asteroid, AsteroidHash>& roid_map)
{
	if (a0 == a1)
		return true;

	int x_steps = a1.x - a0.x;
	int y_steps = a1.y - a0.y;
	int gcd = std::gcd(x_steps, y_steps);

	int x_hop = x_steps / gcd;
	int y_hop = y_steps / gcd;

	a0.x += x_hop;
	a0.y += y_hop;
	while(a0 != a1) {
		if (roid_map.count(a0) == 1) // there's another roid blocking LOS
			return false;

		a0.x += x_hop;
		a0.y += y_hop;
	}
	return true;
}

double RotationDegrees(Asteroid prev,
                       Asteroid next,
                       const Asteroid& laser_home)
{
	// normalize
	prev.x -= laser_home.x;
	next.x -= laser_home.x;
	prev.y -= laser_home.y;
	next.y -= laser_home.y;

	auto dot = (prev.x * next.x) + (prev.y * next.y);
	auto det = (prev.x * next.y) - (prev.y * next.x);

	auto angle = std::atan2(det, dot);
	return angle * 180 / 3.14159;
}

std::string PrintField(const std::unordered_set<Asteroid, AsteroidHash>& field,
                       const Asteroid& laser_home,
                       const Asteroid& prev_target,
                       const Asteroid& curr_target)
{
	constexpr int field_side_len = 25;

	std::stringstream ss;

	for (int y = 0; y < field_side_len; y++) {
		for (int x = 0; x < field_side_len; x++) {
			Asteroid temp{x, y};
			if (temp == laser_home)
				ss << "@";
			else if (temp == prev_target)
				ss << "+";
			else if (temp == curr_target)
				ss << "X";
			else if (field.count(temp) == 1)
				ss << "#";
			else
				ss << ".";
		}
		ss << std::endl;
	}
	return ss.str();
}

void Both()
{
	// pt 1
	auto lines = ReadLinesStrings("Inputs/day10.txt");
	std::unordered_set<Asteroid, AsteroidHash> asteroid_field;

	for (int y = 0; y < lines.size(); y++) {
		for (int x = 0; x < lines[y].length(); x++) {
			if (lines[y][x] == '#')
				asteroid_field.emplace(x, y);
		}
	}

	int max_roids = 0;
	Asteroid laser_home{0, 0};
	for (const auto& roid0 : asteroid_field) {
		int roidcount = 0;
		for (const auto& roid1 : asteroid_field) {
			if (HasLOS(roid0, roid1, asteroid_field))
				roidcount++;
		}

		if (roidcount > max_roids) {
			max_roids = roidcount;
			laser_home = roid0;
		}
	}

	std::cout << max_roids - 1 << std::endl;
	std::cout << "x: "<< laser_home.x << ", y: " << laser_home.y << std::endl;



	// pt 2
	asteroid_field.erase(laser_home);

	// find first asteroid lasered, i.e. the closest one immediately north
	Asteroid first_target = laser_home;
	while (true) { // meh
		first_target.y--;
		if (asteroid_field.count(first_target) == 1)
			break;
	}

	asteroid_field.erase(first_target);
	std::cout << "First asteroid blown up: " << first_target.ToStr() << std::endl;
	std::cout << PrintField(asteroid_field, laser_home, first_target, Asteroid{99999,99999});

	auto prev_target = first_target;
	for (int i = 1; i < 200; i++) {
		std::unordered_set<Asteroid, AsteroidHash> asteroids_in_los;
		for (const auto& roid : asteroid_field)
			if (HasLOS(laser_home, roid, asteroid_field))
				asteroids_in_los.insert(roid);


		double min_rotation = 99999999;
		Asteroid next_target{999999999, 999999999};

		for (const auto& roid : asteroids_in_los) {
			auto rotation = RotationDegrees(prev_target, roid, laser_home);
			if (rotation == 0)
				continue; // skip asteroid directly in line with prev_target if it exists

			if (rotation < 0)
				rotation += 360; // convert negative (ccw) rotation to positive (cw)

			if (rotation < min_rotation) {
				min_rotation = rotation;
				next_target = roid;
			}
		}

		asteroid_field.erase(next_target);

		std::cout << "Asteroid blown up: " << next_target.ToStr() << std::endl;
		std::cout << "Had rotation (degrees): " << min_rotation << std::endl;
		std::cout << PrintField(asteroid_field, laser_home, prev_target, next_target);

		prev_target = next_target;
	}
}

}

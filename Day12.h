#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <queue>
#include <unordered_set>
#include "Util.h"
#include "IntcodeComputer.h"

namespace AOC {

struct Moon {
	std::string name;
	int64_t x_pos;
	int64_t y_pos;
	int64_t z_pos;

	int64_t x_vel = 0;
	int64_t y_vel = 0;
	int64_t z_vel = 0;

	Moon(std::string n, int64_t x, int64_t y, int64_t z)
	  : name{std::move(n)}, x_pos{x}, y_pos{y}, z_pos{z}
	{}

	std::string ToStr()
	{
		std::stringstream ss;
		ss << "name: " << name << std::endl;
		ss << "x_pos: " << x_pos << std::endl;
		ss << "y_pos: " << y_pos << std::endl;
		ss << "z_pos: " << z_pos << std::endl;
		ss << "x_vel: " << x_vel << std::endl;
		ss << "y_vel: " << y_vel << std::endl;
		ss << "z_vel: " << z_vel << std::endl;
		return ss.str();
	}

	bool operator!=(const Moon& m) const
	{
		return this->name != m.name ||
		       this->x_pos != m.x_pos ||
		       this->y_pos != m.y_pos ||
		       this->z_pos != m.z_pos ||

		       this->x_vel != m.x_vel ||
		       this->y_vel != m.y_vel ||
		       this->z_vel != m.z_vel;
	}

	bool operator==(const Moon& m) const
	{
		return this->name == m.name &&
		       this->x_pos == m.x_pos &&
		       this->y_pos == m.y_pos &&
		       this->z_pos == m.z_pos &&

		       this->x_vel == m.x_vel &&
		       this->y_vel == m.y_vel &&
		       this->z_vel == m.z_vel;
	}
};

class MoonHash {
public:
	int operator()(const Moon& m) const
	{
		return m.x_pos * m.y_pos;
	}
};

void ApplyGravity(Moon& moon, const std::vector<Moon>& moons)
{
	for (const auto& other : moons) {
		if (moon.name == other.name)
			continue;

		//if (moon.x_pos < other.x_pos)
		//	moon.x_vel++;
		//else if (moon.x_pos > other.x_pos)
		//	moon.x_vel--;

		//if (moon.y_pos < other.y_pos)
		//	moon.y_vel++;
		//else if (moon.y_pos > other.y_pos)
		//	moon.y_vel--;

		if (moon.z_pos < other.z_pos)
			moon.z_vel++;
		else if (moon.z_pos > other.z_pos)
			moon.z_vel--;
	}
}

void ApplyVelocity(Moon& moon)
{
	//moon.x_pos += moon.x_vel;
	//moon.y_pos += moon.y_vel;
	moon.z_pos += moon.z_vel;
}

uint64_t GetPotentialEnergy(const Moon& moon)
{
	return std::abs(moon.x_pos) +
	       std::abs(moon.y_pos) +
	       std::abs(moon.z_pos);
}

uint64_t GetKineticEnergy(const Moon& moon)
{
	return std::abs(moon.x_vel) +
	       std::abs(moon.y_vel) +
	       std::abs(moon.z_vel);
}

uint64_t GetTotalEnergy(const Moon& moon)
{
	return GetPotentialEnergy(moon) * GetKineticEnergy(moon);
}

void Part1()
{
	std::vector<Moon> moons;
	moons.emplace_back("Io", 1, -4, 3);
	moons.emplace_back("Europa", -14, 9, -4);
	moons.emplace_back("Ganymede", -4, -6, 7);
	moons.emplace_back("Callisto", 6, -9, -11);

	for (int i = 0; i < 1000; i++) {
		for (auto& moon : moons)
			ApplyGravity(moon, moons);

		for (auto& moon : moons)
			ApplyVelocity(moon);
	}

	uint64_t total_energy = 0;
	for (const auto& moon : moons)
		total_energy += GetTotalEnergy(moon);

	std::cout << total_energy << std::endl;

}

void Part2()
{
	std::vector<Moon> moons;
	moons.emplace_back("Io", 1, -4, 3);
	moons.emplace_back("Europa", -14, 9, -4);
	moons.emplace_back("Ganymede", -4, -6, 7);
	moons.emplace_back("Callisto", 6, -9, -11);

	auto init_state = moons;

	for (uint64_t i = 0; i < 10000000000; i++) {
		for (auto& moon : moons)
			ApplyGravity(moon, moons);

		for (auto& moon : moons)
			ApplyVelocity(moon);

		bool repeat = true;
		for (int i = 0; i < 4; i++) {
			if (moons[i].z_pos != init_state[i].z_pos || moons[i].z_vel != 0) {
				repeat = false;
				break;
			}
		}
		if (repeat)
			std::cout << "all z's repeat on inter: " << i << std::endl;

	}

}



}

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

		if (moon.x_pos < other.x_pos)
			moon.x_vel++;
		else if (moon.x_pos > other.x_pos)
			moon.x_vel--;

		if (moon.y_pos < other.y_pos)
			moon.y_vel++;
		else if (moon.y_pos > other.y_pos)
			moon.y_vel--;

		if (moon.z_pos < other.z_pos)
			moon.z_vel++;
		else if (moon.z_pos > other.z_pos)
			moon.z_vel--;
	}
}

void ApplyVelocity(Moon& moon)
{
	moon.x_pos += moon.x_vel;
	moon.y_pos += moon.y_vel;
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

struct MoonMinMaxTracker {
	std::string name;
	uint64_t reset_iterations;
	uint64_t iteration_count;


	int64_t min_x_pos;
	int64_t min_y_pos;
	int64_t min_z_pos;
	int64_t min_x_vel;
	int64_t min_y_vel;
	int64_t min_z_vel;

	int64_t max_x_pos;
	int64_t max_y_pos;
	int64_t max_z_pos;
	int64_t max_x_vel;
	int64_t max_y_vel;
	int64_t max_z_vel;

	void Reset()
	{
		iteration_count = 0;

		min_x_pos = 999999999999;
		min_y_pos = 999999999999;
		min_z_pos = 999999999999;
		min_x_vel = 999999999999;
		min_y_vel = 999999999999;
		min_z_vel = 999999999999;

		max_x_pos = -9999999999999;
		max_y_pos = -9999999999999;
		max_z_pos = -9999999999999;
		max_x_vel = -9999999999999;
		max_y_vel = -9999999999999;
		max_z_vel = -9999999999999;
	}

	void PrintTracking()
	{
		std::cout << "Values for the last " << iteration_count << " iterations of moon " << name << ": " << std::endl;

		std::cout << "min_x_pos: " << min_x_pos << std::endl;
		std::cout << "min_y_pos: " << min_y_pos << std::endl;
		std::cout << "min_z_pos: " << min_z_pos << std::endl;
		std::cout << "min_x_vel: " << min_x_vel << std::endl;
		std::cout << "min_y_vel: " << min_y_vel << std::endl;
		std::cout << "min_z_vel: " << min_z_vel << std::endl;

		std::cout << "max_x_pos: " << max_x_pos << std::endl;
		std::cout << "max_y_pos: " << max_y_pos << std::endl;
		std::cout << "max_z_pos: " << max_z_pos << std::endl;
		std::cout << "max_x_vel: " << max_x_vel << std::endl;
		std::cout << "max_y_vel: " << max_y_vel << std::endl;
		std::cout << "max_z_vel: " << max_z_vel << std::endl;
	}

	MoonMinMaxTracker(Moon m, uint64_t ri)
	  : name{m.name},
	    reset_iterations{ri}
	{
		Reset();
	}

	void Track(const Moon& moon)
	{
		if (moon.x_pos < min_x_pos)
			min_x_pos = moon.x_pos;
		if (moon.y_pos < min_y_pos)
			min_y_pos = moon.y_pos;
		if (moon.z_pos < min_z_pos)
			min_z_pos = moon.z_pos;
		if (moon.x_vel < min_x_vel)
			min_x_vel = moon.x_vel;
		if (moon.y_vel < min_y_vel)
			min_y_vel = moon.y_vel;
		if (moon.z_vel < min_z_vel)
			min_z_vel = moon.z_vel;

		if (moon.x_pos > max_x_pos)
			max_x_pos = moon.x_pos;
		if (moon.y_pos > max_y_pos)
			max_y_pos = moon.y_pos;
		if (moon.z_pos > max_z_pos)
			max_z_pos = moon.z_pos;
		if (moon.x_vel > max_x_vel)
			max_x_vel = moon.x_vel;
		if (moon.y_vel > max_y_vel)
			max_y_vel = moon.y_vel;
		if (moon.z_vel > max_z_vel)
			max_z_vel = moon.z_vel;

		if (++iteration_count > reset_iterations) {
			PrintTracking();
			Reset();
		}
	}

};

void Part2()
{
	constexpr uint64_t iterations = 100000000;
	std::vector<Moon> moons;

	moons.emplace_back("Io", 1, -4, 3);
	moons.emplace_back("Europa", -14, 9, -4);
	moons.emplace_back("Ganymede", -4, -6, 7);
	moons.emplace_back("Callisto", 6, -9, -11);

	//MoonMinMaxTracker mmmt_io{moons[0], 10000000};
	//MoonMinMaxTracker mmmt_eu{moons[1], 10000000};
	//MoonMinMaxTracker mmmt_gm{moons[2], 10000000};
	//MoonMinMaxTracker mmmt_cl{moons[3], 10000000};

	//uint64_t last_iter_seen = 0;
	//uint64_t last_iter_seen2 = 0;
	std::unordered_set<Moon, MoonHash> zpos_maxes;

	for (uint64_t i = 0; i < iterations; i++) {
		for (auto& moon : moons)
			ApplyGravity(moon, moons);

		for (auto& moon : moons)
			ApplyVelocity(moon);

		if (moons[0].z_pos == 1509) {
			if (zpos_maxes.count(moons[0]) == 1)
				std::cout << "Zomg a repeat of the following moon on iteration " << i << std::endl << moons[0].ToStr() << std::endl;
			else
				zpos_maxes.insert(moons[0]);
		}
		//mmmt_io.Track(moons[0]);
		//mmmt_eu.Track(moons[1]);
		//mmmt_gm.Track(moons[2]);
		//mmmt_cl.Track(moons[3]);
	}

	std::cout << "Donezo" << std::endl;
}



}

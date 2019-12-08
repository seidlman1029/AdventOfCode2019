#pragma once
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "Util.h"

namespace AOC {

struct Planet {
	std::string name{};
	std::vector<std::shared_ptr<Planet>> orbits{};
};

std::unordered_map<std::string, std::unordered_set<std::string>> cached_orbits;
inline std::unordered_set<std::string> GetOrbits(std::shared_ptr<Planet> planet)
{
	if (cached_orbits.count(planet->name) == 1)
		return cached_orbits[planet->name];

	std::unordered_set<std::string> orbitee_names;

	for (const auto& orbitee : planet->orbits) {
		orbitee_names.emplace(orbitee->name);

		for (const auto& sub_orbitee : GetOrbits(orbitee))
			orbitee_names.emplace(sub_orbitee);
	}

	cached_orbits[planet->name] = orbitee_names;
	return orbitee_names;
}

inline void Part1()
{
	std::vector<std::string> lines = ReadLinesStrings("./Inputs/day6.txt");

	std::unordered_set<std::string> planet_names;
	std::unordered_map<std::string, std::shared_ptr<Planet>> planets;

	for (const auto& line : lines) {
		planet_names.emplace(line.substr(0, 3));
		planet_names.emplace(line.substr(4));
	}

	for (const auto& p : planet_names)
		planets[p] = std::make_shared<Planet>(Planet{p});

	for (const auto& line : lines) {
		const auto orbitee = line.substr(0, 3);
		const auto orbiter = line.substr(4);
		planets[orbiter]->orbits.emplace_back(planets[orbitee]);
	}

	int total_orbits = 0;
	for (const auto& p : planet_names)
		total_orbits += GetOrbits(planets[p]).size();

	std::cout << total_orbits << std::endl;

}

inline void GetShortestPath(std::shared_ptr<Planet> current_planet,
	                    std::unordered_set<std::string> planets_hopped,
	                    int& min_path_found)
{
	planets_hopped.emplace(current_planet->name);
	if (planets_hopped.size() > min_path_found)
		return;

	for (const auto& orbit : current_planet->orbits) {
		if (planets_hopped.count(orbit->name) == 1) {
			continue;
		}
		else if (orbit->name == "SAN" && min_path_found > planets_hopped.size()) {
			min_path_found = planets_hopped.size();
			return;
		} else {
			GetShortestPath(orbit, planets_hopped, min_path_found);
		}
	}
}

inline void Part2()
{
	std::vector<std::string> lines = ReadLinesStrings("./Inputs/day6.txt");

	std::unordered_set<std::string> planet_names;
	std::unordered_map<std::string, std::shared_ptr<Planet>> planets;

	for (const auto& line : lines) {
		planet_names.emplace(line.substr(0, 3));
		planet_names.emplace(line.substr(4));
	}

	for (const auto& p : planet_names)
		planets[p] = std::make_shared<Planet>(Planet{p});

	for (const auto& line : lines) {
		const auto orbitee = line.substr(0, 3);
		const auto orbiter = line.substr(4);
		planets[orbiter]->orbits.emplace_back(planets[orbitee]);
		planets[orbitee]->orbits.emplace_back(planets[orbiter]);
	}

	auto current_planet = planets["YOU"];
	std::unordered_set<std::string> planets_hopped;
	int min_path = 999999999;

	GetShortestPath(current_planet, planets_hopped, min_path);

	std::cout << min_path - 2 << std::endl;

}




}

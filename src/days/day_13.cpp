#include "day_13.hpp"

#include <algorithm>
#include <iostream>
#include <numeric>

void aoc::day_13::part_one()
{
	const auto lines = m_input.strings();
	const unsigned long start_time = std::stoul(lines.at(0));

	std::vector<unsigned long> buses;
	auto buses_str = lines.at(1);
	size_t next_pos = 0;
	while (next_pos < buses_str.size())
	{
		buses_str = buses_str.substr(next_pos);
		if (buses_str.at(0) == 'x')
		{
			next_pos = 2;
			continue;
		}
		buses.emplace_back(std::stoul(buses_str, &next_pos));
		++next_pos;
	}

	std::sort(buses.begin(), buses.end(), [start_time](unsigned long a, unsigned long b) {
		return time_to_next(start_time, a) < time_to_next(start_time, b);
		});

	std::cout << buses.at(0) * time_to_next(start_time, buses.at(0)) << std::endl;
}

void aoc::day_13::part_two()
{
	const auto lines = m_input.strings();

	std::vector<unsigned long> buses;
	auto buses_str = lines.at(1);
	size_t next_pos = 0;
	while (next_pos < buses_str.size())
	{
		buses_str = buses_str.substr(next_pos);
		if (buses_str.at(0) == 'x')
		{
			buses.emplace_back(0);
			next_pos = 2;
			continue;
		}
		buses.emplace_back(std::stoul(buses_str, &next_pos));
		++next_pos;
	}

	size_t time = buses.at(0);
	size_t lcm = time;
	for (size_t i = 1; i < buses.size(); ++i)
	{
		const auto& bus = buses.at(i);
		if (bus == 0) continue;

		while ((time + i) % bus != 0)
		{
			time += lcm;
		}

		lcm = std::lcm(lcm, bus);
	}

	std::cout << time << std::endl;
}

unsigned long aoc::day_13::time_to_next(const unsigned long& curr_time, const unsigned long& frequency)
{
	return (frequency - (curr_time % frequency)) % frequency;
}

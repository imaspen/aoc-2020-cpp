#include "day_06.hpp"

#include <array>
#include <iostream>

void aoc::day_06::part_one()
{
	const auto raw_lines = m_input.strings(true);
	std::vector<std::string> lines;

	std::string next_line = "";
	for (const auto &line : raw_lines)
	{
		if (line == "")
		{
			lines.emplace_back(next_line);
			next_line = "";
		}
		else
		{
			next_line += line;
		}
	}

	std::array<bool, 26> answers;
	u_long count = 0;
	for (const auto &line : lines)
	{
		answers.fill(0);

		for (const auto &c : line)
		{
			answers.at(c - 'a') = true;
		}

		for (const auto &b : answers)
		{
			count += b;
		}
	}

	std::cout << count << std::endl;
}

void aoc::day_06::part_two()
{
	const auto raw_lines = m_input.strings(true);
	std::vector<std::vector<std::string>> groups;

	std::vector<std::string> next_group;
	for (const auto &line : raw_lines)
	{
		if (line == "")
		{
			groups.emplace_back(next_group);
			next_group = std::vector<std::string>();
		}
		else
		{
			next_group.emplace_back(line);
		}
	}

	std::array<size_t, 26> answers;
	u_long count = 0;
	for (const auto &group : groups)
	{
		answers.fill(0);

		for (const auto &line : group)
		{
			for (const auto &c : line)
			{
				answers.at(c - 'a') += 1;
			}
		}

		for (const auto &b : answers)
		{
			count += b == group.size();
		}
	}

	std::cout << count << std::endl;
}

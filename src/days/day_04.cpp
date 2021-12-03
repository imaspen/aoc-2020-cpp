#include "day_04.hpp"

#include <iostream>

#include "../objects/passport.hpp"

void aoc::day_04::part_one()
{
	const auto raw_lines = m_input.strings(true);

	std::vector<std::string> lines;

	std::string current_line;
	for (const auto &line : raw_lines)
	{
		current_line += " " + line;
		if (line == "")
		{
			lines.push_back(current_line.substr(1));
			current_line = "";
		}
	}

	size_t count = 0;
	for (const auto &line : lines)
	{
		++count;
		for (const auto &field : aoc::passport::REQUIRED_FIELDS)
		{
			const auto pos = line.find(field);
			if (pos == std::string::npos)
			{
				--count;
				break;
			}
		}
	}

	std::cout << count << std::endl;
}

void aoc::day_04::part_two()
{
	const auto raw_lines = m_input.strings(true);

	std::vector<std::string> lines;

	std::string current_line;
	for (const auto &line : raw_lines)
	{
		current_line += " " + line;
		if (line == "")
		{
			lines.push_back(current_line.substr(1));
			current_line = "";
		}
	}

	size_t valid_count = 0;
	for (const auto &line : lines)
	{
		try
		{
			aoc::passport::from_string(line);
			++valid_count;
		}
		catch (aoc::missing_required_field_exception)
		{
		}
		catch (aoc::invalid_required_field_exception)
		{
		}
	}

	std::cout << valid_count << std::endl;
}

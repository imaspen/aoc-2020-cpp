#include "day_03.hpp"

#include <iostream>

void aoc::day_03::part_one()
{
	const auto lines = m_input.strings();

	size_t width = lines.at(0).size();

	size_t x = 0;
	size_t y = 0;

	u_long count = 0;
	while (y < lines.size())
	{
		if (lines.at(y).at(x) == '#')
		{
			++count;
		}

		x += 3;
		x = x % width;
		y += 1;
	}

	std::cout << count << std::endl;
}

void aoc::day_03::part_two()
{
	const auto lines = m_input.strings();

	size_t width = lines.at(0).size();

	std::vector<std::tuple<size_t, size_t>> slopes({
		std::make_tuple(1, 1),
		std::make_tuple(3, 1),
		std::make_tuple(5, 1),
		std::make_tuple(7, 1),
		std::make_tuple(1, 2),
	});

	u_long res = 1;

	for (const auto &slope : slopes)
	{
		size_t x = 0, y = 0, dx = 0, dy = 0, count = 0;
		std::tie(dx, dy) = slope;

		while (y < lines.size())
		{
			if (lines.at(y).at(x) == '#')
			{
				++count;
			}

			x += dx;
			x = x % width;
			y += dy;
		}

		res *= count;
	}

	std::cout << res << std::endl;
}

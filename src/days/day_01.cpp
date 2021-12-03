#include "day_01.hpp"

#include <iostream>

void aoc::day_01::part_one()
{
	const auto lines = m_input.ints();

	for (size_t i = 0; i < lines.size(); ++i)
	{
		const auto a = lines.at(i);
		for (size_t j = i + 1; j < lines.size(); ++j)
		{
			const auto b = lines.at(j);
			if (a + b == 2020)
			{
				std::cout << a * b << std::endl;
				return;
			}
		}
	}
}

void aoc::day_01::part_two()
{
	const auto lines = m_input.ints();

	for (size_t i = 0; i < lines.size(); ++i)
	{
		const auto a = lines.at(i);
		for (size_t j = i + 1; j < lines.size(); ++j)
		{
			const auto b = lines.at(j);
			if (a + b >= 2020)
			{
				continue;
			}
			for (size_t k = j + 1; k < lines.size(); ++k)
			{
				const auto c = lines.at(k);
				if (a + b + c == 2020)
				{
					std::cout << a * b * c << std::endl;
					return;
				}
			}
		}
	}
}

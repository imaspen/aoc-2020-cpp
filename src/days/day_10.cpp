#include "day_10.hpp"

#include <iostream>

void aoc::day_10::part_one()
{
	auto nums = m_input.ints();
	nums.emplace_back(0);
	std::sort(nums.begin(), nums.end());
	nums.emplace_back(nums.back() + 3);

	size_t ones = 0, threes = 0;
	int last = nums.at(0);
	for (size_t i = 1; i < nums.size(); ++i)
	{
		const auto& num = nums.at(i);
		const auto dif = num - last;

		if (dif == 1)
		{
			++ones;
		}
		else if (dif == 3)
		{
			++threes;
		}

		last = num;
	}

	std::cout << ones * threes << std::endl;
}

int aoc::day_10::variants_for_count(int count)
{
	switch (count)
	{
	case 0: return 1;
	case 1: return 1;
	case 2: return 2;
	case 3: return 4;
	case 4: return 7;
	default: throw std::exception();
	}
}

void aoc::day_10::part_two()
{
	auto nums = m_input.ints();
	nums.emplace_back(0);
	std::sort(nums.begin(), nums.end());
	nums.emplace_back(nums.back() + 3);

	size_t count = 0;
	u_long variants = 1;
	for (size_t i = 1; i < nums.size(); ++i)
	{
		const auto dif = nums.at(i) - nums.at(i - 1);
		if (dif == 1)
		{
			++count;
		}
		else if (dif == 3)
		{
			variants *= variants_for_count(count);
			count = 0;
		}
	}

	std::cout << variants << std::endl;
}

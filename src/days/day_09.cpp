#include "day_09.hpp"

#include <iostream>
#include <map>
#include <queue>
#include <vector>

long aoc::day_09::get_problem_number()
{
	const size_t count = m_input.test ? 5 : 25;
	std::vector<long> _nums = m_input.longs();
	std::queue<long> nums;
	std::vector<long> previous_nums;
	std::map<long, long> previous_nums_set;

	for (const auto& num : _nums)
	{
		nums.push(num);
	}

	for (size_t i = 0; i < count; ++i)
	{
		const auto& num = nums.front();
		nums.pop();
		previous_nums.emplace_back(num);
		if (previous_nums_set.count(num) == 0)
		{
			previous_nums_set.emplace(num, 1);
		}
		else
		{
			++previous_nums_set.at(num);
		}
	}

	while (!nums.empty())
	{
		bool found_pair = false;
		const auto& num = nums.front();
		nums.pop();

		for (const auto& previous_num : previous_nums)
		{
			if (previous_nums_set.count(num - previous_num) == 1)
			{
				const auto count = previous_nums_set.at(num - previous_num);
				if (num - previous_num != previous_num || count > 1)
				{
					found_pair = true;
					break;
				}
			}
		}

		if (!found_pair)
		{
			return num;
		}

		const auto to_remove = previous_nums.front();
		previous_nums.erase(previous_nums.begin());
		const auto new_count = --previous_nums_set.at(to_remove);
		if (new_count == 0)
		{
			previous_nums_set.erase(to_remove);
		}
		previous_nums.emplace_back(num);
		if (previous_nums_set.count(num) == 0)
		{
			previous_nums_set.emplace(num, 1);
		}
		else
		{
			++previous_nums_set.at(num);
		}
	}

	return 0;
}

void aoc::day_09::part_one()
{
	std::cout << aoc::day_09::get_problem_number() << std::endl;
}

void aoc::day_09::part_two()
{
	const auto target = aoc::day_09::get_problem_number();
	auto nums = m_input.longs();
	for (size_t i = 0; i < nums.size(); ++i)
	{
		long total = nums.at(i), min = nums.at(i), max = nums.at(i);
		for (size_t j = i + 1; j < nums.size(); ++j)
		{
			const auto to_add = nums.at(j);
			total += to_add;
			if (to_add > max)
			{
				max = to_add;
			}
			if (to_add < min)
			{
				min = to_add;
			}
			if (total >= target)
			{
				break;
			}
		}
		if (total == target)
		{
			std::cout << min + max << std::endl;
			return;
		}
	}
}

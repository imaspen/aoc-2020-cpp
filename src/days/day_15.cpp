#include "day_15.hpp"

#include <iostream>
#include <map>

void aoc::day_15::part_one()
{
	std::cout << run(2020) << std::endl;
}

void aoc::day_15::part_two()
{
	std::cout << run(30000000) << std::endl;
}

size_t aoc::day_15::run(const size_t& run_to)
{
	std::map<size_t, size_t> last_seen_at;
	const auto ints = m_input.csv_ints();
	for (size_t i = 0; i < ints.size() - 1; ++i)
	{
		last_seen_at.insert_or_assign(static_cast<size_t>(ints.at(i)), i + 1);
	}

	auto last_seen = ints.back();
	size_t pos = ints.size();

	while (pos < run_to)
	{
		size_t next_last_seen;
		if (last_seen_at.count(last_seen) == 0)
		{
			next_last_seen = 0;
		}
		else
		{
			const auto at = last_seen_at.at(last_seen);
			next_last_seen = pos - at;
		}
		last_seen_at.insert_or_assign(last_seen, pos);
		++pos;
		last_seen = next_last_seen;
	}

	return last_seen;
}

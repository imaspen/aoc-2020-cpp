#include "day_05.hpp"

#include <algorithm>
#include <iostream>

std::tuple<u_int, u_int> aoc::day_05::get_row_column(const std::string &line)
{
	u_int minRow = 0, minColumn = 0, numRows = 128, numColumns = 8;

	for (const auto &c : line)
	{
		switch (c)
		{
		case 'B':
			minRow += numRows / 2;
		case 'F':
			numRows /= 2;
			break;
		case 'R':
			minColumn += numColumns / 2;
		case 'L':
			numColumns /= 2;
			break;
		default:
			throw aoc::unrecognized_dir_exception(c);
		}
	}

	return std::make_tuple(minRow, minColumn);
}

void aoc::day_05::part_one()
{
	const auto lines = m_input.strings();

	u_long max_id = 0;
	for (const auto &line : lines)
	{
		u_int row, column;
		std::tie(row, column) = get_row_column(line);
		const u_long id = (row * 8) + column;

		if (id > max_id)
		{
			max_id = id;
		}
	}

	std::cout << max_id << std::endl;
}

void aoc::day_05::part_two()
{
	const auto lines = m_input.strings();
	std::vector<u_long> ids(lines.size());

	for (size_t i = 0; i < lines.size(); ++i)
	{
		const auto &line = lines.at(i);

		u_int row, column;
		std::tie(row, column) = get_row_column(line);
		const u_long id = (row * 8) + column;

		ids.at(i) = id;
	}

	std::sort(ids.begin(), ids.end());

	auto last_id = ids.at(0);
	for (size_t i = 1; i < ids.size(); ++i)
	{
		const auto &id = ids.at(i);
		if (id - 1 != last_id)
		{
			break;
		}
		last_id = id;
	}

	std::cout << last_id + 1 << std::endl;
}

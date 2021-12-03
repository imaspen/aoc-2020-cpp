#include "day_02.hpp"

#include <iostream>
#include <string>

void aoc::day_02::part_one()
{
	const auto lines = m_input.strings();
	uint valid_count = 0;
	for (const auto &line : lines)
	{
		const auto count_def_seperator = line.find('-');
		const auto end_of_count_def = line.find(' ');
		const auto end_of_char_def = line.find(": ");

		const auto min_count = std::stoul(line.substr(0, count_def_seperator));
		const auto max_count = std::stoul(line.substr(count_def_seperator + 1, end_of_count_def - count_def_seperator - 1));
		const auto required_char = line.substr(end_of_count_def + 1, end_of_char_def - end_of_count_def - 1).at(0);
		const auto password = line.substr(end_of_char_def + 2);

		u_long count = 0;
		size_t pos = -1;
		while (true)
		{
			pos = password.find(required_char, pos + 1);
			if (pos == std::string::npos)
			{
				break;
			}
			count++;
		}

		if (count >= min_count && count <= max_count)
		{
			valid_count++;
		}
	}

	std::cout << valid_count << std::endl;
}

void aoc::day_02::part_two()
{
	const auto lines = m_input.strings();
	uint valid_count = 0;
	for (const auto &line : lines)
	{
		const auto count_def_seperator = line.find('-');
		const auto end_of_count_def = line.find(' ');
		const auto end_of_char_def = line.find(": ");

		const auto i = std::stoul(line.substr(0, count_def_seperator));
		const auto j = std::stoul(line.substr(count_def_seperator + 1, end_of_count_def - count_def_seperator - 1));
		const auto required_char = line.substr(end_of_count_def + 1, end_of_char_def - end_of_count_def - 1).at(0);
		const auto password = line.substr(end_of_char_def + 2);

		const auto char_i = password.at(i - 1);
		const auto char_j = password.at(j - 1);

		if ((char_i == required_char && char_j != required_char) || (char_i != required_char && char_j == required_char))
		{
			++valid_count;
		}
	}

	std::cout << valid_count << std::endl;
}

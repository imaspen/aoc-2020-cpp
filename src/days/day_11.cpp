#include "day_11.hpp"

#include <iostream>

aoc::day_11::day_11(const aoc::input& input) : day(input)
{
	const auto strings = m_input.strings();
	m_height = strings.size();
	m_width = strings.at(0).size();

	for (const auto& line : strings)
	{
		std::vector<space> row;
		for (const auto& c : line)
		{
			row.emplace_back(static_cast<space>(c));
		}
		m_spaces.emplace_back(row);
	}
}

void aoc::day_11::part_one()
{
	bool any_changes = true;
	while (any_changes)
	{
		any_changes = false;
		auto next_spaces = m_spaces;
		for (size_t y = 0; y < m_height; ++y)
		{
			for (size_t x = 0; x < m_width; ++x)
			{
				const auto& space = m_spaces.at(y).at(x);
				if (space == space::OCCUPIED)
				{
					if (adjacent_occupied(x, y) >= 4)
					{
						any_changes = true;
						next_spaces.at(y).at(x) = space::EMPTY;
					}
				}
				else if (space == space::EMPTY)
				{
					if (adjacent_occupied(x, y) == 0)
					{
						any_changes = true;
						next_spaces.at(y).at(x) = space::OCCUPIED;
					}
				}
			}
		}
		m_spaces = next_spaces;
	}

	int count = 0;
	for (const auto& row : m_spaces)
	{
		for (const auto& space : row)
		{
			count += space == space::OCCUPIED;
		}
	}

	std::cout << count << std::endl;
}

void aoc::day_11::part_two()
{
	bool any_changes = true;
	while (any_changes)
	{
		any_changes = false;
		auto next_spaces = m_spaces;
		for (size_t y = 0; y < m_height; ++y)
		{
			for (size_t x = 0; x < m_width; ++x)
			{
				const auto space = m_spaces.at(y).at(x);
				if (space == space::OCCUPIED)
				{
					if (visible_occupied(x, y) >= 5)
					{
						any_changes = true;
						next_spaces.at(y).at(x) = space::EMPTY;
					}
				}
				else if (space == space::EMPTY)
				{
					if (visible_occupied(x, y) == 0)
					{
						any_changes = true;
						next_spaces.at(y).at(x) = space::OCCUPIED;
					}
				}
			}
		}
		m_spaces = next_spaces;
	}

	int count = 0;
	for (const auto& row : m_spaces)
	{
		for (const auto& space : row)
		{
			count += space == space::OCCUPIED;
		}
	}

	std::cout << count << std::endl;
}

int aoc::day_11::adjacent_occupied(size_t x, size_t y)
{
	int count = 0;
	bool is_left = x == 0;
	bool is_right = x == (m_width - 1);
	bool is_top = y == 0;
	bool is_bottom = y == (m_height - 1);

	if (!is_top)
	{
		if (!is_left)
		{
			count += m_spaces.at(y - 1).at(x - 1) == space::OCCUPIED;
		}
		count += m_spaces.at(y - 1).at(x) == space::OCCUPIED;
		if (!is_right)
		{
			count += m_spaces.at(y - 1).at(x + 1) == space::OCCUPIED;
		}
	}
	if (!is_left)
	{
		count += m_spaces.at(y).at(x - 1) == space::OCCUPIED;
	}
	if (!is_right)
	{
		count += m_spaces.at(y).at(x + 1) == space::OCCUPIED;
	}
	if (!is_bottom)
	{
		if (!is_left)
		{
			count += m_spaces.at(y + 1).at(x - 1) == space::OCCUPIED;
		}
		count += m_spaces.at(y + 1).at(x) == space::OCCUPIED;
		if (!is_right)
		{
			count += m_spaces.at(y + 1).at(x + 1) == space::OCCUPIED;
		}
	}

	return count;
}

int aoc::day_11::visible_occupied(size_t sx, size_t sy)
{
	int count = 0;
	// look up
	for (size_t y = sy - 1; y < m_height; --y)
	{
		const auto space = m_spaces.at(y).at(sx);
		if (space != space::FLOOR)
		{
			count += space == space::OCCUPIED;
			break;
		}
	}
	// look down
	for (size_t y = sy + 1; y < m_height; ++y)
	{
		const auto space = m_spaces.at(y).at(sx);
		if (space != space::FLOOR)
		{
			count += space == space::OCCUPIED;
			break;
		}
	}
	// look left
	for (size_t x = sx - 1; x < m_width; --x)
	{
		const auto space = m_spaces.at(sy).at(x);
		if (space != space::FLOOR)
		{
			count += space == space::OCCUPIED;
			break;
		}
	}
	// look right
	for (size_t x = sx + 1; x < m_width; ++x)
	{
		const auto space = m_spaces.at(sy).at(x);
		if (space != space::FLOOR)
		{
			count += space == space::OCCUPIED;
			break;
		}
	}
	// look up + left
	for (size_t x = sx - 1, y = sy - 1; x < m_width && y < m_height; --x, --y)
	{
		const auto space = m_spaces.at(y).at(x);
		if (space != space::FLOOR)
		{
			count += space == space::OCCUPIED;
			break;
		}
	}
	// look up + right
	for (size_t x = sx + 1, y = sy - 1; x < m_width && y < m_height; ++x, --y)
	{
		const auto space = m_spaces.at(y).at(x);
		if (space != space::FLOOR)
		{
			count += space == space::OCCUPIED;
			break;
		}
	}
	// look down + left
	for (size_t x = sx - 1, y = sy + 1; x < m_width && y < m_height; --x, ++y)
	{
		const auto space = m_spaces.at(y).at(x);
		if (space != space::FLOOR)
		{
			count += space == space::OCCUPIED;
			break;
		}
	}
	// look down + right
	for (size_t x = sx + 1, y = sy + 1; x < m_width && y < m_height; ++x, ++y)
	{
		const auto space = m_spaces.at(y).at(x);
		if (space != space::FLOOR)
		{
			count += space == space::OCCUPIED;
			break;
		}
	}

	return count;
}

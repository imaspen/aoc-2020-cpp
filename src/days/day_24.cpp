#include "day_24.hpp"

#include <iostream>

aoc::day_24::day_24(const aoc::input& input) : day(input)
{
	const auto lines = m_input.strings();
	for (const auto& line : lines)
	{
		std::vector<dir> tile;
		for (size_t i = 0; i < line.size(); ++i)
		{
			const auto& c = line.at(i);
			if (c == 'e') tile.emplace_back(dir::E);
			else if (c == 'w') tile.emplace_back(dir::W);
			else if (c == 's')
			{
				const auto& c2 = line.at(++i);
				if (c2 == 'e') tile.emplace_back(dir::SE);
				else if (c2 == 'w') tile.emplace_back(dir::SW);
				else throw std::exception();
			}
			else if (c == 'n')
			{
				const auto& c2 = line.at(++i);
				if (c2 == 'e') tile.emplace_back(dir::NE);
				else if (c2 == 'w') tile.emplace_back(dir::NW);
				else throw std::exception();
			}
			else throw std::exception();
		}
		m_tiles_to_flip.emplace_back(tile);
	}
}

void aoc::day_24::part_one()
{
	for (const auto& tile_to_flip : m_tiles_to_flip)
	{
		int q = 0, r = 0;
		for (const auto& dir : tile_to_flip)
		{
			if (dir == dir::E) ++q;
			if (dir == dir::W) --q;
			if (dir == dir::SE) ++r;
			if (dir == dir::SW) ++r, --q;
			if (dir == dir::NE) --r, ++q;
			if (dir == dir::NW) --r;
		}
		const auto point = std::make_pair(q, r);
		if (m_tiles_flipped.count(point) == 0) m_tiles_flipped.emplace(point, true);
		else m_tiles_flipped.at(point) ^= true;
	}

	size_t count = 0;
	for (const auto& point_flipped : m_tiles_flipped)
	{
		if (point_flipped.second) ++count;
	}

	std::cout << count << std::endl;
}

void aoc::day_24::part_two()
{
	for (const auto& tile_to_flip : m_tiles_to_flip)
	{
		int q = 0, r = 0;
		for (const auto& dir : tile_to_flip)
		{
			if (dir == dir::E) ++q;
			if (dir == dir::W) --q;
			if (dir == dir::SE) ++r;
			if (dir == dir::SW) ++r, --q;
			if (dir == dir::NE) --r, ++q;
			if (dir == dir::NW) --r;
		}
		const auto point = std::make_pair(q, r);
		if (m_tiles_flipped.count(point) == 0) m_tiles_flipped.emplace(point, true);
		else m_tiles_flipped.at(point) ^= true;
	}

	for (const auto& point_flipped : m_tiles_flipped)
	{
		if (point_flipped.second) m_flipped_tiles.emplace(point_flipped.first);
	}

	for (size_t i = 0; i < 100; ++i) iterate();

	std::cout << m_flipped_tiles.size() << std::endl;
}

void aoc::day_24::iterate()
{
	m_adjacencies.clear();
	m_next_flipped_tiles.clear();

	for (const auto& tile : m_flipped_tiles)
	{
		const auto& q = tile.first;
		const auto& r = tile.second;
		increase_adjacencies_at(q + 1, r);
		increase_adjacencies_at(q - 1, r);
		increase_adjacencies_at(q, r + 1);
		increase_adjacencies_at(q - 1, r + 1);
		increase_adjacencies_at(q + 1, r - 1);
		increase_adjacencies_at(q, r - 1);
	}

	for (const auto& point_count : m_adjacencies)
	{
		const auto& point = point_count.first;
		const auto& count = point_count.second;
		if (m_flipped_tiles.count(point) == 1 && count >= 1 && count <= 2) m_next_flipped_tiles.emplace(point);
		else if (count == 2) m_next_flipped_tiles.emplace(point);
	}

	m_flipped_tiles.swap(m_next_flipped_tiles);
}

void aoc::day_24::increase_adjacencies_at(int q, int r)
{
	const auto point = std::make_pair(q, r);
	if (m_adjacencies.count(point) == 0) m_adjacencies.emplace(point, 1);
	else ++m_adjacencies.at(point);
}

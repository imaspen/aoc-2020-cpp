#include "day_17.hpp"

#include <iostream>

void aoc::day_17::part_one()
{
	parse_input();
	for (size_t i = 0; i < 6; ++i)
	{
		cycle();
	}
	std::cout << count_active() << std::endl;
}

void aoc::day_17::part_two()
{
	parse_input_4d();
	for (size_t i = 0; i < 6; ++i)
	{
		cycle_4d();
	}
	std::cout << count_active_4d() << std::endl;
}

void aoc::day_17::parse_input()
{
	const auto& lines = m_input.strings();
	int x = 0, y = 0;
	for (const auto& line : lines)
	{
		x = 0;
		for (const auto& cell : line)
		{
			if (cell == '#')
			{
				set_point(x, y, 0, true);
			}
			++x;
		}
		++y;
	}
	m_points = m_next_points;
}

void aoc::day_17::parse_input_4d()
{
	const auto& lines = m_input.strings();
	int x = 0, y = 0;
	for (const auto& line : lines)
	{
		x = 0;
		for (const auto& cell : line)
		{
			if (cell == '#')
			{
				set_point_4d(x, y, 0, 0, true);
			}
			++x;
		}
		++y;
	}
	m_points_4d = m_next_points_4d;
}

void aoc::day_17::cycle()
{
	m_next_points = m_points;
	m_adjacency_counts.clear();
	for (const auto& z_plane : m_points)
	{
		const auto& z = z_plane.first;
		const auto& plane = z_plane.second;
		for (const auto& y_line : plane)
		{
			const auto& y = y_line.first;
			const auto& line = y_line.second;
			for (const auto& x_point : line)
			{
				const auto& x = x_point.first;
				const auto& point = x_point.second;

				const auto adjacent = get_adjacent(x, y, z, point);

				if (point)
				{
					set_point(x, y, z, adjacent == 2 || adjacent == 3);
				}
			}
		}
	}
	for (const auto& z_plane : m_adjacency_counts)
	{
		const auto& z = z_plane.first;
		const auto& plane = z_plane.second;
		for (const auto& y_line : plane)
		{
			const auto& y = y_line.first;
			const auto& line = y_line.second;
			for (const auto& x_count : line)
			{
				const auto& x = x_count.first;
				const auto& count = x_count.second;

				if (!get_point(x, y, z) && count == 3)
				{
					set_point(x, y, z, true);
				}
			}
		}
	}
	m_points = m_next_points;
}

void aoc::day_17::cycle_4d()
{
	m_next_points_4d = m_points_4d;
	m_adjacency_counts_4d.clear();
	for (const auto& w_cube : m_points_4d)
	{
		const auto& w = w_cube.first;
		const auto& cube = w_cube.second;
		for (const auto& z_plane : cube)
		{
			const auto& z = z_plane.first;
			const auto& plane = z_plane.second;
			for (const auto& y_line : plane)
			{
				const auto& y = y_line.first;
				const auto& line = y_line.second;
				for (const auto& x_point : line)
				{
					const auto& x = x_point.first;
					const auto& point = x_point.second;

					const auto adjacent = get_adjacent_4d(x, y, z, w, point);

					if (point)
					{
						set_point_4d(x, y, z, w, adjacent == 2 || adjacent == 3);
					}
				}
			}
		}
	}
	for (const auto& w_cube : m_adjacency_counts_4d)
	{
		const auto& w = w_cube.first;
		const auto& cube = w_cube.second;
		for (const auto& z_plane : cube)
		{
			const auto& z = z_plane.first;
			const auto& plane = z_plane.second;
			for (const auto& y_line : plane)
			{
				const auto& y = y_line.first;
				const auto& line = y_line.second;
				for (const auto& x_count : line)
				{
					const auto& x = x_count.first;
					const auto& count = x_count.second;

					if (!get_point_4d(x, y, z, w) && count == 3)
					{
						set_point_4d(x, y, z, w, true);
					}
				}
			}
		}
	}
	m_points_4d = m_next_points_4d;
}

size_t aoc::day_17::get_adjacent(const int& x, const int& y, const int& z, const bool& active)
{
	size_t count = 0;
	for (int dz = -1; dz <= 1; ++dz)
	{
		for (int dy = -1; dy <= 1; ++dy)
		{
			for (int dx = -1; dx <= 1; ++dx)
			{
				if (dz == 0 && dy == 0 && dx == 0) continue;
				if (get_point(x + dx, y + dy, z + dz)) ++count;
				increment_adjacency_count(x + dx, y + dy, z + dz, active);
			}
		}
	}
	return count;
}

size_t aoc::day_17::get_adjacent_4d(const int& x, const int& y, const int& z, const int& w, const bool& active)
{
	size_t count = 0;
	for (int dw = -1; dw <= 1; ++dw)
	{
		for (int dz = -1; dz <= 1; ++dz)
		{
			for (int dy = -1; dy <= 1; ++dy)
			{
				for (int dx = -1; dx <= 1; ++dx)
				{
					if (dw == 0 && dz == 0 && dy == 0 && dx == 0) continue;
					if (get_point_4d(x + dx, y + dy, z + dz, w + dw)) ++count;
					increment_adjacency_count_4d(x + dx, y + dy, z + dz, w + dw, active);
				}
			}
		}
	}
	return count;
}

void aoc::day_17::increment_adjacency_count(const int& x, const int& y, const int& z, const bool& active)
{
	if (!active) return;
	if (m_adjacency_counts.count(z) == 0) m_adjacency_counts.insert(std::make_pair(z, std::map<int, std::map<int, int>>()));
	auto& plane = m_adjacency_counts.at(z);
	if (plane.count(y) == 0) plane.insert(std::make_pair(y, std::map<int, int>()));
	auto& line = plane.at(y);
	if (line.count(x) == 0) line.insert(std::make_pair(x, 0));
	++line.at(x);
}

void aoc::day_17::increment_adjacency_count_4d(const int& x, const int& y, const int& z, const int& w, const bool& active)
{
	if (!active) return;
	if (m_adjacency_counts_4d.count(w) == 0) m_adjacency_counts_4d.insert(std::make_pair(w, std::map<int, std::map<int, std::map<int, int>>>()));
	auto& cube = m_adjacency_counts_4d.at(w);
	if (cube.count(z) == 0) cube.insert(std::make_pair(z, std::map<int, std::map<int, int>>()));
	auto& plane = cube.at(z);
	if (plane.count(y) == 0) plane.insert(std::make_pair(y, std::map<int, int>()));
	auto& line = plane.at(y);
	if (line.count(x) == 0) line.insert(std::make_pair(x, 0));
	++line.at(x);
}

bool aoc::day_17::get_point(const int& x, const int& y, const int& z)
{
	if (m_points.count(z) == 0) return false;
	const auto& plane = m_points.at(z);
	if (plane.count(y) == 0) return false;
	const auto& line = plane.at(y);
	if (line.count(x) == 0) return false;
	return line.at(x);
}

bool aoc::day_17::get_point_4d(const int& x, const int& y, const int& z, const int& w)
{
	if (m_points_4d.count(w) == 0) return false;
	const auto& cube = m_points_4d.at(w);
	if (cube.count(z) == 0) return false;
	const auto& plane = cube.at(z);
	if (plane.count(y) == 0) return false;
	const auto& line = plane.at(y);
	if (line.count(x) == 0) return false;
	return line.at(x);
}

void aoc::day_17::set_point(const int& x, const int& y, const int& z, const bool& active)
{
	if (m_next_points.count(z) == 0) m_next_points.insert(std::make_pair(z, std::map<int, std::map<int, bool>>()));
	auto& plane = m_next_points.at(z);
	if (plane.count(y) == 0) plane.insert(std::make_pair(y, std::map<int, bool>()));
	auto& line = plane.at(y);
	if (line.count(x) == 0) line.insert(std::make_pair(x, false));
	line.at(x) = active;
}

void aoc::day_17::set_point_4d(const int& x, const int& y, const int& z, const int& w, const bool& active)
{
	if (m_next_points_4d.count(w) == 0) m_next_points_4d.insert(std::make_pair(w, std::map<int, std::map<int, std::map<int, bool>>>()));
	auto& cube = m_next_points_4d.at(w);
	if (cube.count(z) == 0) cube.insert(std::make_pair(z, std::map<int, std::map<int, bool>>()));
	auto& plane = cube.at(z);
	if (plane.count(y) == 0) plane.insert(std::make_pair(y, std::map<int, bool>()));
	auto& line = plane.at(y);
	if (line.count(x) == 0) line.insert(std::make_pair(x, false));
	line.at(x) = active;
}

size_t aoc::day_17::count_active()
{
	size_t count = 0;
	for (const auto& plane : m_points)
	{
		for (const auto& line : plane.second)
		{
			for (const auto& cell : line.second)
			{
				if (cell.second) ++count;
			}
		}
	}
	return count;
}

size_t aoc::day_17::count_active_4d()
{
	size_t count = 0;
	for (const auto& cube : m_points_4d)
	{
		for (const auto& plane : cube.second)
		{
			for (const auto& line : plane.second)
			{
				for (const auto& cell : line.second)
				{
					if (cell.second) ++count;
				}
			}
		}
	}
	return count;
}

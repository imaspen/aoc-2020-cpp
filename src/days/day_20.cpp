#include "day_20.hpp"

#include <cmath>
#include <iostream>
#include <stack>

aoc::day_20::day_20(const aoc::input& input) : aoc::day(input)
{
	const auto lines = m_input.strings();
	int id = -1;
	pixel_grid pixels;
	std::vector<std::string> strings;
	for (const auto& line : lines)
	{
		if (line.substr(0, 4) == "Tile")
		{
			if (id != -1)
			{
				m_tiles.emplace_back(std::make_shared<tile>(id, pixels, strings));
			}
			strings.clear();
			pixels.clear();
			id = std::stoi(line.substr(5));
		}
		else
		{
			std::vector<bool> pixel_line;
			for (const auto& c : line)
			{
				pixel_line.emplace_back(c == '#');
			}
			pixels.emplace_back(pixel_line);
			strings.emplace_back(line);
		}
	}
	m_tiles.emplace_back(std::make_shared<tile>(id, pixels, strings));
}

void aoc::day_20::part_one()
{
	const auto checksum_matches = get_checksum_matches();

	unsigned long product = 1;
	for (const auto& id : get_corners(checksum_matches))
	{
		product *= id;
	}

	std::cout << product << std::endl;
}

void aoc::day_20::part_two()
{
	std::map<int, std::shared_ptr<tile>> remaining_tiles;
	for (const auto& tile : m_tiles)
	{
		remaining_tiles.emplace(tile->id, tile);
	}

	const auto checksum_matches = get_checksum_matches();
	auto corner_id = get_corners(checksum_matches).at(0);
	auto corner = remaining_tiles.at(corner_id);
	remaining_tiles.erase(corner_id);

	for (size_t r = 0; r < 4; ++r)
	{
		bool oriented = false;
		for (size_t f = 0; f < 2; ++f)
		{
			corner->rotation = r;
			corner->flipped = f;
			const auto checksums = corner->current_checksums();
			if (checksum_matches.at(checksums.at(0)).size() == 1 && checksum_matches.at(checksums.at(3)).size() == 1)
			{
				oriented = true;
				break;
			}
		}
		if (oriented) break;
	}

	std::vector<std::vector<std::shared_ptr<tile>>> tiles;
	std::vector<std::shared_ptr<tile>> row({ corner });
	auto next_edge = corner;
	while (next_edge)
	{
		auto edge = next_edge;
		auto next = edge;
		next_edge.reset();

		while (next)
		{
			auto current = next;
			next.reset();

			const auto current_right = current->current_checksums().at(1);
			for (const auto& id_tile : remaining_tiles)
			{
				auto tile = id_tile.second;
				if (tile->try_match_left_edge(current_right))
				{
					remaining_tiles.erase(tile->id);
					row.emplace_back(tile);
					next = tile;
					break;
				}
			}
		}

		tiles.emplace_back(row);
		row.clear();

		const auto edge_bottom = edge->current_checksums().at(2);
		for (const auto& id_tile : remaining_tiles)
		{
			auto tile = id_tile.second;
			if (tile->try_match_top_edge(edge_bottom))
			{
				remaining_tiles.erase(tile->id);
				row.emplace_back(tile);
				next_edge = tile;
				next = tile;
				break;
			}
		}
	}

	pixel_grid image;
	std::array<std::vector<bool>, 8> lines;
	for (const auto& row : tiles)
	{
		for (const auto& tile : row)
		{
			pixels_array pixels = tile->current_arrangement();
			for (size_t y = 1; y < 9; ++y)
			{
				const auto pixel_row = pixels.at(y);
				auto& line = lines.at(y - 1);
				for (size_t x = 1; x < 9; ++x)
				{
					line.emplace_back(pixel_row.at(x));
				}
			}
		}
		for (auto& line : lines)
		{
			image.emplace_back(line);
			line.clear();
		}
	}

	std::vector<std::pair<size_t, size_t>> sea_monsters;
	int rotation, flip;
	for (rotation = 0; rotation < 4; ++rotation)
	{
		for (flip = 0; flip < 2; ++flip)
		{
			const auto transformed_image = transform_image(image, rotation, flip);
			for (size_t y = 0; y < transformed_image.size() - 3; ++y)
			{
				const auto& row = transformed_image.at(y);
				for (size_t x = 0; x < row.size() - 20; ++x)
				{
					if (is_sea_monster(transformed_image, x, y)) sea_monsters.emplace_back(x, y);
				}
			}
			if (sea_monsters.size() > 0) break;
		}
		if (sea_monsters.size() > 0) break;
	}

	image = transform_image(image, rotation, flip);
	for (const auto& point : sea_monsters)
	{
		clear_sea_monster(image, point.first, point.second);
	}

	size_t count = 0;
	for (const auto& line : image)
	{
		for (const auto& pixel : line)
		{
			count += pixel;
		}
	}

	std::cout << count << std::endl;
}

std::map<int, std::vector<std::shared_ptr<aoc::day_20::tile>>> aoc::day_20::get_checksum_matches()
{
	std::map<int, std::vector<std::shared_ptr<tile>>> checksum_matches;
	for (const auto& tile : m_tiles)
	{
		for (const auto& checksum_pair : tile->possible_checksums())
		{
			for (const auto& checksum : checksum_pair)
			{
				if (checksum_matches.count(checksum) == 0) checksum_matches.insert(std::make_pair(checksum, std::vector<std::shared_ptr<day_20::tile>>()));
				checksum_matches.at(checksum).emplace_back(tile);
			}
		}
	}
	return checksum_matches;
}

std::array<int, 4> aoc::day_20::get_corners(std::map<int, std::vector<std::shared_ptr<tile>>> checksum_matches)
{
	std::map<int, int> pair_counts;
	for (const auto& checksum_tiles : checksum_matches)
	{
		const auto& tiles = checksum_tiles.second;
		if (tiles.size() == 2)
		{
			for (const auto& tile : tiles)
			{
				if (pair_counts.count(tile->id) == 0) pair_counts.insert(std::make_pair(tile->id, 0));
				++pair_counts.at(tile->id);
			}
		}
	}

	size_t i = 0;
	std::array<int, 4> corners;
	for (const auto& id_count : pair_counts)
	{
		if (id_count.second == 4) corners.at(i++) = id_count.first;
	}

	return corners;
}

aoc::day_20::tile::tile(int id, pixel_grid pixels, const std::vector<std::string>& lines) : id(id), pixels(pixels)
{
	auto& zero = arrangements.at(0).at(0);
	auto& ninety = arrangements.at(1).at(0);
	auto& oneeighty = arrangements.at(2).at(0);
	auto& twoseventy = arrangements.at(3).at(0);

	for (size_t y = 0; y < 10; ++y)
	{
		const auto& line = lines.at(y);
		for (size_t x = 0; x < 10; ++x)
		{
			const auto& pixel = line.at(x) == '#';
			zero.at(y).at(x) = pixel;
			ninety.at(x).at(9 - y) = pixel;
			oneeighty.at(9 - y).at(9 - x) = pixel;
			twoseventy.at(9 - x).at(y) = pixel;
		}
	}

	for (size_t i = 0; i < 4; ++i)
	{
		arrangements.at(i).at(1) = arrangements.at(i).at(0);
		for (auto& row : arrangements.at(i).at(1)) std::reverse(row.begin(), row.end());
	}
}

aoc::day_20::checksums aoc::day_20::tile::possible_checksums() const
{
	checksums checksums;
	std::array<unsigned int, 2> empty;
	empty.fill(0);
	checksums.fill(empty);
	for (size_t i = 0; i < pixels.size(); ++i)
	{
		checksums.at(0).at(0) <<= 1;
		checksums.at(0).at(1) <<= 1;
		checksums.at(1).at(0) <<= 1;
		checksums.at(1).at(1) <<= 1;
		checksums.at(2).at(0) <<= 1;
		checksums.at(2).at(1) <<= 1;
		checksums.at(3).at(0) <<= 1;
		checksums.at(3).at(1) <<= 1;
		if (pixels.front().at(i)) ++checksums.at(0).at(0);
		if (pixels.front().at(pixels.size() - 1 - i)) ++checksums.at(0).at(1);
		if (pixels.at(i).front()) ++checksums.at(1).at(0);
		if (pixels.at(pixels.size() - 1 - i).front()) ++checksums.at(1).at(1);
		if (pixels.back().at(i)) ++checksums.at(2).at(0);
		if (pixels.back().at(pixels.size() - 1 - i)) ++checksums.at(2).at(1);
		if (pixels.at(i).back()) ++checksums.at(3).at(0);
		if (pixels.at(pixels.size() - 1 - i).back()) ++checksums.at(3).at(1);
	}
	return checksums;
}

std::array<unsigned int, 4> aoc::day_20::tile::current_checksums()
{
	std::array<unsigned int, 4> checksums;
	checksums.fill(0);

	const auto current_pixels = current_arrangement();

	for (size_t i = 0; i < 10; ++i)
	{
		checksums.at(0) <<= 1;
		checksums.at(1) <<= 1;
		checksums.at(2) <<= 1;
		checksums.at(3) <<= 1;
		checksums.at(0) += current_pixels.at(0).at(i);
		checksums.at(1) += current_pixels.at(i).at(9);
		checksums.at(2) += current_pixels.at(9).at(i);
		checksums.at(3) += current_pixels.at(i).at(0);
	}

	return checksums;
}

aoc::day_20::pixels_array aoc::day_20::tile::current_arrangement()
{
	return arrangements.at(rotation).at(flipped);
}

bool aoc::day_20::tile::try_match_left_edge(unsigned int other_right)
{
	for (size_t r = 0; r < 4; ++r)
	{
		for (size_t f = 0; f < 2; ++f)
		{
			rotation = r;
			flipped = f;
			const auto checksums = current_checksums();
			if (other_right == checksums.at(3)) return true;
		}
	}
	return false;
}

bool aoc::day_20::tile::try_match_top_edge(unsigned int other_bottom)
{
	for (size_t r = 0; r < 4; ++r)
	{
		for (size_t f = 0; f < 2; ++f)
		{
			rotation = r;
			flipped = f;
			const auto checksums = current_checksums();
			if (other_bottom == checksums.at(0)) return true;
		}
	}
	return false;
}

aoc::day_20::pixel_grid aoc::day_20::transform_image(const pixel_grid& pixels, int rotation, int flip)
{
	pixel_grid transformed = pixels;
	const auto edge_length = pixels.size() - 1;
	if (rotation == 1)
	{
		for (size_t y = 0; y < pixels.size(); ++y)
		{
			const auto& line = pixels.at(y);
			for (size_t x = 0; x < line.size(); ++x)
			{
				transformed.at(x).at(edge_length - y) = line.at(x);
			}
		}
	}
	else if (rotation == 2)
	{
		for (size_t y = 0; y < pixels.size(); ++y)
		{
			const auto& line = pixels.at(y);
			for (size_t x = 0; x < line.size(); ++x)
			{
				transformed.at(edge_length - y).at(edge_length - x) = line.at(x);
			}
		}
	}
	else if (rotation == 3)
	{
		for (size_t y = 0; y < pixels.size(); ++y)
		{
			const auto& line = pixels.at(y);
			for (size_t x = 0; x < line.size(); ++x)
			{
				transformed.at(edge_length - x).at(y) = line.at(x);
			}
		}
	}
	else if (rotation != 0) throw std::exception();

	if (flip == 1)
	{
		for (auto& row : transformed) std::reverse(row.begin(), row.end());
	}
	else if (flip != 0) throw std::exception();

	return transformed;
}

bool aoc::day_20::is_sea_monster(const pixel_grid& pixels, size_t x, size_t y)
{
	//                   # 
	// #    ##    ##    ###
	//  #  #  #  #  #  #   
	if (!pixels.at(y).at(x + 18)) return false;
	if (!pixels.at(y + 1).at(x)) return false;
	if (!pixels.at(y + 1).at(x + 5)) return false;
	if (!pixels.at(y + 1).at(x + 6)) return false;
	if (!pixels.at(y + 1).at(x + 11)) return false;
	if (!pixels.at(y + 1).at(x + 12)) return false;
	if (!pixels.at(y + 1).at(x + 17)) return false;
	if (!pixels.at(y + 1).at(x + 18)) return false;
	if (!pixels.at(y + 1).at(x + 19)) return false;
	if (!pixels.at(y + 2).at(x + 1)) return false;
	if (!pixels.at(y + 2).at(x + 4)) return false;
	if (!pixels.at(y + 2).at(x + 7)) return false;
	if (!pixels.at(y + 2).at(x + 10)) return false;
	if (!pixels.at(y + 2).at(x + 13)) return false;
	if (!pixels.at(y + 2).at(x + 16)) return false;
	return true;
}

void aoc::day_20::clear_sea_monster(pixel_grid& pixels, size_t x, size_t y)
{
	//                   # 
	// #    ##    ##    ###
	//  #  #  #  #  #  #   
	pixels.at(y).at(x + 18) = false;
	pixels.at(y + 1).at(x) = false;
	pixels.at(y + 1).at(x + 5) = false;
	pixels.at(y + 1).at(x + 6) = false;
	pixels.at(y + 1).at(x + 11) = false;
	pixels.at(y + 1).at(x + 12) = false;
	pixels.at(y + 1).at(x + 17) = false;
	pixels.at(y + 1).at(x + 18) = false;
	pixels.at(y + 1).at(x + 19) = false;
	pixels.at(y + 2).at(x + 1) = false;
	pixels.at(y + 2).at(x + 4) = false;
	pixels.at(y + 2).at(x + 7) = false;
	pixels.at(y + 2).at(x + 10) = false;
	pixels.at(y + 2).at(x + 13) = false;
	pixels.at(y + 2).at(x + 16) = false;
}

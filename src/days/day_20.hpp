#pragma once

#include <array>
#include <map>
#include <memory>
#include <vector>

#include "day.hpp"

namespace aoc
{
	class day_20 : public aoc::day
	{
	public:
		day_20(const aoc::input& input);

		virtual void part_one() override;
		virtual void part_two() override;

	private:
		typedef std::vector<std::vector<bool>> pixel_grid;
		typedef std::array<std::array<bool, 10>, 10> pixels_array;
		typedef std::array<std::array<unsigned int, 2>, 4> checksums;
		struct tile
		{
		public:
			tile(int id, pixel_grid pixels, const std::vector<std::string>& lines);

			int id, rotation = 0, flipped = 0;

			pixel_grid pixels;
			std::array<std::array<pixels_array, 2>, 4> arrangements;

			// 0: top, 1: right, 2: bottom, 3: right => 0: top->bottom, left->right, 1: bottom->top, right->left
			checksums possible_checksums() const;
			std::array<unsigned int, 4> current_checksums();
			pixels_array current_arrangement();

			bool try_match_left_edge(unsigned int other_right);
			bool try_match_top_edge(unsigned int other_bottom);
		};

		std::map<int, std::vector<std::shared_ptr<tile>>> get_checksum_matches();
		static std::array<int, 4> get_corners(std::map<int, std::vector<std::shared_ptr<tile>>> checksum_matches);

		static pixel_grid transform_image(const pixel_grid& pixels, int rotation, int flip);
		static bool is_sea_monster(const pixel_grid& pixels, size_t x, size_t y);
		static void clear_sea_monster(pixel_grid& pixels, size_t x, size_t y);

		std::vector<std::shared_ptr<tile>> m_tiles;
	};
}

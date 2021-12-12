#pragma once

#include <map>
#include <set>
#include <utility>
#include <vector>

#include "day.hpp"

namespace aoc
{
	class day_24 : public aoc::day
	{
	public:
		day_24(const aoc::input& input);

		virtual void part_one() override;
		virtual void part_two() override;

	private:
		enum dir
		{
			E,
			SE,
			SW,
			W,
			NW,
			NE,
		};

		void iterate();
		void increase_adjacencies_at(int q, int r);

		std::map<std::pair<int, int>, bool> m_tiles_flipped;
		std::set<std::pair<int, int>> m_flipped_tiles, m_next_flipped_tiles;
		std::map<std::pair<int, int>, int> m_adjacencies;

		std::vector<std::vector<dir>> m_tiles_to_flip;
	};
}

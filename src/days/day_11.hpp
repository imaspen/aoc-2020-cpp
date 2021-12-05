#pragma once

#include "day.hpp"

namespace aoc
{
	class day_11 : public aoc::day
	{
	public:
		day_11(aoc::input const& input);

		virtual void part_one() override;
		virtual void part_two() override;

	private:
		enum space
		{
			FLOOR = '.',
			EMPTY = 'L',
			OCCUPIED = '#',
		};

		int adjacent_occupied(size_t x, size_t y);
		int visible_occupied(size_t sx, size_t sy);

		size_t m_width, m_height;
		std::vector<std::vector<space>> m_spaces;
	};
}

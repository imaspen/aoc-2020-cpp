#pragma once

#include "day.hpp"

namespace aoc
{
	class day_14 : public aoc::day
	{
	public:
		using day::day;

		virtual void part_one() override;
		virtual void part_two() override;

	private:
		static size_t find_mask_with_x(const std::vector<std::string>& masks);
	};
}

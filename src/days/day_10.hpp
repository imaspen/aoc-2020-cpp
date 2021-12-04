#pragma once

#include "day.hpp"

namespace aoc
{
	class day_10 : public aoc::day
	{
	public:
		using day::day;

		virtual void part_one() override;
		virtual void part_two() override;

	private:
		static int variants_for_count(int count);
	};
}

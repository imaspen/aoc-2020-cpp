#pragma once

#include "day.hpp"

namespace aoc
{
	class day_13 : public aoc::day
	{
	public:
		using day::day;

		virtual void part_one() override;
		virtual void part_two() override;

	private:
		static unsigned long time_to_next(const unsigned long& curr_time, const unsigned long& frequency);
	};
}

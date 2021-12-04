#pragma once

#include "day.hpp"

namespace aoc
{
	class day_09 : public aoc::day
	{
	public:
		using day::day;

		virtual void part_one() override;
		virtual void part_two() override;

	private:
		long get_problem_number();
	};
}

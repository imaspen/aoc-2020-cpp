#pragma once

#include "day.hpp"

namespace aoc
{
	class day_15 : public aoc::day
	{
	public:
		using day::day;

		virtual void part_one() override;
		virtual void part_two() override;

	private:
		size_t run(const size_t& run_to);
	};
}

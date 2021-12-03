#pragma once

#include "../input.hpp"

namespace aoc
{
	class day
	{
	public:
		day(aoc::input const &input) : m_input(input){};
		virtual ~day() = default;

		virtual void part_one() = 0;
		virtual void part_two() = 0;

	protected:
		aoc::input m_input;
	};
}

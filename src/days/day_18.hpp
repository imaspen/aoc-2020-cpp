#pragma once

#include "day.hpp"

namespace aoc
{
	class unrecognized_equation_char_exception : public std::exception
	{
	public:
		unrecognized_equation_char_exception(const char& c) : c(c) {};

		char c;
	};

	class day_18 : public aoc::day
	{
	public:
		using day::day;

		virtual void part_one() override;
		virtual void part_two() override;

	private:
		static std::string strip_spaces(const std::string& str);

		static unsigned long solve_equation(std::string equation);
		static unsigned long solve_equation_prioritized(std::string equation);
	};
}

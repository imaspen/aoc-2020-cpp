#pragma once

#include "day.hpp"

#include <tuple>

namespace aoc
{
	class unrecognized_dir_exception : public std::exception
	{
	public:
		unrecognized_dir_exception(char dir) : dir(dir){};

		char dir;
	};

	class day_05 : public aoc::day
	{
	public:
		using day::day;

		virtual void part_one() override;
		virtual void part_two() override;

	private:
		static std::tuple<unsigned int, unsigned int> get_row_column(const std::string &line);
	};
}

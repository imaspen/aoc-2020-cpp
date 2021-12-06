#pragma once

#include "day.hpp"

namespace aoc
{
	class day_16 : public aoc::day
	{
	public:
		using day::day;

		virtual void part_one() override;
		virtual void part_two() override;

	private:
		typedef std::vector<int> ticket;

		struct field
		{
			std::string name;
			int min_1, max_1, min_2, max_2;
			size_t pos = 0;
		};

		static ticket ticket_from_string(std::string str);
		static field field_from_string(std::string str);
		static std::vector<std::vector<bool>> simplify_valids(std::vector<std::vector<bool>> field_valid_at_pos);
		static bool valids_in_simplest_form(const std::vector<std::vector<bool>>& field_valid_at_pos);
	};
}

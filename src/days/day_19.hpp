#pragma once

#include <map>

#include "day.hpp"

namespace aoc
{
	class day_19 : public aoc::day
	{
	public:
		using day::day;

		virtual void part_one() override;
		virtual void part_two() override;

	private:
		struct rule
		{
			enum { STR, NUM } type;
			std::string regex;
			std::vector<std::vector<int>> rules;
		};

		static std::map<int, rule> generate_rules(const std::vector<std::string>& rule_strs);
		static std::map<int, rule> generate_rules_p2(const std::vector<std::string>& rule_strs);
		static bool rules_simplified(const std::map<int, rule>& rules);
		static void simplify_rules(std::map<int, rule>& rules);
		static void simplify_rules_p2(std::map<int, rule>& rules);
	};
}

#pragma once

#include <map>
#include <set>
#include <utility>
#include <vector>

#include "day.hpp"

namespace aoc
{
	class day_21 : public aoc::day
	{
	public:
		day_21(const aoc::input& input);

		virtual void part_one() override;
		virtual void part_two() override;

	private:
		typedef std::string ingredient;
		typedef std::string allergen;
		typedef std::pair<std::set<ingredient>, std::set<allergen>> food;

		std::set<ingredient> m_ingredients;
		std::set<allergen> m_allergens;
		std::vector<food> m_foods;

		static bool is_list_simplified(const std::map<allergen, std::set<ingredient>>& list);
		static std::map<allergen, std::set<ingredient>> simplify_list(const std::map<allergen, std::set<ingredient>>& list);
	};
}

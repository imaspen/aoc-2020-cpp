#include "day_21.hpp"

#include <algorithm>
#include <iostream>

aoc::day_21::day_21(const input& input) : day(input)
{
	for (auto line : m_input.strings())
	{
		food food;
		bool in_allergens = false;
		while (true)
		{
			auto part = line.substr(0, line.find(" "));

			if (in_allergens)
			{
				if (part.back() == ')' || part.back() == ',') part.pop_back();
				m_allergens.emplace(part);
				food.second.emplace(part);
			}
			else if (part == "(contains")
			{
				in_allergens = true;
			}
			else
			{
				m_ingredients.emplace(part);
				food.first.emplace(part);
			}

			auto pos = line.find(" ");
			if (pos == std::string::npos) break;
			line = line.substr(pos + 1);
		}
		m_foods.emplace_back(food);
	}
}

void aoc::day_21::part_one()
{
	std::map<allergen, std::set<ingredient>> allergen_possible_ingredients;
	for (const auto& ingredients_allergens : m_foods)
	{
		for (const auto& allergen : ingredients_allergens.second)
		{
			if (allergen_possible_ingredients.count(allergen) == 0)
			{
				allergen_possible_ingredients.emplace(allergen, ingredients_allergens.first);
			}
			else
			{
				std::set<ingredient> intersection;
				for (const auto& i : allergen_possible_ingredients.at(allergen))
				{
					if (ingredients_allergens.first.count(i) == 1) intersection.emplace(i);
				}
				allergen_possible_ingredients.at(allergen) = intersection;
			}
		}
	}

	std::set<ingredient> safe_ingredients;
	for (const auto& ingredient : m_ingredients)
	{
		bool safe = true;
		for (const auto& allergen_ingredients : allergen_possible_ingredients)
		{
			if (allergen_ingredients.second.count(ingredient) == 1)
			{
				safe = false;
				break;
			}
		}
		if (safe) safe_ingredients.emplace(ingredient);
	}

	size_t count = 0;
	for (const auto& ingredients_allergens : m_foods)
	{
		for (const auto& ingredient : ingredients_allergens.first)
		{
			count += safe_ingredients.count(ingredient);
		}
	}

	std::cout << count << std::endl;
}

void aoc::day_21::part_two()
{
	std::map<allergen, std::set<ingredient>> allergen_possible_ingredients;
	for (const auto& ingredients_allergens : m_foods)
	{
		for (const auto& allergen : ingredients_allergens.second)
		{
			if (allergen_possible_ingredients.count(allergen) == 0)
			{
				allergen_possible_ingredients.emplace(allergen, ingredients_allergens.first);
			}
			else
			{
				std::set<ingredient> intersection;
				for (const auto& i : allergen_possible_ingredients.at(allergen))
				{
					if (ingredients_allergens.first.count(i) == 1) intersection.emplace(i);
				}
				allergen_possible_ingredients.at(allergen) = intersection;
			}
		}
	}

	while (!is_list_simplified(allergen_possible_ingredients))
	{
		allergen_possible_ingredients = simplify_list(allergen_possible_ingredients);
	}

	std::string canonical_dangerous_ingredients;
	for (const auto& entry : allergen_possible_ingredients)
	{
		canonical_dangerous_ingredients += *entry.second.begin();
		canonical_dangerous_ingredients.push_back(',');
	}
	canonical_dangerous_ingredients.pop_back();

	std::cout << canonical_dangerous_ingredients << std::endl;
}

bool aoc::day_21::is_list_simplified(const std::map<allergen, std::set<ingredient>>& list)
{
	for (const auto& e : list)
	{
		if (e.second.size() > 1) return false;
	}
	return true;
}

std::map<aoc::day_21::allergen, std::set<aoc::day_21::ingredient>> aoc::day_21::simplify_list(const std::map<allergen, std::set<ingredient>>& list)
{
	std::map<allergen, std::set<ingredient>> next = list;

	for (const auto& allergen_ingredients : list)
	{
		const auto& allergen = allergen_ingredients.first;
		const auto& ingredients = allergen_ingredients.second;
		if (ingredients.size() == 1)
		{
			const auto& ingredient = *ingredients.begin();
			for (auto& other_allergen_ingredients : next)
			{
				if (other_allergen_ingredients.first != allergen) other_allergen_ingredients.second.erase(ingredient);
			}
		}
	}

	return next;
}

#include "day_07.hpp"

#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <set>

#include "../objects/bag.hpp"

void aoc::day_07::part_one()
{
	const auto lines = m_input.strings();

	std::map<std::string, std::shared_ptr<aoc::bag>> bags;

	for (const auto &line : lines)
	{
		const auto description = aoc::bag::description_from_string(line);
		bags.insert({description, std::make_shared<aoc::bag>(description)});
	}

	for (const auto &line : lines)
	{
		const auto description = aoc::bag::description_from_string(line);
		const auto contents = aoc::bag::content_from_string(line, bags);
		const auto &bag = bags.at(description);
		for (const auto &content : contents)
		{
			bag->can_contain.emplace_back(content);
			content.type->contained_by.emplace_back(bag);
		}
	}

	std::queue<std::shared_ptr<aoc::bag>> queue;
	queue.emplace(bags.at("shiny gold"));
	std::set<std::shared_ptr<aoc::bag>> can_contain;

	while (!queue.empty())
	{
		const auto bag = queue.front();
		queue.pop();
		const bool visited = can_contain.count(bag);
		if (visited)
		{
			continue;
		}

		can_contain.emplace(bag);

		for (const auto &b : bag->contained_by)
		{
			queue.emplace(b);
		}
	}

	std::cout << can_contain.size() - 1 << std::endl;
}

void aoc::day_07::part_two()
{
	const auto lines = m_input.strings();

	std::map<std::string, std::shared_ptr<aoc::bag>> bags;

	for (const auto &line : lines)
	{
		const auto description = aoc::bag::description_from_string(line);
		bags.insert({description, std::make_shared<aoc::bag>(description)});
	}

	for (const auto &line : lines)
	{
		const auto description = aoc::bag::description_from_string(line);
		const auto contents = aoc::bag::content_from_string(line, bags);
		const auto &bag = bags.at(description);
		for (const auto &content : contents)
		{
			bag->can_contain.emplace_back(content);
			content.type->contained_by.emplace_back(bag);
		}
	}

	std::cout << bags.at("shiny gold")->get_bags_count() - 1 << std::endl;
}

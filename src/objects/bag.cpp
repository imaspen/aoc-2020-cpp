#include "bag.hpp"

#include <iostream>

std::string aoc::bag::description_from_string(const std::string &line)
{
	const auto split_idx = line.find(" bags contain ");
	return line.substr(0, split_idx);
}

std::vector<aoc::bag::content> aoc::bag::content_from_string(const std::string &line, const std::map<std::string, std::shared_ptr<aoc::bag>> &bags)
{
	const auto content_idx = line.find(" bags contain ") + 14;
	const auto content_str = line.substr(content_idx, line.size() - content_idx - 1);

	if (content_str == "no other bags")
	{
		return {};
	}

	std::vector<std::string> contents_strs;
	std::string remainder = content_str;
	while (true)
	{
		size_t split_idx = remainder.find(", ");
		contents_strs.emplace_back(remainder.substr(0, split_idx));
		if (split_idx == std::string::npos)
		{
			break;
		}
		remainder = remainder.substr(split_idx + 2);
	}

	std::vector<aoc::bag::content> contents;
	for (const auto &content : contents_strs)
	{
		size_t count_split_idx = content.find(' ');
		const size_t count = std::stoul(content.substr(0, count_split_idx));
		size_t description_split_idx = content.find(" bag");
		const std::string description = content.substr(count_split_idx + 1, description_split_idx - count_split_idx - 1);

		contents.emplace_back(aoc::bag::content{.count = count, .type = bags.at(description)});
	}

	return contents;
}

size_t aoc::bag::get_bags_count()
{
	size_t count = 1;
	for (const auto &content : can_contain)
	{
		count += content.type->get_bags_count() * content.count;
	}
	return count;
}

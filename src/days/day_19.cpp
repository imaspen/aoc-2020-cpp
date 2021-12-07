#include "day_19.hpp"

#include <iostream>
#include <regex>

void aoc::day_19::part_one()
{
	std::vector<std::string> rule_strs, messages;
	for (const auto& str : m_input.strings())
	{
		const auto& c = str.at(0);
		if (c == 'a' || c == 'b')
		{
			messages.push_back(str);
		}
		else if (c >= '0' && c <= '9')
		{
			rule_strs.push_back(str);
		}
	}

	auto rules = generate_rules(rule_strs);

	std::regex rule_zero("^" + rules.at(0).regex + "$");

	size_t count = 0;
	for (const auto& message : messages)
	{
		if (std::regex_search(message, rule_zero)) ++count;
	}

	std::cout << count << std::endl;
}

void aoc::day_19::part_two()
{
	std::vector<std::string> rule_strs, messages;
	for (const auto& str : m_input.strings())
	{
		const auto& c = str.at(0);
		if (c == 'a' || c == 'b')
		{
			messages.push_back(str);
		}
		else if (c >= '0' && c <= '9')
		{
			rule_strs.push_back(str);
		}
	}

	auto rules = generate_rules_p2(rule_strs);

	std::regex rule_zero("^" + rules.at(0).regex + "$");

	size_t count = 0;
	for (const auto& message : messages)
	{
		if (std::regex_search(message, rule_zero)) ++count;
	}

	std::cout << count << std::endl;
}

std::map<int, aoc::day_19::rule> aoc::day_19::generate_rules(const std::vector<std::string>& rule_strs)
{
	std::map<int, rule> rules;
	for (auto str : rule_strs)
	{
		size_t rule_num_end;
		const auto rule_num = std::stoi(str, &rule_num_end);
		const auto rule_str = str.substr(rule_num_end + 2);
		if (rule_str.at(0) == '"')
		{
			rules.emplace(rule_num, rule{ .type = rule::STR, .regex = rule_str.substr(1, rule_str.size() - 2) });
		}
		else
		{
			std::vector<std::vector<int>> options;
			std::vector<int> rs;
			size_t next_pos = str.find(':') + 2;
			while (next_pos < str.size())
			{
				str = str.substr(next_pos);
				if (str.at(0) == '|')
				{
					options.emplace_back(rs);
					rs.clear();
					next_pos = 2;
				}
				else
				{
					rs.emplace_back(std::stoi(str, &next_pos));
					++next_pos;
				}
			}
			options.emplace_back(rs);
			rules.emplace(rule_num, rule{ .type = rule::NUM, .rules = options });
		}
	}
	simplify_rules(rules);
	return rules;
}

std::map<int, aoc::day_19::rule> aoc::day_19::generate_rules_p2(const std::vector<std::string>& rule_strs)
{
	std::map<int, rule> rules;
	for (auto str : rule_strs)
	{
		size_t rule_num_end;
		const auto rule_num = std::stoi(str, &rule_num_end);
		const auto rule_str = str.substr(rule_num_end + 2);
		if (rule_str.at(0) == '"')
		{
			rules.emplace(rule_num, rule{ .type = rule::STR, .regex = rule_str.substr(1, rule_str.size() - 2) });
		}
		else
		{
			std::vector<std::vector<int>> options;
			std::vector<int> rs;
			size_t next_pos = str.find(':') + 2;
			while (next_pos < str.size())
			{
				str = str.substr(next_pos);
				if (str.at(0) == '|')
				{
					options.emplace_back(rs);
					rs.clear();
					next_pos = 2;
				}
				else
				{
					rs.emplace_back(std::stoi(str, &next_pos));
					++next_pos;
				}
			}
			options.emplace_back(rs);
			if (rule_num == 11)
			{
				for (size_t i = 2; i <= 5; ++i)
				{
					std::vector<int> repeated_rs;
					for (size_t j = 0; j < i; ++j)
					{
						repeated_rs.emplace_back(rs.at(0));
					}
					for (size_t j = 0; j < i; ++j)
					{
						repeated_rs.emplace_back(rs.at(1));
					}
					options.emplace_back(repeated_rs);
				}
			}
			rules.emplace(rule_num, rule{ .type = rule::NUM, .rules = options });
		}
	}
	simplify_rules_p2(rules);
	return rules;
}

bool aoc::day_19::rules_simplified(const std::map<int, rule>& rules)
{
	for (const auto& rule : rules)
	{
		if (rule.second.type == rule::NUM) return false;
	}
	return true;
}

void aoc::day_19::simplify_rules(std::map<int, rule>& rules)
{
	while (!rules_simplified(rules))
	{
		for (auto& num_rule : rules)
		{
			auto& rule = num_rule.second;
			if (rule.type == rule::STR) continue;
			bool can_be_simplified = true;
			for (const auto& option : rule.rules)
			{
				for (const auto& ref : option)
				{
					if (rules.at(ref).type == rule::NUM)
					{
						can_be_simplified = false;
						break;
					}
				}
				if (!can_be_simplified) break;
			}
			if (can_be_simplified)
			{
				rule.type = rule::STR;
				std::vector<std::string> str_options;
				for (const auto& option : rule.rules)
				{
					std::string str_option;
					for (const auto& ref : option)
					{
						str_option += rules.at(ref).regex;
					}
					str_options.emplace_back(str_option);
				}
				std::string regex = "(" + str_options.front();
				for (auto it = ++str_options.begin(); it != str_options.end(); ++it)
				{
					regex += "|" + *it;
				}
				regex += ")";
				rule.regex = regex;
			}
		}
	}
}

void aoc::day_19::simplify_rules_p2(std::map<int, rule>& rules)
{
	while (!rules_simplified(rules))
	{
		for (auto& num_rule : rules)
		{
			auto& rule = num_rule.second;
			if (rule.type == rule::STR) continue;
			bool can_be_simplified = true;
			for (const auto& option : rule.rules)
			{
				for (const auto& ref : option)
				{
					if (rules.at(ref).type == rule::NUM)
					{
						can_be_simplified = false;
						break;
					}
				}
				if (!can_be_simplified) break;
			}
			if (can_be_simplified)
			{
				rule.type = rule::STR;
				std::vector<std::string> str_options;
				for (const auto& option : rule.rules)
				{
					std::string str_option;
					for (const auto& ref : option)
					{
						if (ref == 8)
						{
							str_option += rules.at(ref).regex;
							str_option.push_back('+');
						}
						else
						{
							str_option += rules.at(ref).regex;
						}
					}
					str_options.emplace_back(str_option);
				}
				std::string regex = "(" + str_options.front();
				for (auto it = ++str_options.begin(); it != str_options.end(); ++it)
				{
					regex += "|" + *it;
				}
				regex += ")";
				rule.regex = regex;
			}
		}
	}
}

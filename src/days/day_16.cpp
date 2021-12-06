#include "day_16.hpp"

#include <iostream>

void aoc::day_16::part_one()
{
	const auto lines = m_input.strings();

	std::vector<field> fields;

	size_t i = 0;
	while (lines.at(i) != "your ticket:")
	{
		fields.emplace_back(field_from_string(lines.at(i)));
		++i;
	}
	++i;
	const ticket my_ticket = ticket_from_string(lines.at(i));

	std::vector<ticket> other_tickets;
	for (i += 2; i < lines.size(); ++i)
	{
		other_tickets.emplace_back(ticket_from_string(lines.at(i)));
	}

	size_t count = 0;

	for (const auto& ticket : other_tickets)
	{
		for (const auto& value : ticket)
		{
			bool failed = true;
			for (const auto& field : fields)
			{
				if ((value >= field.min_1 && value <= field.max_1) || (value >= field.min_2 && value <= field.max_2))
				{
					failed = false;
					break;
				}
			}
			if (failed)
			{
				count += value;
			}
		}
	}

	std::cout << count << std::endl;
}

void aoc::day_16::part_two()
{
	const auto lines = m_input.strings();

	std::vector<field> fields;

	size_t i = 0;
	while (lines.at(i) != "your ticket:")
	{
		fields.emplace_back(field_from_string(lines.at(i)));
		++i;
	}
	++i;
	const ticket my_ticket = ticket_from_string(lines.at(i));

	std::vector<ticket> other_tickets;
	for (i += 2; i < lines.size(); ++i)
	{
		other_tickets.emplace_back(ticket_from_string(lines.at(i)));
	}

	std::vector<ticket> valid_tickets;
	for (const auto& ticket : other_tickets)
	{
		bool any_failed = false;
		for (const auto& value : ticket)
		{
			bool failed = true;
			for (const auto& field : fields)
			{
				if ((value >= field.min_1 && value <= field.max_1) || (value >= field.min_2 && value <= field.max_2))
				{
					failed = false;
					break;
				}
			}
			if (failed)
			{
				any_failed = true;
				break;
			}
		}
		if (!any_failed)
		{
			valid_tickets.emplace_back(ticket);
		}
	}

	std::vector<std::vector<bool>> field_valid_at_pos(fields.size(), std::vector<bool>(fields.size(), true));
	for (const auto& ticket : valid_tickets)
	{
		for (size_t i = 0; i < ticket.size(); ++i)
		{
			const auto& value = ticket.at(i);
			for (size_t j = 0; j < fields.size(); ++j)
			{
				const auto& field = fields.at(j);
				if (!((value >= field.min_1 && value <= field.max_1) || (value >= field.min_2 && value <= field.max_2)))
				{
					field_valid_at_pos.at(j).at(i) = false;
					break;
				}
			}
		}
	}
	field_valid_at_pos = simplify_valids(field_valid_at_pos);

	for (size_t i = 0; i < fields.size(); ++i)
	{
		auto& field = fields.at(i);
		const auto& valid_at_pos = field_valid_at_pos.at(i);

		for (size_t j = 0; j < valid_at_pos.size(); ++j)
		{
			if (valid_at_pos.at(j))
			{
				field.pos = j;
				break;
			}
		}
	}

	unsigned long product = 1;
	for (const auto& field : fields)
	{
		if (field.name.find("departure ") != std::string::npos)
		{
			product *= my_ticket.at(field.pos);
		}
	}

	std::cout << product << std::endl;
}

aoc::day_16::ticket aoc::day_16::ticket_from_string(std::string str)
{
	size_t next_pos = 0;
	ticket t;
	while (next_pos < str.size())
	{
		str = str.substr(next_pos);
		t.emplace_back(std::stoi(str, &next_pos));
		++next_pos;
	}
	return t;
}

aoc::day_16::field aoc::day_16::field_from_string(std::string str)
{
	const auto name_end_pos = str.find(':');
	const auto name = str.substr(0, name_end_pos);

	str = str.substr(name_end_pos + 2);

	size_t next_pos = 0;
	const auto min_1 = std::stoi(str, &next_pos);
	str = str.substr(next_pos + 1);
	const auto max_1 = std::stoi(str, &next_pos);
	str = str.substr(next_pos + 4);
	const auto min_2 = std::stoi(str, &next_pos);
	str = str.substr(next_pos + 1);
	const auto max_2 = std::stoi(str, &next_pos);

	return { .name = name, .min_1 = min_1, .max_1 = max_1, .min_2 = min_2, .max_2 = max_2 };
}

std::vector<std::vector<bool>> aoc::day_16::simplify_valids(std::vector<std::vector<bool>> field_valid_at_pos)
{
	while (!valids_in_simplest_form(field_valid_at_pos))
	{
		// std::vector<std::vector<bool>> next_fields = field_valid_at_pos;
		for (size_t i = 0; i < field_valid_at_pos.size(); ++i)
		{
			const auto& field = field_valid_at_pos.at(i);
			size_t pos = std::string::npos;
			bool simple = true;
			for (size_t j = 0; j < field.size(); ++j)
			{
				const auto& valid_at_pos = field.at(j);
				if (valid_at_pos)
				{
					if (pos == std::string::npos)
					{
						pos = j;
					}
					else
					{
						simple = false;
						break;
					}
				}
			}
			if (simple)
			{
				for (size_t j = 0; j < field_valid_at_pos.size(); ++j)
				{
					if (i == j) continue;
					field_valid_at_pos.at(j).at(pos) = false;
				}
			}
		}
	}
	return field_valid_at_pos;
}

bool aoc::day_16::valids_in_simplest_form(const std::vector<std::vector<bool>>& field_valid_at_pos)
{
	for (const auto& field : field_valid_at_pos)
	{
		size_t count = 0;
		for (const auto& valid_at_pos : field)
		{
			if (valid_at_pos && ++count > 1)
			{
				return false;
			}
		}
	}
	return true;
}

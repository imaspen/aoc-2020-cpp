#include "day_23.hpp"

#include <iostream>

aoc::day_23::day_23(const aoc::input& input) : day(input)
{
	const auto digits = m_input.digits().at(0);
	for (size_t i = 0; i < 9; ++i)
	{
		m_cups.at(i) = digits.at(i);
	}
	for (size_t i = 0; i < 1000000; ++i)
	{
		m_many_cups.at(i).value = i + 1;
	}
	for (size_t i = 9; i < 999999; ++i)
	{
		m_many_cups.at(i).next = &m_many_cups.at(i + 1);
	}

	m_many_cups.back().next = &m_many_cups.at(m_cups.at(0) - 1);
	m_many_cups.at(m_cups.at(8) - 1).next = &m_many_cups.at(9);

	for (size_t i = 0; i < 8; ++i) m_many_cups.at(m_cups.at(i) - 1).next = &m_many_cups.at(m_cups.at(i + 1) - 1);
	m_current_cup = &m_many_cups.at(m_cups.at(0) - 1);
}

void aoc::day_23::part_one()
{
	for (size_t i = 0; i < 100; ++i) play_round();

	std::string res, suffix;

	bool one_found = false;
	for (const auto& c : m_cups)
	{
		if (one_found) res.push_back('0' + c);
		else if (c == 1) one_found = true;
		else suffix.push_back('0' + c);
	}

	res += suffix;

	std::cout << res << std::endl;
}

void aoc::day_23::part_two()
{
	for (size_t i = 0; i < 10000000; ++i) play_many_cups_round();

	std::cout << m_many_cups.at(0).next->value * m_many_cups.at(0).next->next->value << std::endl;
}

void aoc::day_23::play_round()
{
	auto search = m_cups.at(0);

	do
	{
		--search;
		if (search == 0) search = 9;
	} while (m_cups.at(1) == search || m_cups.at(2) == search || m_cups.at(3) == search);

	for (size_t i = 0, offset = 4; i < 8; ++i)
	{
		const auto cup = m_cups.at(i + offset);
		m_cups_next.at(i) = cup;
		if (cup == search)
		{
			m_cups_next.at(i + 1) = m_cups.at(1);
			m_cups_next.at(i + 2) = m_cups.at(2);
			m_cups_next.at(i + 3) = m_cups.at(3);
			i += 3;
			offset = 1;
		}
	}
	m_cups_next.at(8) = m_cups.at(0);

	m_cups.swap(m_cups_next);
}

void aoc::day_23::play_many_cups_round()
{
	auto search = m_current_cup->value;

	auto start_move = m_current_cup->next;
	auto end_move = start_move->next->next;

	m_current_cup->next = end_move->next;

	do
	{
		--search;
		if (search == 0) search = 1000000;
	} while (start_move->value == search || start_move->next->value == search || end_move->value == search);

	auto& search_cup = m_many_cups.at(search - 1);

	end_move->next = search_cup.next;
	search_cup.next = start_move;
	m_current_cup = m_current_cup->next;
}

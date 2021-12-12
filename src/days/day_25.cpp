#include "day_25.hpp"

#include <iostream>

aoc::day_25::day_25(const aoc::input& input) : day(input)
{
	const auto ints = m_input.ints();
	m_card_public_key = ints.at(0);
	m_door_public_key = ints.at(1);
}

void aoc::day_25::part_one()
{
	std::cout << calculate_encryption_key(get_loop_size_for_key(m_card_public_key), m_door_public_key) << std::endl;
}

void aoc::day_25::part_two()
{
}

size_t aoc::day_25::get_loop_size_for_key(key k)
{
	size_t loop_size = 0;
	key v = 1;
	while (true)
	{
		++loop_size;
		v *= 7;
		v %= 20201227;
		if (v == k) return loop_size;
	}
}

aoc::day_25::key aoc::day_25::calculate_encryption_key(size_t loop_size, key other_public_key)
{
	key value = 1;
	for (size_t i = 0; i < loop_size; ++i)
	{
		value *= other_public_key;
		value %= 20201227;
	}
	return value;
}

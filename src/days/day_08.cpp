#include "day_08.hpp"

#include <iostream>

#include "../objects/console.hpp"

void aoc::day_08::part_one()
{
	auto console = aoc::console(m_input.strings());
	std::cout << console.run() << std::endl;
}

void aoc::day_08::part_two()
{
	auto console = aoc::console(m_input.strings());
	std::cout << console.fix_loop() << std::endl;
}

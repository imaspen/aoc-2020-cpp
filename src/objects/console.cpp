#include "console.hpp"

#include <iostream>

aoc::console::opcode aoc::console::string_to_opcode(const std::string& str)
{
	if (str == "acc") return aoc::console::opcode::ACC;
	else if (str == "jmp") return aoc::console::opcode::JMP;
	else if (str == "nop") return aoc::console::opcode::NOP;
	else throw aoc::opcode_not_recognized_exception(str);
}

aoc::console::console(const std::vector<std::string>& lines)
{
	for (const auto& line : lines)
	{
		const auto opcode = string_to_opcode(line.substr(0, 3));
		const auto value = std::stol(line.substr(4));
		m_instructions.emplace_back(opcode, value);
	}
}

long aoc::console::run()
{
	while (m_run_instructions.count(m_program_counter) == 0 && m_program_counter < m_instructions.size())
	{
		m_run_instructions.emplace(m_program_counter);
		const auto& instruction = m_instructions.at(m_program_counter);

		switch (instruction.opcode)
		{
		case aoc::console::opcode::ACC:
			m_accumulator += instruction.value;
			++m_program_counter;
			break;
		case aoc::console::opcode::JMP:
			m_program_counter += instruction.value;
			break;
		case aoc::console::opcode::NOP:
		default:
			++m_program_counter;
		}
	}

	return m_accumulator;
}

long aoc::console::fix_loop()
{
	for (auto& instruction : m_instructions)
	{
		m_accumulator = 0;
		m_program_counter = 0;
		m_run_instructions = std::set<size_t>();

		if (instruction.opcode == aoc::console::opcode::NOP)
		{
			instruction.opcode = aoc::console::opcode::JMP;
			run();
			instruction.opcode = aoc::console::opcode::NOP;
		}
		else if (instruction.opcode == aoc::console::opcode::JMP)
		{
			instruction.opcode = aoc::console::opcode::NOP;
			run();
			instruction.opcode = aoc::console::opcode::JMP;
		}

		if (m_program_counter >= m_instructions.size())
		{
			return m_accumulator;
		}
	}

	throw aoc::unfixable_instructions_exception();
}

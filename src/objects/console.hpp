#pragma once

#include <exception>
#include <set>
#include <string>
#include <vector>

namespace aoc
{
	class opcode_not_recognized_exception : public std::exception
	{
	public:
		opcode_not_recognized_exception(const std::string& instruction) : opcode(instruction) {};
		std::string opcode;
	};

	class unfixable_instructions_exception : public std::exception {};

	class console
	{
	public:
		enum opcode
		{
			ACC,
			JMP,
			NOP,
		};

		struct instruction
		{
			instruction(opcode opcode, long value) : opcode(opcode), value(value) {};
			opcode opcode;
			long value;
		};

		static opcode string_to_opcode(const std::string& str);

		console(const std::vector<instruction>& instructions) : m_instructions(instructions) {};
		console(const std::vector<std::string>& lines);

		long run();
		long fix_loop();

	private:
		std::vector<instruction> m_instructions;
		std::set<size_t> m_run_instructions;

		size_t m_program_counter = 0;
		long m_accumulator = 0;
	};
}

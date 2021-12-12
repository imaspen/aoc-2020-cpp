#pragma once

#include <array>
#include <memory>

#include "day.hpp"

namespace aoc
{
	class day_23 : public aoc::day
	{
	public:
		day_23(const aoc::input& input);

		virtual void part_one() override;
		virtual void part_two() override;

	private:
		typedef unsigned long cup;
		typedef std::array<cup, 9> cups;

		struct smart_cup
		{
			cup value;
			smart_cup* next;
		};

		typedef std::array<smart_cup, 1000000> many_cups;

		void play_round();
		void play_many_cups_round();

		cups m_cups, m_cups_next;
		many_cups m_many_cups;
		smart_cup* m_current_cup;
	};
}

#pragma once

#include <deque>

#include "day.hpp"

namespace aoc
{
	class day_22 : public aoc::day
	{
	public:
		day_22(const aoc::input& input);

		virtual void part_one() override;
		virtual void part_two() override;

	private:
		typedef unsigned long card;
		typedef std::deque<card> deck;

		bool play_sub_game(deck deck_1, deck deck_2);

		deck deck_1, deck_2;
	};
}

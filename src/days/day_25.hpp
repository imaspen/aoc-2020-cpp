#pragma once

#include "day.hpp"

namespace aoc
{
	class day_25 : public aoc::day
	{
	public:
		day_25(const aoc::input& input);

		virtual void part_one() override;
		virtual void part_two() override;

	private:
		typedef unsigned long key;

		size_t get_loop_size_for_key(key k);
		key calculate_encryption_key(size_t loop_size, key other_public_key);

		key m_card_public_key, m_door_public_key;
	};
}

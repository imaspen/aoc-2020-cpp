#pragma once

#include "day.hpp"

#include <queue>

namespace aoc
{
	class day_12 : public aoc::day
	{
	public:
		day_12(const aoc::input& input);

		virtual void part_one() override;
		virtual void part_two() override;

		enum action
		{
			NORTH = 'N',
			SOUTH = 'S',
			EAST = 'E',
			WEST = 'W',
			LEFT = 'L',
			RIGHT = 'R',
			FORWARD = 'F',
		};

		struct instruction
		{
			action action;
			unsigned long value;
		};

	private:
		void rotate(const action& dir, const unsigned long& value);
		void rotate_waypoint(const action& dir, const unsigned long& value);
		void move(const action& dir, const unsigned long& value);
		void move_waypoint(const action& dir, const unsigned long& value);

		std::queue<instruction> m_instructions;
		action m_direction = action::EAST;
		long x = 0, y = 0, waypoint_x = 10, waypoint_y = 1;
	};

	class invalid_action_exception : std::exception
	{
	public:
		invalid_action_exception(const aoc::day_12::action& action) : action(action) {};
		aoc::day_12::action action;
	};

	class invalid_rotation_exception : std::exception
	{
	public:
		invalid_rotation_exception(const aoc::day_12::action& action, const unsigned long& value) : action(action), value(value) {};
		aoc::day_12::action action;
		unsigned long value;
	};

	class invalid_move_exception : std::exception
	{
	public:
		invalid_move_exception(const aoc::day_12::action& action, const unsigned long& value) : action(action), value(value) {};
		aoc::day_12::action action;
		unsigned long value;
	};
}

#include "day_12.hpp"

#include <iostream>

aoc::day_12::day_12(const aoc::input& input) : day(input)
{
	const auto& lines = m_input.strings();
	for (const auto& line : lines)
	{
		m_instructions.push({
			.action = static_cast<action>(line.at(0)),
			.value = std::stoul(line.substr(1)) });
	}
}

void aoc::day_12::part_one()
{
	while (!m_instructions.empty())
	{
		const auto& instruction = m_instructions.front();
		switch (instruction.action)
		{
		case action::NORTH:
		case action::SOUTH:
		case action::EAST:
		case action::WEST:
			move(instruction.action, instruction.value);
			break;
		case action::FORWARD:
			move(m_direction, instruction.value);
			break;
		case action::LEFT:
		case action::RIGHT:
			rotate(instruction.action, instruction.value);
			break;
		default:
			throw invalid_action_exception(instruction.action);
		}
		m_instructions.pop();
	}

	std::cout << std::abs(x) + std::abs(y) << std::endl;
}

void aoc::day_12::part_two()
{
	while (!m_instructions.empty())
	{
		const auto& instruction = m_instructions.front();
		switch (instruction.action)
		{
		case action::NORTH:
		case action::SOUTH:
		case action::EAST:
		case action::WEST:
			move_waypoint(instruction.action, instruction.value);
			break;
		case action::LEFT:
		case action::RIGHT:
			rotate_waypoint(instruction.action, instruction.value);
			break;
		case action::FORWARD:
			x += waypoint_x * instruction.value;
			y += waypoint_y * instruction.value;
			break;
		default:
			throw invalid_action_exception(instruction.action);
		}
		m_instructions.pop();
	}

	std::cout << std::abs(x) + std::abs(y) << std::endl;
}

void aoc::day_12::rotate(const action& dir, const unsigned long& value)
{
	if ((dir == action::RIGHT && value == 90) || (dir == action::LEFT && value == 270))
	{
		if (m_direction == action::NORTH)
		{
			m_direction = action::EAST;
		}
		else if (m_direction == action::EAST)
		{
			m_direction = action::SOUTH;
		}
		else if (m_direction == action::SOUTH)
		{
			m_direction = action::WEST;
		}
		else if (m_direction == action::WEST)
		{
			m_direction = action::NORTH;
		}
	}
	else if ((dir == action::RIGHT || dir == action::LEFT) && value == 180)
	{
		if (m_direction == action::NORTH)
		{
			m_direction = action::SOUTH;
		}
		else if (m_direction == action::SOUTH)
		{
			m_direction = action::NORTH;
		}
		else if (m_direction == action::EAST)
		{
			m_direction = action::WEST;
		}
		else if (m_direction == action::WEST)
		{
			m_direction = action::EAST;
		}
	}
	else if ((dir == action::RIGHT && value == 270) || (dir == action::LEFT && value == 90))
	{
		if (m_direction == action::NORTH)
		{
			m_direction = action::WEST;
		}
		else if (m_direction == action::WEST)
		{
			m_direction = action::SOUTH;
		}
		else if (m_direction == action::SOUTH)
		{
			m_direction = action::EAST;
		}
		else if (m_direction == action::EAST)
		{
			m_direction = action::NORTH;
		}
	}
	else
	{
		throw invalid_rotation_exception(dir, value);
	}
}

void aoc::day_12::move(const action& dir, const unsigned long& value)
{
	if (dir == action::NORTH)
	{
		y += value;
	}
	else if (dir == action::SOUTH)
	{
		y -= value;
	}
	else if (dir == action::EAST)
	{
		x += value;
	}
	else if (dir == action::WEST)
	{
		x -= value;
	}
	else
	{
		throw aoc::invalid_move_exception(dir, value);
	}
}

void aoc::day_12::rotate_waypoint(const action& dir, const unsigned long& value)
{
	if ((dir == action::RIGHT && value == 90) || (dir == action::LEFT && value == 270))
	{
		const auto cy = waypoint_y;
		waypoint_y = -waypoint_x;
		waypoint_x = cy;
	}
	else if ((dir == action::RIGHT || dir == action::LEFT) && value == 180)
	{
		waypoint_x *= -1;
		waypoint_y *= -1;
	}
	else if ((dir == action::RIGHT && value == 270) || (dir == action::LEFT && value == 90))
	{
		const auto cx = waypoint_x;
		waypoint_x = -waypoint_y;
		waypoint_y = cx;
	}
	else
	{
		throw invalid_rotation_exception(dir, value);
	}
}

void aoc::day_12::move_waypoint(const action& dir, const unsigned long& value)
{
	if (dir == action::NORTH)
	{
		waypoint_y += value;
	}
	else if (dir == action::SOUTH)
	{
		waypoint_y -= value;
	}
	else if (dir == action::EAST)
	{
		waypoint_x += value;
	}
	else if (dir == action::WEST)
	{
		waypoint_x -= value;
	}
	else
	{
		throw invalid_move_exception(dir, value);
	}
}

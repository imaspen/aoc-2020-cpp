#include "day_18.hpp"

#include <iostream>
#include <stack>

void aoc::day_18::part_one()
{
	const auto lines = m_input.strings();
	unsigned long sum = 0;
	for (const auto& line : lines)
	{
		sum += solve_equation(strip_spaces(line));
	}
	std::cout << sum << std::endl;
}

void aoc::day_18::part_two()
{
	const auto lines = m_input.strings();
	unsigned long sum = 0;
	for (const auto& line : lines)
	{
		sum += solve_equation_prioritized(strip_spaces(line));
	}
	std::cout << sum << std::endl;
}

std::string aoc::day_18::strip_spaces(const std::string& str)
{
	std::string stripped;
	for (const auto& c : str)
	{
		if (c != ' ') stripped.push_back(c);
	}
	return stripped;
}

unsigned long aoc::day_18::solve_equation(std::string equation)
{
	std::stack<unsigned long> sums({ 0 });
	std::stack<char> operators({ '+' });
	while (!equation.empty())
	{
		const auto& c = equation.at(0);
		if (c >= '0' && c <= '9')
		{
			size_t next_pos;
			const auto val = std::stoul(equation, &next_pos);
			const auto op = operators.top();
			operators.pop();
			if (op == '+') sums.top() += val;
			else if (op == '*') sums.top() *= val;
			equation = equation.substr(next_pos);
		}
		else if (c == '+' || c == '*')
		{
			operators.emplace(c);
			equation = equation.substr(1);
		}
		else if (c == '(')
		{
			sums.emplace(0);
			operators.emplace('+');
			equation = equation.substr(1);
		}
		else if (c == ')')
		{
			const auto val = sums.top();
			sums.pop();
			const auto op = operators.top();
			operators.pop();
			if (op == '+') sums.top() += val;
			else if (op == '*') sums.top() *= val;
			equation = equation.substr(1);
		}
		else throw unrecognized_equation_char_exception(c);
	}
	return sums.top();
}

unsigned long aoc::day_18::solve_equation_prioritized(std::string equation)
{
	std::stack<unsigned long> sums({ 0 });
	std::stack<char> operators({ '+' });
	while (!equation.empty())
	{
		const auto& c = equation.at(0);
		if (c >= '0' && c <= '9')
		{
			size_t next_pos;
			const auto val = std::stoul(equation, &next_pos);
			const auto op = operators.top();
			operators.pop();
			if (op == '+') sums.top() += val;
			else if (op == '*') sums.top() *= val;
			equation = equation.substr(next_pos);
		}
		else if (c == '+')
		{
			operators.emplace(c);
			equation = equation.substr(1);
		}
		else if (c == '*')
		{
			operators.emplace('*');
			operators.emplace('+');
			sums.emplace(0);
			equation = equation.substr(1);
		}
		else if (c == '(')
		{
			sums.emplace(0);
			operators.emplace('+');
			equation = equation.substr(1);
		}
		else if (c == ')')
		{
			char op;
			do {
				const auto val = sums.top();
				sums.pop();
				op = operators.top();
				operators.pop();
				if (op == '+') sums.top() += val;
				else if (op == '*') sums.top() *= val;
			} while (op == '*');
			equation = equation.substr(1);
		}
		else throw unrecognized_equation_char_exception(c);
	}
	while (!operators.empty())
	{
		const auto val = sums.top();
		sums.pop();
		const auto op = operators.top();
		operators.pop();
		if (op == '+') sums.top() += val;
		else if (op == '*') sums.top() *= val;
	}
	return sums.top();
}

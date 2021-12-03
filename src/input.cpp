#include "input.hpp"

#include <fstream>
#include <iostream>
#include <string>

constexpr auto format = "inputs/%s%02d.txt";
aoc::input::input(bool test, int day)
{
	const auto testStr = test ? "test/" : "";
	const auto size = std::snprintf(nullptr, 0, format, testStr, day);
	std::string path(size + 1, '\0');
	std::sprintf(&path[0], format, testStr, day);
	std::ifstream file(path);

	if (file.is_open())
	{
		while (file.good())
		{
			std::string line;
			std::getline(file, line);
			m_lines_raw.emplace_back(line);
			if (line != "")
			{
				m_lines.emplace_back(line);
			}
		}
		file.close();
	}
	else
	{
		throw aoc::file_not_found_exception(path);
	}
}

std::vector<std::string> aoc::input::strings(bool raw) const
{
	return raw ? m_lines_raw : m_lines;
}

std::vector<int> aoc::input::ints() const
{
	std::vector<int> lines(m_lines.size());
	for (size_t i = 0; i < lines.size(); ++i)
	{
		lines.at(i) = stoi(m_lines.at(i));
	}
	return lines;
}

std::vector<std::tuple<std::string, std::string>> aoc::input::string_string_tuples() const
{
	std::vector<std::tuple<std::string, std::string>> lines(m_lines.size());
	for (size_t i = 0; i < lines.size(); ++i)
	{
		const auto &line = m_lines.at(i);
		const auto split_idx = line.find_first_of(' ');
		lines.at(i) = std::make_tuple(line.substr(0, split_idx), line.substr(split_idx + 1, std::string::npos));
	}
	return lines;
}

std::vector<std::tuple<std::string, int>> aoc::input::string_int_tuples() const
{
	std::vector<std::tuple<std::string, int>> lines(m_lines.size());
	for (size_t i = 0; i < lines.size(); ++i)
	{
		const auto &line = m_lines.at(i);
		const auto split_idx = line.find_first_of(' ');
		lines.at(i) = std::tuple<std::string, int>(
			line.substr(0, split_idx),
			std::stoi(line.substr(split_idx + 1, std::string::npos)));
	}
	return lines;
}

std::vector<std::vector<bool>> aoc::input::bits() const
{
	std::vector<std::vector<bool>> lines(m_lines.size());
	for (size_t i = 0; i < lines.size(); ++i)
	{
		lines.at(i) = std::vector<bool>(m_lines.at(i).size());
		auto &line = lines.at(i);
		const auto &str = m_lines.at(i);
		for (size_t j = 0; j < str.size(); ++j)
		{
			line.at(j) = str.at(j) == '1';
		}
	}
	return lines;
}

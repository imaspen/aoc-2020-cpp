#pragma once

#include <string>
#include <tuple>
#include <vector>

namespace aoc
{
	class file_not_found_exception : public std::exception
	{
	public:
		file_not_found_exception(const std::string &path) : path(path){};
		const std::string path;
	};

	class input
	{
	public:
		input(bool test, int day);

		std::vector<std::string> strings() { return m_lines; }

		std::vector<int> ints();

		std::vector<std::tuple<std::string, std::string>> string_string_tuples();

		std::vector<std::tuple<std::string, int>> string_int_tuples();

		std::vector<std::vector<bool>> bits() const;

	private:
		std::vector<std::string> m_lines;
	};
};

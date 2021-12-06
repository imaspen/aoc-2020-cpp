#pragma once

#include <map>

#include "day.hpp"

namespace aoc
{
	class day_17 : public aoc::day
	{
	public:
		using day::day;

		virtual void part_one() override;
		virtual void part_two() override;

	private:
		void parse_input();
		void parse_input_4d();

		void cycle();
		void cycle_4d();

		bool get_point(const int& x, const int& y, const int& z);
		bool get_point_4d(const int& x, const int& y, const int& z, const int& w);

		size_t get_adjacent(const int& x, const int& y, const int& z, const bool& active);
		size_t get_adjacent_4d(const int& x, const int& y, const int& z, const int& w, const bool& active);

		void set_point(const int& x, const int& y, const int& z, const bool& active);
		void set_point_4d(const int& x, const int& y, const int& z, const int& w, const bool& active);

		void increment_adjacency_count(const int& x, const int& y, const int& z, const bool& active);
		void increment_adjacency_count_4d(const int& x, const int& y, const int& z, const int& w, const bool& active);

		size_t count_active();
		size_t count_active_4d();

		typedef std::map<int, std::map<int, std::map<int, bool>>> points;
		typedef std::map<int, std::map<int, std::map<int, int>>> counts;
		points m_points, m_next_points;
		std::map<int, points> m_points_4d, m_next_points_4d;
		counts m_adjacency_counts;
		std::map<int, counts> m_adjacency_counts_4d;
	};
}

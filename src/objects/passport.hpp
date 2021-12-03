#pragma once

#include <string>
#include <vector>

namespace aoc
{
	class field_exception : public std::exception
	{
	public:
		field_exception(std::string field) : field(field){};

		std::string field;
	};

	class missing_required_field_exception : public aoc::field_exception
	{
	public:
		using field_exception::field_exception;
	};

	class invalid_required_field_exception : public aoc::field_exception
	{
	public:
		invalid_required_field_exception(std::string field, std::string value) : field_exception(field), value(value){};

		std::string value;
	};

	class passport
	{
	public:
		passport(int, int, int, int, std::string, std::string, std::string, std::string);

		static aoc::passport from_string(const std::string &string);

		static bool hair_color_valid(const std::string &hcl);
		static bool eye_color_valid(const std::string &ecl);
		static bool passport_id_valid(const std::string &pid);

		static inline const std::vector<std::string> REQUIRED_FIELDS = std::vector<std::string>({
			"byr",
			"iyr",
			"eyr",
			"hgt",
			"hcl",
			"ecl",
			"pid",
		});

		static inline const std::vector<std::string> EYE_COLORS = std::vector<std::string>({
			"amb",
			"blu",
			"brn",
			"gry",
			"grn",
			"hzl",
			"oth",
		});

	private:
		int byr, iyr, eyr, hgt_amount;
		std::string hcl, ecl, pid, hgt_unit;
	};
}

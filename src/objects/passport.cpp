#include "passport.hpp"

#include <iostream>

aoc::passport::passport(int _byr, int _iyr, int _eyr, int _hgt_amount, std::string _hgt_unit, std::string _hcl, std::string _ecl, std::string _pid)
{
	if (_byr >= 1920 && _byr <= 2002)
	{
		byr = _byr;
	}
	else
	{
		throw aoc::invalid_required_field_exception("byr", std::to_string(_byr));
	}

	if (_iyr >= 2010 && _iyr <= 2020)
	{
		iyr = _iyr;
	}
	else
	{
		throw aoc::invalid_required_field_exception("iyr", std::to_string(_iyr));
	}

	if (_eyr >= 2020 && _eyr <= 2030)
	{
		eyr = _eyr;
	}
	else
	{
		throw aoc::invalid_required_field_exception("eyr", std::to_string(_eyr));
	}

	if (
		(_hgt_unit == "cm" && _hgt_amount >= 150 && _hgt_amount <= 193) ||
		(_hgt_unit == "in" && _hgt_amount >= 59 && _hgt_amount <= 76))
	{
		hgt_amount = _hgt_amount;
		hgt_unit = _hgt_unit;
	}
	else
	{
		throw aoc::invalid_required_field_exception("hgt", std::to_string(_hgt_amount) + _hgt_unit);
	}

	if (hair_color_valid(_hcl))
	{
		hcl = _hcl;
	}
	else
	{
		throw aoc::invalid_required_field_exception("hcl", _hcl);
	}

	if (eye_color_valid(_ecl))
	{
		ecl = _ecl;
	}
	else
	{
		throw aoc::invalid_required_field_exception("ecl", _ecl);
	}

	if (passport_id_valid(_pid))
	{
		pid = _pid;
	}
	else
	{
		throw aoc::invalid_required_field_exception("pid", _pid);
	}
}

aoc::passport aoc::passport::from_string(const std::string &string)
{
	int byr = 0, iyr = 0, eyr = 0, hgt_amount = 0;
	std::string hgt_unit, hgt, hcl, ecl, pid;

	for (const auto &field : REQUIRED_FIELDS)
	{
		size_t pos = string.find(field);
		if (pos == std::string::npos)
		{
			throw aoc::missing_required_field_exception(field);
		}
		size_t data_pos = pos + 4;
		size_t end_pos = string.find(" ", data_pos);
		const auto data = string.substr(data_pos, end_pos - data_pos);

		if (field == "byr")
		{
			byr = stoi(data);
		}
		else if (field == "iyr")
		{
			iyr = stoi(data);
		}
		else if (field == "eyr")
		{
			eyr = stoi(data);
		}
		else if (field == "hgt")
		{
			size_t remainder = std::string::npos;
			hgt_amount = stoi(data, &remainder);
			hgt_unit = data.substr(remainder);
		}
		else if (field == "hcl")
		{
			hcl = data;
		}
		else if (field == "ecl")
		{
			ecl = data;
		}
		else if (field == "pid")
		{
			pid = data;
		}
	}

	return aoc::passport(byr, iyr, eyr, hgt_amount, hgt_unit, hcl, ecl, pid);
}

bool aoc::passport::hair_color_valid(const std::string &hcl)
{
	if (hcl.size() != 7)
	{
		return false;
	}

	for (const char &c : hcl.substr(1))
	{
		if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f')))
		{
			return false;
		}
	}

	return true;
}

bool aoc::passport::eye_color_valid(const std::string &ecl)
{
	for (const std::string &color : EYE_COLORS)
	{
		if (color == ecl)
		{
			return true;
		}
	}
	return false;
}

bool aoc::passport::passport_id_valid(const std::string &pid)
{
	if (pid.size() != 9)
	{
		return false;
	}

	for (const char &c : pid)
	{
		if (c < '0' || c > '9')
		{
			return false;
		}
	}

	return true;
}

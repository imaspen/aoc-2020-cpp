#include <iostream>
#include <string>

#include "input.hpp"
#include "days/day.hpp"
#include "days/day_01.hpp"
#include "days/day_02.hpp"
#include "days/day_03.hpp"
#include "days/day_04.hpp"
#include "days/day_05.hpp"
#include "days/day_06.hpp"
#include "days/day_07.hpp"
#include "days/day_08.hpp"
#include "days/day_09.hpp"
#include "days/day_10.hpp"
#include "days/day_11.hpp"
#include "days/day_12.hpp"
#include "days/day_13.hpp"
#include "days/day_14.hpp"
#include "days/day_15.hpp"
#include "days/day_16.hpp"
#include "days/day_17.hpp"
#include "days/day_18.hpp"

void print_usage()
{
	std::cout << "Usage: aoc\n";
	std::cout << "\t-t\t\tRun with test input\n";
	std::cout << "\t-d<day>\t\tRequired. Day number (1-25)\n";
	std::cout << "\t-p<part>\tRequired. Part number (1-2)" << std::endl;
}

int main(int argc, const char* argv[])
{
	int day = 0;
	int part = 0;
	bool test = false;

	for (int i = 1; i < argc; ++i)
	{
		if (argv[i][0] != '-')
		{
			std::cout << "Invalid argument: " << argv[i] << std::endl;
			print_usage();
			return 1;
		}

		switch (argv[i][1])
		{
		case 't':
			test = argv[i][2] != '0';
			continue;
		case 'd':
			day = atoi(&argv[i][2]);
			if (day < 1 || day > 25)
			{
				std::cout << "Invalid day passed: " << &argv[i][2] << std::endl;
				print_usage();
				return 1;
			}
			continue;
		case 'p':
			part = atoi(&argv[i][2]);
			if (part < 1 || part > 2)
			{
				std::cout << "Invalid part passed: " << &argv[i][2] << std::endl;
				print_usage();
				return 1;
			}
			continue;
		default:
			std::cout << "Invalid argument: " << argv[i] << std::endl;
			print_usage();
			return 1;
		}
	}

	if (day == 0)
	{
		std::cout << "Day not passed." << std::endl;
		print_usage();
		return 1;
	}

	if (part == 0)
	{
		std::cout << "Part not passed." << std::endl;
		print_usage();
		return 1;
	}

	try
	{
		aoc::input input(test, day);

		std::unique_ptr<aoc::day> day_ptr;

		switch (day)
		{
		case 1:
			day_ptr = std::make_unique<aoc::day_01>(input);
			break;
		case 2:
			day_ptr = std::make_unique<aoc::day_02>(input);
			break;
		case 3:
			day_ptr = std::make_unique<aoc::day_03>(input);
			break;
		case 4:
			day_ptr = std::make_unique<aoc::day_04>(input);
			break;
		case 5:
			day_ptr = std::make_unique<aoc::day_05>(input);
			break;
		case 6:
			day_ptr = std::make_unique<aoc::day_06>(input);
			break;
		case 7:
			day_ptr = std::make_unique<aoc::day_07>(input);
			break;
		case 8:
			day_ptr = std::make_unique<aoc::day_08>(input);
			break;
		case 9:
			day_ptr = std::make_unique<aoc::day_09>(input);
			break;
		case 10:
			day_ptr = std::make_unique<aoc::day_10>(input);
			break;
		case 11:
			day_ptr = std::make_unique<aoc::day_11>(input);
			break;
		case 12:
			day_ptr = std::make_unique<aoc::day_12>(input);
			break;
		case 13:
			day_ptr = std::make_unique<aoc::day_13>(input);
			break;
		case 14:
			day_ptr = std::make_unique<aoc::day_14>(input);
			break;
		case 15:
			day_ptr = std::make_unique<aoc::day_15>(input);
			break;
		case 16:
			day_ptr = std::make_unique<aoc::day_16>(input);
			break;
		case 17:
			day_ptr = std::make_unique<aoc::day_17>(input);
			break;
		case 18:
			day_ptr = std::make_unique<aoc::day_18>(input);
			break;
		default:
			std::cout << "Unimplemented." << std::endl;
			return 1;
		}

		switch (part)
		{
		case 1:
			day_ptr->part_one();
			break;
		case 2:
			day_ptr->part_two();
			break;
		default:
			std::cout << "Part " << part << "out of range." << std::endl;
			print_usage();
			return 1;
		}
	}
	catch (aoc::file_not_found_exception exception)
	{
		std::cout << "File not found: " << exception.path << std::endl;
		return 1;
	}

	return 0;
}

#include "day_14.hpp"

#include <iostream>
#include <map>

void aoc::day_14::part_one()
{
	const auto lines = m_input.strings();
	unsigned long zeros_mask, ones_mask;
	std::map<unsigned long, unsigned long> memory;

	for (const auto& line : lines)
	{
		const auto& c = line.at(1);
		if (c == 'a')
		{
			std::string mask = line.substr(7);
			zeros_mask = ULONG_MAX;
			ones_mask = 0;
			for (const auto& c : mask)
			{
				zeros_mask <<= 1;
				ones_mask <<= 1;
				if (c != '0')
				{
					++zeros_mask;
				}
				if (c == '1')
				{
					++ones_mask;
				}
			}
		}
		else if (c == 'e')
		{
			const auto mem_end = line.find(']');
			const auto mem_address = std::stoul(line.substr(4, mem_end - 4));
			const auto to_write = (std::stoul(line.substr(mem_end + 4)) & zeros_mask) | ones_mask;
			memory.insert_or_assign(mem_address, to_write);
		}
	}

	unsigned long total = 0;
	for (const auto& mem : memory)
	{
		total += mem.second;
	}
	std::cout << total << std::endl;
}

void aoc::day_14::part_two()
{
	const auto lines = m_input.strings();

	std::map<unsigned long, unsigned long> memory;
	std::vector<std::tuple<unsigned long, unsigned long>> masks;

	for (const auto& line : lines)
	{
		const auto& c = line.at(1);
		if (c == 'a')
		{
			auto mask = line.substr(7);
			for (auto& c : mask)
			{
				c = c == '0' ? ' ' : c;
			}

			std::vector<std::string> str_masks({ mask });
			size_t mask_pos = find_mask_with_x(str_masks);
			while (mask_pos != std::string::npos)
			{
				auto mask = str_masks.at(mask_pos);
				str_masks.erase(str_masks.begin() + mask_pos);
				const auto x_pos = mask.find('X');
				mask.at(x_pos) = '0';
				str_masks.push_back(mask);
				mask.at(x_pos) = '1';
				str_masks.push_back(mask);
				mask_pos = find_mask_with_x(str_masks);
			}

			masks = std::vector<std::tuple<unsigned long, unsigned long>>();
			for (const auto& str_mask : str_masks)
			{
				unsigned long zeros_mask = ULONG_MAX;
				unsigned long ones_mask = 0;
				for (const auto& c : str_mask)
				{
					zeros_mask <<= 1;
					ones_mask <<= 1;
					if (c != '0')
					{
						++zeros_mask;
					}
					if (c == '1')
					{
						++ones_mask;
					}
				}
				masks.push_back(std::make_tuple(zeros_mask, ones_mask));
			}
		}
		else if (c == 'e')
		{
			const auto mem_end = line.find(']');
			const auto base_mem_address = std::stoul(line.substr(4, mem_end - 4));
			const auto to_write = std::stoul(line.substr(mem_end + 4));
			for (const auto& mask : masks)
			{
				unsigned long zeros_mask, ones_mask;
				std::tie(zeros_mask, ones_mask) = mask;
				const auto mem_address = (base_mem_address & zeros_mask) | ones_mask;

				memory.insert_or_assign(mem_address, to_write);
			}
		}
	}

	unsigned long total = 0;
	for (const auto& mem : memory)
	{
		total += mem.second;
	}
	std::cout << total << std::endl;
}

size_t aoc::day_14::find_mask_with_x(const std::vector<std::string>& masks)
{
	for (size_t i = 0; i < masks.size(); ++i)
	{
		const auto& pos = masks.at(i).find('X');
		if (pos != std::string::npos) return i;
	}
	return std::string::npos;
}

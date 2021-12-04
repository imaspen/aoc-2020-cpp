#pragma once

#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

namespace aoc
{
	class bag
	{
	public:
		bag(const std::string &description) : description(description){};

		size_t get_bags_count();

		struct content
		{
			size_t count;
			std::shared_ptr<bag> type;
		};

		static std::string description_from_string(const std::string &line);
		static std::vector<bag::content> content_from_string(const std::string &line, const std::map<std::string, std::shared_ptr<bag>> &bags);

		std::string description;
		std::vector<content> can_contain;
		std::vector<std::shared_ptr<bag>> contained_by;
	};
}

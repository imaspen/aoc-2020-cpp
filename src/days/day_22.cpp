#include "day_22.hpp"

#include <iostream>
#include <set>

aoc::day_22::day_22(const aoc::input& input) : aoc::day(input)
{
	bool player_2 = false;
	for (const auto& line : m_input.strings())
	{
		if (line == "Player 1:") continue;
		if (line == "Player 2:")
		{
			player_2 = true;
			continue;
		}

		const auto c = std::stoi(line);

		if (player_2) deck_2.push_back(c);
		else deck_1.push_back(c);
	}
}

void aoc::day_22::part_one()
{
	while (deck_1.size() > 0 && deck_2.size() > 0)
	{
		const auto card_1 = deck_1.front();
		deck_1.pop_front();
		const auto card_2 = deck_2.front();
		deck_2.pop_front();
		if (card_1 > card_2)
		{
			deck_1.push_back(card_1);
			deck_1.push_back(card_2);
		}
		else
		{
			deck_2.push_back(card_2);
			deck_2.push_back(card_1);
		}
	}

	size_t i = 0, score = 0;
	auto& winning_deck = deck_1.size() > 0 ? deck_1 : deck_2;
	while (winning_deck.size() > 0)
	{
		score += ++i * winning_deck.back();
		winning_deck.pop_back();
	}

	std::cout << score << std::endl;
}

void aoc::day_22::part_two()
{
	std::set<deck> previous_deck_1s, previous_deck_2s;
	while (deck_1.size() > 0 && deck_2.size() > 0)
	{
		if (!previous_deck_1s.insert(deck_1).second) break;
		if (!previous_deck_2s.insert(deck_2).second) break;

		const auto card_1 = deck_1.front();
		deck_1.pop_front();
		const auto card_2 = deck_2.front();
		deck_2.pop_front();

		bool player_1_won;
		auto it_1 = deck_1.begin(), it_2 = deck_2.begin();
		if (deck_1.size() >= card_1 && deck_2.size() >= card_2)
		{
			deck sub_1, sub_2;
			for (size_t i = 0; i < card_1; ++i) sub_1.push_back(*it_1++);
			for (size_t i = 0; i < card_2; ++i) sub_2.push_back(*it_2++);
			player_1_won = play_sub_game(sub_1, sub_2);
		}
		else player_1_won = card_1 > card_2;

		if (player_1_won)
		{
			deck_1.push_back(card_1);
			deck_1.push_back(card_2);
		}
		else
		{
			deck_2.push_back(card_2);
			deck_2.push_back(card_1);
		}
	}

	size_t i = 0, score = 0;
	auto& winning_deck = deck_1.size() == 0 ? deck_2 : deck_1;
	while (winning_deck.size() > 0)
	{
		score += ++i * winning_deck.back();
		winning_deck.pop_back();
	}

	std::cout << score << std::endl;
}

// true when player 1 wins, false when player_2 wins
bool aoc::day_22::play_sub_game(deck deck_1, deck deck_2)
{
	std::set<deck> previous_deck_1s, previous_deck_2s;
	while (deck_1.size() > 0 && deck_2.size() > 0)
	{
		if (!previous_deck_1s.insert(deck_1).second) return true;
		if (!previous_deck_2s.insert(deck_2).second) return true;

		const auto card_1 = deck_1.front();
		deck_1.pop_front();
		const auto card_2 = deck_2.front();
		deck_2.pop_front();

		bool player_1_won;
		auto it_1 = deck_1.begin(), it_2 = deck_2.begin();
		if (deck_1.size() >= card_1 && deck_2.size() >= card_2)
		{
			deck sub_1, sub_2;
			for (size_t i = 0; i < card_1; ++i) sub_1.push_back(*it_1++);
			for (size_t i = 0; i < card_2; ++i) sub_2.push_back(*it_2++);
			player_1_won = play_sub_game(sub_1, sub_2);
		}
		else player_1_won = card_1 > card_2;

		if (player_1_won)
		{
			deck_1.push_back(card_1);
			deck_1.push_back(card_2);
		}
		else
		{
			deck_2.push_back(card_2);
			deck_2.push_back(card_1);
		}
	}

	return deck_1.size() > 0;
}

#include "../../../../core/fundamental classes/logic/card/card.h"
#include "../../../../core/fundamental classes/logic/deck/deck.h"
#include <iostream>

#define WASTE_COL -1

#pragma once
class card_field
{
	deck tableau_piles[7] = { deck(18), deck(18), deck(18), deck(18), deck(18), deck(18), deck(18) };
	deck foundation_piles[4] = { deck(13), deck(13), deck(13), deck(13) };
	deck stock_pile{ 24 };
	deck waste_pile{ 24 };
public:
	card_field();
	card_field(std::mt19937&);

	void print_field_console();

	bool foundation_piles_is_full();
	int get_col_from_card(card&);
	int get_index_from_card(card&);
	int get_first_faceup_index(int);

	void open_card_from_stock();
	void move_card_from_col_to_col(int, int, int);
	void move_card_to_foundation(int, int);
	void move_card_from_waste_to_col(int);
	void return_card_from_foundation_to_col(int, int);

	// Auto functions TODO in new update)))
private:
	void deck_init(deck&);

	void move_tableau_to_foundation(int, int);
	void move_waste_to_foundation(int, int);

	bool is_valid_move(card&, int);
	bool is_valid_move_to_foundation(card&, int);
	void open_top_card(int);
	int get_top_card_index_from_longest_col();
};
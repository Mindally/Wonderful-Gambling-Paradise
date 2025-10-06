#include "card_field.h"

card_field::card_field() {
	deck deck;
	deck.shuffle();
	deck_init(deck);
}

card_field::card_field(std::mt19937& gen) {
	deck deck;
	deck.shuffle(gen);
	deck_init(deck);
}

void card_field::print_field_console() {
	std::cout << stock_pile.top_index() + 1 << " ";
	if (!waste_pile.is_empty())	waste_pile.get_top_card().print();
	else std::cout << "BL";

	std::cout << "    ";
	for (int i = 0; i < 4; i++) {
		if (foundation_piles[i].is_empty()) std::cout << "F" << i << " ";
		else {
			foundation_piles[i].get_top_card().print();
			std::cout << " ";
		}
	}
	std::cout << std::endl << std::endl;

	for (int row = 0; row < get_top_card_index_from_longest_col() + 1; row++) {
		for (int col = 0; col < 7; col++) {
			tableau_piles[col][row].print();
			std::cout << " ";
		}
		std::cout << std::endl;
	}
}

bool card_field::foundation_piles_is_full() {
	for (int i = 0; i < 4; i++) {
		if (!foundation_piles[i].is_full()) return false;
	}
	return true;
}

int card_field::get_col_from_card(card& card) {
	for (int col = 0; col < 7; col++) {
		for (int row = 0; row < 18; row++) {
			if (tableau_piles[col][row].state() == Blank) break;
			if (tableau_piles[col][row] == card) return col;
		}
	}
	return WASTE_COL;
}

int card_field::get_index_from_card(card& card) {
	for (int col = 0; col < 7; col++) {
		for (int row = 0; row < 18; row++) {
			if (tableau_piles[col][row].state() == Blank) break;
			if (tableau_piles[col][row] == card) return row;
		}
	}
	return WASTE_COL;
}

int card_field::get_first_faceup_index(int col) {
	if (col < 0 || col > 6) throw std::invalid_argument("card_field.get_first_faceup_card: Invalid argument 'col' - must be in the range from 0 to 6");
	if (!tableau_piles[col].is_empty()) {
		for (int row = 0; row < 18; row++) {
			if (tableau_piles[col][row].state() == FaceUp) return row;
		}
	}
	return WASTE_COL;
}
void card_field::open_card_from_stock() {
	if (stock_pile.is_empty() && waste_pile.is_empty()) throw std::logic_error("card_field.open_card_from_stock: Can't open card from stock");
	if (!stock_pile.is_empty()) {
		waste_pile.append(stock_pile.get_top_card());
		stock_pile.erase();
	}
	else {
		waste_pile.shrink_to_fit();
		stock_pile.assign(waste_pile, Reverse);
		waste_pile.clear();
	}

}

void card_field::move_card_from_col_to_col(int from, int to, int index) {
	if (from < 0 || from > 6) throw std::invalid_argument("card_field.move_card_from_col_to_col: Invalid argument 'from' - must be in the range from 0 to 6");
	if (to < 0 || to > 6) throw std::invalid_argument("card_field.move_card_from_col_to_col: Invalid argument 'to' - must be in the range from 0 to 6");
	if (index < 0 || index > 17) throw std::invalid_argument("card_field.move_card_from_col_to_col: Invalid argument 'index' - must be in range from 0 to 17");
	if (tableau_piles[from][index].state() != FaceUp) throw std::invalid_argument("card_field.move_card_from_col_to_col: Invalid argument 'index' - must be FaceUp");

	if (is_valid_move(tableau_piles[from][index], to)) {
		deck temp(tableau_piles[from], index, tableau_piles[from].top_index());
		for (int i = tableau_piles[from].top_index(); i >= index; i--) tableau_piles[from].erase();
		tableau_piles[to].append(temp);
		open_top_card(from);
	}
}

void card_field::move_card_to_foundation(int from, int foundation_suit) {
	if ((from < 0 || from > 6) && from != WASTE_COL) throw std::invalid_argument("card_field.move_card_to_foundation: Invalid argument 'from' - must be in the range from 0 to 6 or WASTE_COL");
	if (foundation_suit < 0 || foundation_suit > 3) throw std::invalid_argument("card_field.move_card_to_foundation: Invalid argument 'foundation_suit' - must be entered correctly");

	if (from == WASTE_COL) move_waste_to_foundation(from, foundation_suit);
	else move_tableau_to_foundation(from, foundation_suit);
}

void card_field::move_card_from_waste_to_col(int to) {
	if (to < 0 || to > 6) throw std::invalid_argument("card_field.move_card_from_waste_to_col: Invalid argument 'to' - must be in the range from 0 to 6");

	if (!waste_pile.is_empty()) {
		if (is_valid_move(waste_pile.get_top_card(), to)) {
			tableau_piles[to].append(waste_pile.get_top_card());
			waste_pile.erase();
		}
	}
}

void card_field::return_card_from_foundation_to_col(int foundation_suit, int to) {
	if (foundation_suit < 0 || foundation_suit > 3) throw std::invalid_argument("card_field.return_card_from_foundation_to_col: Invalid argument 'foundation_suit' - must be entered correctly");
	if (to < 0 || to > 6) throw std::invalid_argument("card_field.return_card_from_foundation_to_col: Invalid argument 'to' - must be in the range from 0 to 6");

	if (!foundation_piles[foundation_suit].is_empty()) {
		if (is_valid_move(foundation_piles[foundation_suit].get_top_card(), to)) {
			tableau_piles[to].append(foundation_piles[foundation_suit].get_top_card());
			foundation_piles[foundation_suit].erase();
		}
	}
}

// Auto functions TODO

// Private functions

void card_field::deck_init(deck& deck) {
	for (int col = 0; col < 7; col++) {
		for (int row = 0; row < 18; row++) {
			if (row < col + 1) {
				if (row == col) deck.get_top_card().set_state(FaceUp);
				tableau_piles[col].append(deck.get_top_card());
				deck.erase();
			}
		}
	}
	for (int i = 0; i < 24; i++) {
		deck.get_top_card().set_state(FaceUp);
		stock_pile.append(deck.get_top_card());
		deck.erase();
	}
}

void card_field::move_tableau_to_foundation(int from, int suit) {
	if (is_valid_move_to_foundation(tableau_piles[from].get_top_card(), suit)) {
		foundation_piles[suit].append(tableau_piles[from].get_top_card());
		tableau_piles[from].erase();
		open_top_card(from);
	}
}

void card_field::move_waste_to_foundation(int from, int suit) {
	if (is_valid_move_to_foundation(waste_pile.get_top_card(), suit)) {
		foundation_piles[suit].append(waste_pile.get_top_card());
		waste_pile.erase();
	}
}

bool card_field::is_valid_move(card& card, int to) {
	if (card.state() != FaceUp) throw std::invalid_argument("card_field.is_valid_move: Invalid argument 'card' - state must be FaceUp");
	if (to < 0 || to > 6) throw std::invalid_argument("card_field.is_valid_move: Invalid argument 'to' - state must be in range from 0 to 6");

	if (!tableau_piles[to].is_empty()) {
		if ((is_valid_suit(card.suit(), tableau_piles[to].get_top_card().suit()))
			&& (is_valid_rank(card.rank(), tableau_piles[to].get_top_card().rank()))) return true;
	}
	else {
		if (card.rank() == RK) return true;
	}
	throw std::logic_error("card_field.is_valid_move: Move is not valid");
}

bool card_field::is_valid_move_to_foundation(card& card, int foundation_suit) {
	if (card.state() != FaceUp) throw std::invalid_argument("card_field.is_valid_move_to_foundation: Invalid argument 'card' - state must be FaceUp");
	if (foundation_suit < 0 || foundation_suit > 3) throw std::invalid_argument("card_field.is_valid_move_to_foundation: Invalid argument 'foundation_suit' - must be entered correctly");


	if (card.suit() == foundation_suit) {
		if (!foundation_piles[foundation_suit].is_empty()) {
			if (foundation_piles[foundation_suit].get_top_card().rank() == RA && card.rank() == R2) return true;
			else if (is_valid_rank(foundation_piles[foundation_suit].get_top_card().rank(), card.rank())) return true;
		}
		else {
			if (card.rank() == RA) return true;
		}
	}
	throw std::logic_error("card_field.is_valid_move_to_foundation: Move is not valid");
}

void card_field::open_top_card(int col) {
	if (!tableau_piles[col].is_empty()) {
		if (tableau_piles[col].get_top_card().state() == FaceDown) tableau_piles[col].get_top_card().flip();
	}
}

int card_field::get_top_card_index_from_longest_col() {
	int max_index = 0;
	for (int i = 0; i < 7; i++) {
		if (tableau_piles[i].top_index() > max_index) max_index = tableau_piles[i].top_index();
	}
	return max_index;
}
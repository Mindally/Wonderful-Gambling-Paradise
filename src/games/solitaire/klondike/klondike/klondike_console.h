#include "../../../../core/fundamental classes/logic/card/card.h"
#include "../../../../core/fundamental classes/logic/deck/deck.h"
#include "../cardField/card_field.h"
#include <iostream>
#include <ctime>
#include <windows.h>
#include <string>

#define ERROR_CODE -2

bool string_to_bool(const std::string&);
void to_upper_case(std::string&);
void copy_text_to_clipboard(const std::string&);
bool is_all_digits(const std::string&);

#pragma once

enum Game_state { Defeat, Victory, Setup, Running };

class klondike
{
	int _state = Setup;
	int _player_moves = 0;

	unsigned int _seed;
	card_field _field;
	std::mt19937 _gen;

	// Settings
	bool pauseAfterTurn = false;
	bool showErrorMsg = false;
	bool showPlayerMoves = true;
	bool highContrastCards = false;
public:
	klondike();

	void config();
	void start();
private:
	void reset();
	void reroll();
	void set_seed(unsigned int);
	void is_win();
private: // Config subfunctions
	void seed_config(std::string&);
	void showPlayerMoves_config(std::string&);
	void highContrastCards_confing(std::string&);
	void pauseAfterTurn_config(std::string&);
	void showErrorMsg_config(std::string&);
private: // Start subfunctions
	bool open_card_from_stock_start(char, std::string);
	bool move_card_to_foundation_start(char, std::string);
	bool move_card_from_waste_to_col_start(char, std::string);
	bool return_card_from_foundation_to_col_start(char, std::string);
	bool move_card_from_col_to_col_start(char, std::string);
	bool reset_start(char, std::string);
	bool reroll_start(char, std::string);
};


//#include "klondike_console.h"
//
//bool string_to_bool(const std::string& input) {
//	if (input == "true" || input == "1" || input == "y" || input == "Y") return true;
//	if (input == "false" || input == "0" || input == "n" || input == "N") return false;
//	std::cout << "Set to false" << std::endl;
//	return false;
//}
//
//void to_upper_case(std::string& str) {
//	for (char& c : str) {
//		c = std::toupper(c);
//	}
//}
//
//void copy_text_to_clipboard(const std::string& text) {
//	if (!OpenClipboard(NULL)) return;
//	EmptyClipboard();
//	HGLOBAL hg = GlobalAlloc(GMEM_DDESHARE, text.size() + 1);
//	char* buffer = (char*)GlobalLock(hg);
//	strcpy_s(buffer, text.size() + 1, text.c_str());
//	GlobalUnlock(hg);
//	SetClipboardData(CF_TEXT, hg);
//	CloseClipboard();
//}
//
//bool is_all_digits(const std::string& str) {
//	return all_of(str.begin(), str.end(), [](char c) {
//		return isdigit(c);
//		});
//}
//
//klondike::klondike() {
//	std::random_device rd;
//	_seed = rd();
//	_gen = std::mt19937(_seed);
//	_field = card_field(_gen);
//}
//
//void klondike::config() {
//	if (_state == Setup) {
//		std::string input;
//
//		seed_config(input);
//		showPlayerMoves_config(input);
//		highContrastCards_confing(input);
//		pauseAfterTurn_config(input);
//		if (pauseAfterTurn)	showErrorMsg_config(input);
//
//		system("pause");
//		system("cls");
//	}
//	else std::cout << "klondike.config() is unavailable after the end of the game or during its execution" << std::endl;
//}
//
//void klondike::start() {
//	_state = Running;
//	std::string input;
//
//	while (_state == Running) {
//		if (showPlayerMoves) std::cout << "Moves: " << _player_moves << std::endl;
//		_field.print_field_console();
//
//		std::cout << "\nEnter your move: ";
//		std::getline(std::cin, input);
//		to_upper_case(input);
//		try {
//			if (open_card_from_stock_start('O', input));
//
//			else if (move_card_to_foundation_start('F', input));
//
//			else if (move_card_from_waste_to_col_start('W', input));
//
//			else if (return_card_from_foundation_to_col_start('R', input));
//
//			else if (move_card_from_col_to_col_start('M', input));
//
//			else if (reset_start('A', input));
//
//			else if (reroll_start('N', input));
//
//			else throw std::logic_error("klondike.start: Move is undefined");
//		}
//		catch (const std::exception& e) {
//			if (showErrorMsg) std::cerr << e.what() << std::endl;
//		}
//		if (pauseAfterTurn) system("pause");
//		system("cls");
//	}
//	// Я забыл про победу)))
//}
//
//void klondike::reset() {
//	_state = Running;
//	_player_moves = 0;
//	set_seed(_seed);
//}
//void klondike::reroll() {
//	_state = Running;
//	_player_moves = 0;
//	std::random_device rd;
//	set_seed(rd());
//}
//
//void klondike::set_seed(unsigned int seed) {
//	_seed = seed;
//	_gen.seed(_seed);
//	_field = card_field(_gen);
//}
//
//void klondike::is_win() {
//	_state = int(_field.foundation_piles_is_full());
//}
//
//// Config subfunctions
//
//void klondike::seed_config(std::string& input) {
//	std::cout << "Enter your seed (leave blank for random): ";
//	std::getline(std::cin, input);
//	try {
//		if (!input.empty()) set_seed(stoi(input));
//	}
//	catch (const std::exception& e) {
//		std::cerr << "Seed was entered incorrectly (" << e.what() << "). A random seed is applied" << std::endl;
//	}
//}
//
//void klondike::showPlayerMoves_config(std::string& input) {
//	std::cout << "Show the number of user moves (rule: showPlayerMoves)?: ";
//	std::getline(std::cin, input);
//	showPlayerMoves = string_to_bool(input);
//}
//
//void klondike::highContrastCards_confing(std::string& input) {
//	std::cout << "Make cards high-contrast? (rule: highContrastCards)?: ";
//	std::getline(std::cin, input);
//	highContrastCards = string_to_bool(input);
//}
//
//void klondike::pauseAfterTurn_config(std::string& input) {
//	std::cout << "Do you need a pause between turns (rule: pauseAfterTurn)? ";
//	std::getline(std::cin, input);
//	pauseAfterTurn = string_to_bool(input);
//}
//
//void klondike::showErrorMsg_config(std::string& input) {
//	std::cout << "Show error message after your turn (rule: showErrorMsg)? ";
//	std::getline(std::cin, input);
//	showErrorMsg = string_to_bool(input);
//}
//
//// Start subfunctions
//
//bool klondike::open_card_from_stock_start(char code, std::string input) {
//	if (input[0] == code && input.length() == 1) {
//		_field.open_card_from_stock();
//		_player_moves++;
//		return true;
//	}
//	return false;
//}
//
//bool klondike::move_card_to_foundation_start(char code, std::string input) {
//	if (input[0] == code && input.length() == 3) {
//		int from, suit;
//		switch (input[1]) {
//		case 'W': from = -1; break;
//		case '0': case '1': case '2': case '3': case '4': case '5': case '6': from = input[1] - '0'; break;
//		default: from = ERROR_CODE; break;
//		}
//		switch (input[2]) {
//		case 'C': suit = Clubs; break;
//		case 'D': suit = Diamonds; break;
//		case 'H': suit = Hearts; break;
//		case 'S': suit = Spades; break;
//		default: suit = ERROR_CODE; break;
//		}
//		_field.move_card_to_foundation(from, suit);
//		_player_moves++;
//		return true;
//	}
//	return false;
//}
//
//bool klondike::move_card_from_waste_to_col_start(char code, std::string input) {
//	if (input[0] == code && input.length() == 2) {
//		int to;
//		switch (input[1])
//		{
//		case '0': case '1': case '2': case '3': case '4': case '5': case '6': to = input[1] - '0'; break;
//		default: to = ERROR_CODE; break;
//		}
//		std::cout << to << std::endl;
//		_field.move_card_from_waste_to_col(to);
//		_player_moves++;
//		return true;
//	}
//	return false;
//}
//
//bool klondike::return_card_from_foundation_to_col_start(char code, std::string input) {
//	if (input[0] == code && input.length() == 3) {
//		int suit, to;
//		switch (input[1]) {
//		case 'C': suit = Clubs; break;
//		case 'D': suit = Diamonds; break;
//		case 'H': suit = Hearts; break;
//		case 'S': suit = Spades; break;
//		default: suit = ERROR_CODE; break;
//		}
//		switch (input[2]) {
//		case '0': case '1': case '2': case '3': case '4': case '5': case '6': to = input[2] - '0'; break;
//		default: to = ERROR_CODE; break;
//		}
//		_field.return_card_from_foundation_to_col(suit, to);
//		_player_moves++;
//		return true;
//	}
//	return false;
//}
//
//bool klondike::move_card_from_col_to_col_start(char code, std::string input) {
//	if (input[0] == code && input.length() == 5) {
//		int from, to, index;
//		switch (input[1]) {
//		case '0': case '1': case '2': case '3': case'4': case '5': case '6': from = input[1] - '0'; break;
//		default: from = ERROR_CODE; break;
//		}
//		switch (input[2]) {
//		case '0': case '1': case '2': case '3': case'4': case '5': case '6': to = input[2] - '0'; break;
//		default: to = ERROR_CODE; break;
//		}
//		index = (input[3] - '0') * 10 + (input[4] - '0');
//		_field.move_card_from_col_to_col(from, to, index);
//		_player_moves++;
//		return true;
//	}
//	return false;
//}
//
//bool klondike::reset_start(char code, std::string input) {
//	if (input[0] == code && input.length() == 1) {
//		reset();
//		return true;
//	}
//	return false;
//}
//
//bool klondike::reroll_start(char code, std::string input) {
//	if (input[0] == code && input.length() == 1) {
//		reroll();
//		return true;
//	}
//	return false;
//}
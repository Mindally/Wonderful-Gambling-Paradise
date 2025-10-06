#include "card.h"

void SetConsoleColor(int color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

int len(const char* str) {
	int len = 0;
	while (str[len])
		++len;
	return len;
}

card::card() {
	_suit = Clubs;
	_rank = R2;
	_state = Blank;
}

card::card(char suit, char rank, char state) {
	if (suit < Clubs || suit > Spades) throw std::invalid_argument("card: Invalid argument 'suit' - must be entered correctly");
	if (rank < R2 || rank > RA) throw std::invalid_argument("card: Invalid argument 'rank' - must be entered correctly");
	if (state < FaceDown || state > Blank) throw std::invalid_argument("card: Invalid argument 'state' - must be FaceDown, FaceUp or Blank");

	_rank = rank;
	_suit = suit;
	_state = state;
}

card::card(const char* str) {  // String example: DT1, HQ1, SA0, C40
	if (str == nullptr) throw std::invalid_argument("card: Invalid argument 'string' - null pointer passed");
	if (len(str) != 3) throw std::invalid_argument("card: Invalid argument 'string' - must be exactly 3 characters long");

	switch (str[0])
	{
	case 'D': _suit = Diamonds; break;
	case 'H': _suit = Hearts; break;
	case 'C': _suit = Clubs; break;
	case 'S': _suit = Spades; break;
	default: throw std::invalid_argument("card: Invalid argument 'suit' - invalid suit character");
	}

	switch (str[1]) {
	case '2': _rank = R2; break;
	case '3': _rank = R3; break;
	case '4': _rank = R4; break;
	case '5': _rank = R5; break;
	case '6': _rank = R6; break;
	case '7': _rank = R7; break;
	case '8': _rank = R8; break;
	case '9': _rank = R9; break;
	case 'T': _rank = R10; break;
	case 'J': _rank = RJ; break;
	case 'Q': _rank = RQ; break;
	case 'K': _rank = RK; break;
	case 'A': _rank = RA; break;
	default: throw std::invalid_argument("card: Invalid argument 'rank' - invalid rank character");
	}

	switch (str[2]) {
	case '0': case 'D': _state = FaceDown; break;
	case '1': case 'U': _state = FaceUp; break;
	case '2': case 'B': _state = Blank; break;
	default: throw std::invalid_argument("card: Invalid argument 'state' - invalid state character");
	}
}

card::card(const card& other) {
	_suit = other._suit;
	_rank = other._rank;
	_state = other._state;
}

void card::set_suit(char suit) {
	if (suit < Clubs || suit > Spades) throw std::invalid_argument("card.set_suit: Invalid argument 'suit' - must be entered correctly");
	_suit = suit;
}

void card::set_rank(char rank) {
	if (rank < R2 || rank > RA) throw std::invalid_argument("card.set_rank: Invalid argument 'rank' - must be entered correctly");
	_rank = rank;
}

void card::set_state(char state) {
	if (state < FaceDown || state > Blank) throw std::invalid_argument("card.set_state: Invalid argument 'state' - must be FaceDown, FaceUp or Blank");
	_state = state;
}

int card::suit() const {
	return int(_suit);
}

int card::rank() const {
	return int(_rank);
}

int card::state() const {
	return int(_state);
}

void card::set_random_suit() {
	set_suit(rand() % (Spades + 1));
}

void card::set_random_rank() {
	set_rank(rand() % (RA - R2 + 1) + R2);
}
void card::set_random() {
	set_random_suit();
	set_random_rank();
}

void card::assign(const card& other) {
	_suit = other._suit;
	_rank = other._rank;
	_state = other._state;
}

void card::print() {
	if (_state == FaceDown) {
		std::cout << "**";
	}
	else if (_state == FaceUp) {
		switch (_suit) {
		case Diamonds:
			SetConsoleColor(6);
			std::cout << "D";
			break;
		case Hearts:
			SetConsoleColor(12);
			std::cout << "H";
			break;
		case Clubs:
			SetConsoleColor(9);
			std::cout << "C";
			break;
		case Spades:
			SetConsoleColor(9);
			std::cout << "S";
			break;
		}

		switch (_rank) {
		case R2: std::cout << "2"; break;
		case R3: std::cout << "3"; break;
		case R4: std::cout << "4"; break;
		case R5: std::cout << "5"; break;
		case R6: std::cout << "6"; break;
		case R7: std::cout << "7"; break;
		case R8: std::cout << "8"; break;
		case R9: std::cout << "9"; break;
		case R10: std::cout << "T"; break;
		case RJ: std::cout << "J"; break;
		case RQ: std::cout << "Q"; break;
		case RK: std::cout << "K"; break;
		case RA: std::cout << "A"; break;
		}
		SetConsoleColor(7);
	}
	else if (_state == Blank) {
		std::cout << "  ";
	}
}

void card::flip() {
	if (_state == FaceDown) set_state(FaceUp);
	else if (_state == FaceUp) set_state(FaceDown);
}

bool is_valid_suit(int from_suit, int to_suit) {
	if ((to_suit == Clubs || to_suit == Spades) && (from_suit == Diamonds || from_suit == Hearts)) return true;
	else if ((to_suit == Diamonds || to_suit == Hearts) && (from_suit == Clubs || from_suit == Spades)) return true;
	else return false;
}

bool is_valid_rank(int from_rank, int to_rank) {
	if (to_rank == RA) return false;
	if (to_rank == from_rank + 1) return true;
	else return false;
}

void card::operator=(const card& other) {
	this->assign(other);
}

bool card::operator==(const card& other) {
	if (other._state != Blank && this->_state != Blank)
		return ((this->_rank == other._rank) && (this->_suit == other._suit));
	else return false;
}

bool card::operator!=(const card& other) {
	return !(*this == other);
}

bool card::operator>(const card& other) {
	return (this->_rank > other._rank);
}

bool card::operator<(const card& other) {
	return (this->_rank < other._rank);
}

bool card::operator>=(const card& other) {
	return ((this->_rank > other._rank) || (this->_rank == other._rank));
}

bool card::operator<=(const card& other) {
	return ((this->_rank < other._rank) || (this->_rank == other._rank));
}
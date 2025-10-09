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

namespace WGP {

	card::card() {
		_suit = CardSuit::Hearts;
		_rank = CardRank::R2;
		_state = CardState::Blank;
	}

	card::card(CardSuit suit, CardRank rank, CardState state) {
		if (suit != CardSuit::Clubs &&
			suit != CardSuit::Diamonds &&
			suit != CardSuit::Hearts &&
			suit != CardSuit::Spades)
		{
			throw std::invalid_argument("card: Invalid argument 'suit' - must be entered correctly");
		}
		if (rank < CardRank::R2 || rank > CardRank::RA)
		{
			throw std::invalid_argument("card: Invalid argument 'rank' - must be entered correctly");
		}
		if (state != CardState::FaceDown &&
			state != CardState::FaceUp &&
			state != CardState::Blank)
		{
			throw std::invalid_argument("card: Invalid argument 'state' - must be FaceDown, FaceUp or Blank");
		}

		_rank = rank;
		_suit = suit;
		_state = state;
	}

	card::card(const char* str) {  // String example: DTU, HQU, SAD, C4D
		if (str == nullptr) throw std::invalid_argument("card: Invalid argument 'string' - nullptr passed");
		if (len(str) != 3) throw std::invalid_argument("card: Invalid argument 'string' - must be exactly 3 characters long");

		switch (str[0])
		{
		case 'D': _suit = CardSuit::Diamonds; break;
		case 'H': _suit = CardSuit::Hearts; break;
		case 'C': _suit = CardSuit::Clubs; break;
		case 'S': _suit = CardSuit::Spades; break;
		default: throw std::invalid_argument("card: Invalid argument 'suit' - invalid suit character");
		}

		switch (str[1]) {
		case '2': _rank = CardRank::R2; break;
		case '3': _rank = CardRank::R3; break;
		case '4': _rank = CardRank::R4; break;
		case '5': _rank = CardRank::R5; break;
		case '6': _rank = CardRank::R6; break;
		case '7': _rank = CardRank::R7; break;
		case '8': _rank = CardRank::R8; break;
		case '9': _rank = CardRank::R9; break;
		case 'T': _rank = CardRank::RT; break;
		case 'J': _rank = CardRank::RJ; break;
		case 'Q': _rank = CardRank::RQ; break;
		case 'K': _rank = CardRank::RK; break;
		case 'A': _rank = CardRank::RA; break;
		default: throw std::invalid_argument("card: Invalid argument 'rank' - invalid rank character");
		}

		switch (str[2]) {
		case 'D': _state = CardState::FaceDown; break;
		case 'U': _state = CardState::FaceUp; break;
		case 'B': _state = CardState::Blank; break;
		default: throw std::invalid_argument("card: Invalid argument 'state' - invalid state character");
		}
	}

	card::card(const card& other) {
		_suit = other._suit;
		_rank = other._rank;
		_state = other._state;
	}

	void card::setSuit(CardSuit suit) {
		if (suit != CardSuit::Clubs &&
			suit != CardSuit::Diamonds &&
			suit != CardSuit::Hearts &&
			suit != CardSuit::Spades)
		{
			throw std::invalid_argument("card.set_suit: Invalid argument 'suit' - must be entered correctly");
		}
		_suit = suit;
	}

	void card::setRank(CardRank rank) {
		if (rank < CardRank::R2 || rank > CardRank::RA) {
			throw std::invalid_argument("card.set_rank: Invalid argument 'rank' - must be entered correctly");
		}
		_rank = rank;
	}

	void card::setState(CardState state) {
		if (state != CardState::FaceDown &&
			state != CardState::FaceUp &&
			state != CardState::Blank)
		{
			throw std::invalid_argument("card.set_state: Invalid argument 'state' - must be FaceDown, FaceUp or Blank");
		}
		_state = state;
	}

	CardSuit card::suit() const {
		return _suit;
	}

	CardRank card::rank() const {
		return _rank;
	}

	CardState card::state() const {
		return _state;
	}

	void card::setRandomSuit() {
		setSuit(static_cast<CardSuit>(rand() % 4));
	}

	void card::setRandomRank() {
		setRank(static_cast<CardRank>(rand() % 13 + 2));
	}
	void card::setRandom() {
		setRandomSuit();
		setRandomRank();
	}

	void card::assign(const card& other) {
		_suit = other._suit;
		_rank = other._rank;
		_state = other._state;
	}

	void card::print() const {
		if (_state == CardState::FaceDown) {
			std::cout << "**";
		}
		else if (_state == CardState::FaceUp) {
			switch (_suit) {
			case CardSuit::Diamonds:
				SetConsoleColor(6);
				std::cout << "D";
				break;
			case CardSuit::Hearts:
				SetConsoleColor(12);
				std::cout << "H";
				break;
			case CardSuit::Clubs:
				SetConsoleColor(9);
				std::cout << "C";
				break;
			case CardSuit::Spades:
				SetConsoleColor(9);
				std::cout << "S";
				break;
			}

			switch (_rank) {
			case CardRank::R2: std::cout << "2"; break;
			case CardRank::R3: std::cout << "3"; break;
			case CardRank::R4: std::cout << "4"; break;
			case CardRank::R5: std::cout << "5"; break;
			case CardRank::R6: std::cout << "6"; break;
			case CardRank::R7: std::cout << "7"; break;
			case CardRank::R8: std::cout << "8"; break;
			case CardRank::R9: std::cout << "9"; break;
			case CardRank::RT: std::cout << "T"; break;
			case CardRank::RJ: std::cout << "J"; break;
			case CardRank::RQ: std::cout << "Q"; break;
			case CardRank::RK: std::cout << "K"; break;
			case CardRank::RA: std::cout << "A"; break;
			}
			SetConsoleColor(7);
		}
		else if (_state == CardState::Blank) {
			std::cout << "  ";
		}
	}

	void card::flip() {
		if (_state == CardState::FaceDown) {
			setState(CardState::FaceUp);
		}
		else if (_state == CardState::FaceUp) {
			setState(CardState::FaceDown);
		}
	}

	bool solitaireIsValidSuit(CardSuit fromSuit, CardSuit toSuit) {
		if ((toSuit == CardSuit::Clubs || toSuit == CardSuit::Spades) &&
			(fromSuit == CardSuit::Diamonds || fromSuit == CardSuit::Hearts))
		{
			return true;
		}
		if ((toSuit == CardSuit::Diamonds || toSuit == CardSuit::Hearts) &&
			(fromSuit == CardSuit::Clubs || fromSuit == CardSuit::Spades))
		{
			return true;
		}
		return false;
	}

	bool solitaireIsValidRank(CardRank fromRank, CardRank toRank) {
		if (toRank == CardRank::RA) return false;
		if (static_cast<int>(toRank) == static_cast<int>(fromRank) + 1) return true;
		else return false;
	}

	void card::operator=(const card& other) {
		this->assign(other);
	}

	bool card::operator==(const card& other) const {
		if (other._state != CardState::Blank &&
			this->_state != CardState::Blank)
		{
			return ((this->_rank == other._rank) && (this->_suit == other._suit));
		}
		return false;
	}

	bool card::operator!=(const card& other) const {
		return !(*this == other);
	}

	bool card::operator>(const card& other) const {
		return (this->_rank > other._rank);
	}

	bool card::operator<(const card& other) const {
		return (this->_rank < other._rank);
	}

	bool card::operator>=(const card& other) const {
		return ((this->_rank > other._rank) || (this->_rank == other._rank));
	}

	bool card::operator<=(const card& other) const {
		return ((this->_rank < other._rank) || (this->_rank == other._rank));
	}
}
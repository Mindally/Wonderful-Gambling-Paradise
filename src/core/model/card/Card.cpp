#include "Card.hpp"

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

namespace wgp {

// =============================================
// ÊÎÍÑÒĞÓÊÒÎĞÛ
// =============================================

	Card::Card() :
		_suit(CardSuit::Hearts),
		_rank(CardRank::R2),
		_state(CardState::Blank)
	{}

	Card::Card(CardSuit suit, CardRank rank, CardState state) :
		_suit(suit),
		_rank(rank),
		_state(state)
	{
		if (suit != CardSuit::Clubs &&
			suit != CardSuit::Diamonds &&
			suit != CardSuit::Hearts &&
			suit != CardSuit::Spades)
		{
			throw std::invalid_argument("Card: Invalid argument 'suit' - must be entered correctly");
		}
		if (rank < CardRank::R2 || rank > CardRank::RA)
		{
			throw std::invalid_argument("Card: Invalid argument 'rank' - must be entered correctly");
		}
		if (state != CardState::FaceDown &&
			state != CardState::FaceUp &&
			state != CardState::Blank)
		{
			throw std::invalid_argument("Card: Invalid argument 'state' - must be FaceDown, FaceUp or Blank");
		}
	}

	Card::Card(const char* str) {  // Ïğèìåğ èíèöèàëèçàöèè êàğòû êàê ñòğîêè: DTU, HQU, SAD, C4D
		if (str == nullptr) {
			throw std::invalid_argument("Card: Invalid argument 'string' - nullptr passed");
		}
		if (len(str) != 3) {
			throw std::invalid_argument("Card: Invalid argument 'string' - must be exactly 3 characters long");
		}

		switch (str[0])
		{
		case 'D': _suit = CardSuit::Diamonds; break;
		case 'H': _suit = CardSuit::Hearts; break;
		case 'C': _suit = CardSuit::Clubs; break;
		case 'S': _suit = CardSuit::Spades; break;
		default: throw std::invalid_argument("Card: Invalid argument 'suit' - invalid suit character");
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
		default: throw std::invalid_argument("Card: Invalid argument 'rank' - invalid rank character");
		}

		switch (str[2]) {
		case 'D': _state = CardState::FaceDown; break;
		case 'U': _state = CardState::FaceUp; break;
		case 'B': _state = CardState::Blank; break;
		default: throw std::invalid_argument("Card: Invalid argument 'state' - invalid state character");
		}
	}

	Card::Card(const Card& other) :
		_suit(other._suit),
		_rank(other._rank),
		_state(other._state)
	{}

// =============================================
// ÑÅÒÒÅĞÛ
// =============================================

	void Card::setSuit(CardSuit suit) {
		if (suit != CardSuit::Clubs &&
			suit != CardSuit::Diamonds &&
			suit != CardSuit::Hearts &&
			suit != CardSuit::Spades)
		{
			throw std::invalid_argument("Card.setSuit: Invalid argument 'suit' - must be entered correctly");
		}
		_suit = suit;
	}

	void Card::setRank(CardRank rank) {
		if (rank < CardRank::R2 || rank > CardRank::RA) {
			throw std::invalid_argument("Card.setRank: Invalid argument 'rank' - must be entered correctly");
		}
		_rank = rank;
	}

	void Card::setState(CardState state) {
		if (state != CardState::FaceDown &&
			state != CardState::FaceUp &&
			state != CardState::Blank)
		{
			throw std::invalid_argument("Card.setState: Invalid argument 'state' - must be FaceDown, FaceUp or Blank");
		}
		_state = state;
	}

	void Card::setRandomSuit() {
		std::mt19937 gen(std::random_device{}());
		std::uniform_int_distribution<> distrib(0, 3);

		setSuit(static_cast<CardSuit>(distrib(gen)));
	}

	void Card::setRandomRank() {
		std::mt19937 gen(std::random_device{}());
		std::uniform_int_distribution<> distrib(2, 14);

		setRank(static_cast<CardRank>(distrib(gen)));
	}

	void Card::setRandom() {
		setRandomSuit();
		setRandomRank();
	}

	void Card::setRandomSuit(std::mt19937& gen) {
		std::uniform_int_distribution<> distrib(0, 3);
		setSuit(static_cast<CardSuit>(distrib(gen)));
	}

	void Card::setRandomRank(std::mt19937& gen) {
		std::uniform_int_distribution<> distrib(2, 14);
		setRank(static_cast<CardRank>(distrib(gen)));
	}

	void Card::setRandom(std::mt19937& gen) {
		setRandomSuit(gen);
		setRandomRank(gen);
	}

// =============================================
// ÏĞÎ×ÈÅ ÌÅÒÎÄÛ
// =============================================

	void Card::assign(const Card& other) {
		_suit = other._suit;
		_rank = other._rank;
		_state = other._state;
	}

	bool Card::isEqual(const Card& other) const {
		if (this->_state == CardState::Blank ||
			other._state == CardState::Blank)
		{
			return false;
		}
		return ((this->_rank == other._rank) && (this->_suit == other._suit));
	}

	void Card::print() const {
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

	void Card::flip() {
		if (_state == CardState::FaceDown) {
			setState(CardState::FaceUp);
		}
		else if (_state == CardState::FaceUp) {
			setState(CardState::FaceDown);
		}
	}

// =============================================
// Ïåğåãğóçêà îïåğàòîğîâ
// =============================================

	void Card::operator=(const Card& other) {
		this->assign(other);
	}

	bool Card::operator==(const Card& other) const {
		return this->isEqual(other);
	}

	bool Card::operator!=(const Card& other) const {
		return !(*this == other);
	}

// =============================================
// ÔÓÍÊÖÈÈ ÑĞÀÂÍÅÍÈß ÊÀĞÒ (Card a < Card b)
// =============================================

	bool compareByRank(const Card& first, const Card& second) {
		if (static_cast<int>(first.rank()) != static_cast<int>(second.rank()))
			return static_cast<int>(first.rank()) < static_cast<int>(second.rank());
		return static_cast<int>(first.suit()) < static_cast<int>(second.suit());
	}

	bool compareBySuit(const Card& first, const Card& second) {
		if (static_cast<int>(first.suit()) != static_cast<int>(second.suit()))
			return static_cast<int>(first.suit()) < static_cast<int>(second.suit());
		return static_cast<int>(first.rank()) < static_cast<int>(second.rank());
	}
}

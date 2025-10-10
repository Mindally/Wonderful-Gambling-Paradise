#include "../../TVector/TVector.h"
#include <iostream>
#include <windows.h>

#pragma once

namespace WGP {
	enum class CardRank { R2 = 2, R3, R4, R5, R6, R7, R8, R9, RT, RJ, RQ, RK, RA };
	enum class CardSuit { Clubs, Diamonds, Hearts, Spades };
	enum class CardState { FaceDown, FaceUp, Blank };

	class card
	{
		CardSuit _suit;
		CardRank _rank;
		CardState _state;
	public:
		card();
		card(CardSuit, CardRank, CardState);
		card(const char*);
		card(const card&);

		void setSuit(CardSuit);
		void setRank(CardRank);
		void setState(CardState);

		CardSuit suit() const;
		CardRank rank() const;
		CardState state() const;

		void setRandomSuit();
		void setRandomRank();
		void setRandom();
		void setRandomSuit(std::mt19937&);
		void setRandomRank(std::mt19937&);
		void setRandom(std::mt19937&);

		void assign(const card&);
		void print() const;
		void flip();

		void operator=(const card&);
		bool operator==(const card&) const;
		bool operator!=(const card&) const;
		bool operator>(const card&) const;
		bool operator<(const card&) const;
		bool operator>=(const card&) const;
		bool operator<=(const card&) const;
	};

	bool solitaireIsValidSuit(CardSuit, CardSuit);
	bool solitaireIsValidRank(CardRank, CardRank);
}




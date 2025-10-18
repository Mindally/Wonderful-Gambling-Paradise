#pragma once

#include "../../TVector/TVector.h"
#include <iostream>
#include <windows.h>

namespace wgp {

	enum class CardRank { R2 = 2, R3, R4, R5, R6, R7, R8, R9, RT, RJ, RQ, RK, RA };
	enum class CardSuit { Clubs, Diamonds, Hearts, Spades };
	enum class CardState { FaceDown, FaceUp, Blank };

	class Card
	{
		CardSuit _suit;
		CardRank _rank;
		CardState _state;
	public:
		// === Конструкторы ===
		Card();
		Card(CardSuit, CardRank, CardState);
		Card(const char*);
		Card(const Card&);

		// === Сеттеры ===
		void setSuit(CardSuit);
		void setRank(CardRank);
		void setState(CardState);

		void setRandomSuit();
		void setRandomRank();
		void setRandom();
		void setRandomSuit(std::mt19937&);
		void setRandomRank(std::mt19937&);
		void setRandom(std::mt19937&);

		// === Прочие методы ===
		void assign(const Card&);
		bool isEqual(const Card&) const;
		void print() const;
		void flip();

		// === Геттеры ===
		inline CardSuit suit() const { return _suit; };
		inline CardRank rank() const { return _rank; };
		inline CardState state() const { return _state; };

		inline bool isRed() const { return (_suit == CardSuit::Diamonds || _suit == CardSuit::Hearts); };
		inline bool isBlack() const { return (_suit == CardSuit::Clubs || _suit == CardSuit::Spades); };

		inline bool isFaceCard() const { return (_rank == CardRank::RJ || _rank == CardRank::RQ || _rank == CardRank::RK); };

		// === Перегрузка операторов ===
		void operator=(const Card&);
		bool operator==(const Card&) const;
		bool operator!=(const Card&) const;
	};

	// Функции сравнения карт (Card a < Card b)
	bool compareByRank(const Card&, const Card&);
	bool compareBySuit(const Card&, const Card&);

}

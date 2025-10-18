#pragma once

#include "../card/Card.hpp"
#include "../../TVector/TVector.h"
#include <random>
#include <initializer_list>

namespace wgp {

	enum class Direction { Forward, Reverse };

	class Deck
	{
		TVector<Card> _deck;
		int _topIndex;
	public:
		// === ������������ ===
		Deck();
		Deck(int);
		Deck(int, const Card*);
		Deck(std::initializer_list<Card>);
		Deck(std::initializer_list<const char*>);
		Deck(const Deck&);
		Deck(const Deck&, int, int);

		// === ������ ��������� ������� ���� � ������ ===
		void shuffle();
		void shuffle(std::mt19937&);
		void sort();

		// === ������ ������ ===
		void flip();
		void print() const;
		void assign(const Deck&, Direction);

		// === ������ ���������� ��� �������� ���� ===
		void append(Card&);
		void append(Card*, int);
		void append(const Deck&);
		void erase();
		void clear();

		// === ������ ���������� ������� ===
		void shrinkToFit();
		void resize(int);

		// === ������� ������������ ������ � ��������� ���� ===
		bool isEmpty() const;
		bool isFull() const;
		bool areAllCardsFaceUp() const;

		// === ������� ===
		inline int size() const { return _deck.size(); };
		inline int topIndex() const { return _topIndex; };
		Card& getTopCard();
		Card& getCard(int);
		const Card& getTopCard() const;
		const Card& getCard(int) const;

		// === ���������� ���������� ===
		void operator=(const Deck&);
		Card& operator[](int);
		const Card& operator[](int) const;
	};
}

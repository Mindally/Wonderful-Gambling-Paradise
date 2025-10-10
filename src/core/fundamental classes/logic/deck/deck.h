#include "../../logic/card/card.h"
#include "../../TVector/TVector.h"
#include <random>
#include <initializer_list>

#pragma once

namespace  WGP {
	enum class Direction { Forward, Reverse };

	class deck
	{
		TVector<card> _deck;
		int _topIndex;
	public:
		deck();
		deck(int);
		deck(int, const card*);
		deck(std::initializer_list<card>);
		deck(std::initializer_list<const char*>);
		deck(const deck&);
		deck(const deck&, int, int);

		void shuffle();
		void shuffle(std::mt19937&);
		void flip();
		void sort();

		void print() const;

		bool isEmpty() const;
		bool isFull() const;
		bool areAllCardsFaceUp() const;

		void append(card);
		void append(card*, int);
		void append(const deck&);
		void erase();
		void clear();

		void assign(const deck&, Direction);
		void shrinkToFit();
		void resize(int);

		int size() const;
		int topIndex() const;
		card& getTopCard();
		card& getCard(int);
		const card& getTopCard() const;
		const card& getCard(int) const;

		void operator=(const deck&);
		card& operator[](int);
		const card& operator[](int) const;
	};
}

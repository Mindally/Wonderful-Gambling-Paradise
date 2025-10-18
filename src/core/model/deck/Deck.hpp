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
		// === Конструкторы ===
		Deck();
		Deck(int);
		Deck(int, const Card*);
		Deck(std::initializer_list<Card>);
		Deck(std::initializer_list<const char*>);
		Deck(const Deck&);
		Deck(const Deck&, int, int);

		// === Методы изменения позиций карт в колоде ===
		void shuffle();
		void shuffle(std::mt19937&);
		void sort();

		// === Прочие методы ===
		void flip();
		void print() const;
		void assign(const Deck&, Direction);

		// === Методы добавления или удаления карт ===
		void append(Card&);
		void append(Card*, int);
		void append(const Deck&);
		void erase();
		void clear();

		// === Методы управления памятью ===
		void shrinkToFit();
		void resize(int);

		// === Геттеры заполнености колоды и состояния карт ===
		bool isEmpty() const;
		bool isFull() const;
		bool areAllCardsFaceUp() const;

		// === Геттеры ===
		inline int size() const { return _deck.size(); };
		inline int topIndex() const { return _topIndex; };
		Card& getTopCard();
		Card& getCard(int);
		const Card& getTopCard() const;
		const Card& getCard(int) const;

		// === Перегрузка операторов ===
		void operator=(const Deck&);
		Card& operator[](int);
		const Card& operator[](int) const;
	};
}

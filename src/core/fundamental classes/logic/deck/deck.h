#include "../../logic/card/card.h"
#include "../../TVector/TVector.h"
#include <random>
#include <initializer_list>

enum Direction { Forward, Reverse };

#pragma once
class deck
{
	TVector<card> _deck;
	int _top_index;
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

	void print();

	bool is_empty();
	bool is_full();

	void append(card);
	void append(card*, int);
	void append(const deck&);
	void erase();
	void clear();

	void assign(const deck&, Direction);
	void shrink_to_fit();
	void resize(int);

	int size() const;
	int top_index() const;
	card& get_top_card();
	card& get_card(int);

	void operator=(const deck&);
	card& operator[](int);
};


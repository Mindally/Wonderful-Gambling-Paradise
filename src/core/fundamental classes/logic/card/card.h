#include <iostream>
#include <windows.h>

#pragma once

enum Rank { R2 = 2, R3, R4, R5, R6, R7, R8, R9, R10, RJ, RQ, RK, RA };
enum Suit { Clubs, Diamonds, Hearts, Spades };
enum State { FaceDown, FaceUp, Blank };

class card
{
	char _suit;
	char _rank;
	char _state;
public:
	card();
	card(char, char, char);
	card(const char*);
	card(const card&);

	void set_suit(char);
	void set_rank(char);
	void set_state(char);

	int suit() const;
	int rank() const;
	int state() const;

	void set_random_suit();
	void set_random_rank();
	void set_random();

	void assign(const card&);
	void print();
	void flip();

	void operator=(const card&);
	bool operator==(const card&);
	bool operator!=(const card&);
	bool operator>(const card&);
	bool operator<(const card&);
	bool operator>=(const card&);
	bool operator<=(const card&);
};

bool is_valid_suit(int, int);
bool is_valid_rank(int, int);


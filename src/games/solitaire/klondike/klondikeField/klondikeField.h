#include "../../../../core/fundamental classes/logic/card/card.h"
#include "../../../../core/fundamental classes/logic/deck/deck.h"
#include "../../../../core/fundamental classes/TVector/TVector.h"
#include <iostream>

#define WASTE_COL -1

#pragma once

namespace WGP {
	class klondikeField
	{
		TVector<deck> _tableauPiles{ {deck(18), deck(18), deck(18), deck(18), deck(18), deck(18), deck(18)} };
		TVector<deck> _foundationPiles{ {deck(13), deck(13), deck(13), deck(13)} };
		deck _stockPile{ 24 };
		deck _wastePile{ 24 };
	public:
		klondikeField();
		klondikeField(std::mt19937&);

		void print() const;

		bool foundationPilesIsFull() const;

		void openCardFromStock();
		void moveCardFromColToCol(int, int, int);
		void moveCardToFoundation(int, CardSuit);
		void moveCardFromWasteToCol(int);
		void returnCardFromFoundationToCol(CardSuit, int);

		// Getters
		const deck& getTableauPile(int) const;
		const deck& getFoundationPile(CardSuit) const;
		const deck& getStockPile() const;
		const deck& getWastePile() const;

		// Auto functions TODO in future update :)
	private:
		void deckInit(deck&);

		void moveTableauToFoundation(CardSuit, int);
		void moveWasteToFoundation(CardSuit);

		bool isValidMove(card&, int);
		bool isValidMoveToFoundation(CardSuit, card&);
		void openTopCard(int);
		int getTopCardIndexFromLongestCol() const;
	};
}
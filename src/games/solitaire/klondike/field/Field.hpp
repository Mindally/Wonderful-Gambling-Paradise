#pragma once

#include "../../../../core/model/card/Card.hpp"
#include "../../../../core/model/deck/Deck.hpp"
#include "../../card_position/CardPosition.hpp"
#include "../../card_position/CardPositionPresets.hpp"
#include "../../../../core/TVector/TVector.h"
#include <iostream>

namespace wgp {

	namespace klondike {

		class Field
		{
			TVector<Deck> _tableauPiles{ {Deck(19), Deck(19), Deck(19), Deck(19), Deck(19), Deck(19), Deck(19)} };
			TVector<Deck> _foundationPiles{ {Deck(13), Deck(13), Deck(13), Deck(13)} };
			Deck _stockPile{ 24 };
			Deck _wastePile{ 24 };
		public:
			// === ������������ ===
			Field();
			Field(std::mt19937&);

			// === ����� ����������� � ������� ===
			void print() const;

			// === ������ ����������� ���� �� ���� (����) ===
			void openCardFromStock();
			void moveCardFromColToCol(const solitaire::CardPosition&, const solitaire::CardPosition&);
			void moveCardToFoundation(const solitaire::CardPosition&, CardSuit);
			void moveCardFromWasteToCol(const solitaire::CardPosition&);
			void returnCardFromFoundationToCol(const solitaire::CardPosition&, CardSuit);

			// === ������ ��������������� ����������� ���� �� ���� (��������) ===
			// TODO

			// === ������� ===
			bool foundationPilesIsFull() const;
			const Deck& getTableauPile(int) const;
			const Deck& getFoundationPile(CardSuit) const;
			const Deck& getStockPile() const;
			const Deck& getWastePile() const;

			const Deck& getPile(const solitaire::CardPosition&) const;

			const Card& getCard(const solitaire::CardPosition&) const;

		private:
			// === ����� ����� ������������ Field ===
			void fieldInit(Deck&);

			// === ��������� ������ ����������� ���� ===
			void moveTableauToFoundation(const solitaire::CardPosition&, CardSuit);
			void moveWasteToFoundation(CardSuit);

			// === �������������� ������� ��� ������� ===
			bool isValidSuit(const Card&, const Card&);
			bool isValidRank(const Card&, const Card&);

			// === ������ �������� ������������ ���� ===
			bool isValidMove(const Card&, const solitaire::CardPosition&);
			bool isValidMoveToFoundation(const Card&, CardSuit);

			// === ������ ������ ===
			void openTopCard(const solitaire::CardPosition&);
			int getTopCardIndexFromLongestCol() const;

			// === ��������� ������ ===
			Deck& getPile(const solitaire::CardPosition&);
		};
	}
}
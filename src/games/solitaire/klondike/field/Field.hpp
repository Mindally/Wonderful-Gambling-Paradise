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
			// === Конструкторы ===
			Field();
			Field(std::mt19937&);

			// === Метод отображения в консоль ===
			void print() const;

			// === Медоты перемещения карт по полю (ходы) ===
			void openCardFromStock();
			void moveCardFromColToCol(const solitaire::CardPosition&, const solitaire::CardPosition&);
			void moveCardToFoundation(const solitaire::CardPosition&, CardSuit);
			void moveCardFromWasteToCol(const solitaire::CardPosition&);
			void returnCardFromFoundationToCol(const solitaire::CardPosition&, CardSuit);

			// === Методы автоматического перемещения карт по полю (автоходы) ===
			// TODO

			// === Геттеры ===
			bool foundationPilesIsFull() const;
			const Deck& getTableauPile(int) const;
			const Deck& getFoundationPile(CardSuit) const;
			const Deck& getStockPile() const;
			const Deck& getWastePile() const;

			const Deck& getPile(const solitaire::CardPosition&) const;

			const Card& getCard(const solitaire::CardPosition&) const;

		private:
			// === Общий метод инциализации Field ===
			void fieldInit(Deck&);

			// === Приватные методы перемещения карт ===
			void moveTableauToFoundation(const solitaire::CardPosition&, CardSuit);
			void moveWasteToFoundation(CardSuit);

			// === Дополнительные функции для Косынки ===
			bool isValidSuit(const Card&, const Card&);
			bool isValidRank(const Card&, const Card&);

			// === Методы проверки правильности хода ===
			bool isValidMove(const Card&, const solitaire::CardPosition&);
			bool isValidMoveToFoundation(const Card&, CardSuit);

			// === Прочие методы ===
			void openTopCard(const solitaire::CardPosition&);
			int getTopCardIndexFromLongestCol() const;

			// === Приватный геттер ===
			Deck& getPile(const solitaire::CardPosition&);
		};
	}
}
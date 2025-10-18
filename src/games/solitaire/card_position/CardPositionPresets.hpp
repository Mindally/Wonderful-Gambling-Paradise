#include "CardPosition.hpp"
#include "../../../core/model/card/Card.hpp"

namespace wgp {

	namespace klondike {

		inline solitaire::CardPosition foundation(CardSuit suit, int cardIndex = 0) {
			return solitaire::CardPosition(solitaire::SolitaireType::Klondike, solitaire::PileType::Foundation, static_cast<int>(suit), cardIndex);
		}

		inline solitaire::CardPosition tableau(int pileIndex, int cardIndex = 0) {
			return solitaire::CardPosition(solitaire::SolitaireType::Klondike, solitaire::PileType::Tableau, pileIndex, cardIndex);
		}

		inline solitaire::CardPosition stock(int cardIndex = 0) {
			return solitaire::CardPosition(solitaire::SolitaireType::Klondike, solitaire::PileType::Stock, 0, cardIndex);
		}

		inline solitaire::CardPosition waste(int cardIndex = 0) {
			return solitaire::CardPosition(solitaire::SolitaireType::Klondike, solitaire::PileType::Waste, 0, cardIndex);
		}
	}

	// Другие namespace и другие Пасьянсы
}
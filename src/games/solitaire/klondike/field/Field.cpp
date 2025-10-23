#include "Field.hpp"

namespace wgp {

	namespace klondike {

// =============================================
//  ŒÕ—“–” “Œ–€
// =============================================

		Field::Field() {
			Deck deck;
			deck.shuffle();
			fieldInit(deck);
		}

		Field::Field(std::mt19937& gen) {
			Deck deck;
			deck.shuffle(gen);
			fieldInit(deck);
		}

// =============================================
// Ã≈“Œƒ Œ¡–¿∆≈Õ»ﬂ ¬  ŒÕ—ŒÀ‹
// =============================================

		void Field::print() const {
			std::cout << _stockPile.topIndex() + 1 << " ";
			if (!_wastePile.isEmpty())	_wastePile.getTopCard().print();
			else std::cout << "BL";

			std::cout << "    ";
			for (int i = 0; i < 4; i++) {
				if (_foundationPiles[i].isEmpty()) std::cout << "F" << i << " ";
				else {
					_foundationPiles[i].getTopCard().print();
					std::cout << " ";
				}
			}
			std::cout << std::endl << std::endl;

			for (int row = 0; row < getTopCardIndexFromLongestCol() + 1; row++) {
				for (int col = 0; col < 7; col++) {
					_tableauPiles[col][row].print();
					std::cout << " ";
				}
				std::cout << std::endl;
			}
		}

// =============================================
// Ã≈“Œƒ€ œ≈–≈Ã≈Ÿ≈Õ»ﬂ  ¿–“ œŒ œŒÀﬁ (’Œƒ€)
// =============================================

		void Field::openCardFromStock() {

			if (_stockPile.isEmpty() && _wastePile.isEmpty()) {
				throw std::logic_error("klondike::Field.openCardFromStock: Can't open card from stock - stock and waste are empty");
			}

			if (!_stockPile.isEmpty()) {
				_stockPile.getTopCard().setState(CardState::FaceUp);
				_wastePile.append(_stockPile.getTopCard());
				_stockPile.erase();
			}
			else {
				_wastePile.shrinkToFit();
				_stockPile.assign(_wastePile, Direction::Reverse);
				_stockPile.flip();
				_wastePile.clear();
			}

		}

		void Field::moveCardFromColToCol(const solitaire::CardPosition& source, const solitaire::CardPosition& destination) {
			if (source.getPileType() != solitaire::PileType::Tableau ||
				destination.getPileType() != solitaire::PileType::Tableau)
			{
				throw std::invalid_argument("klondike::Field.moveCardFromColToCol: Invalid argument 'source' or 'destination' - pile type must be Tableau");
			}

			if (getCard(source).state() != CardState::FaceUp) {
				throw std::invalid_argument("klondike::Field.moveCardFromColToCol: Invalid argument 'source_card' - must be FaceUp");
			}

			if (isValidMove(getCard(source), destination)) {
				Deck& sourcePile = getPile(source);
				Deck& destinationPile = getPile(destination);

				Deck temp(sourcePile, source.getCardIndex(), sourcePile.topIndex());

				for (int i = sourcePile.topIndex(); i >= source.getCardIndex(); i--) {
					sourcePile.erase();
				}
				destinationPile.append(temp);
				openTopCard(source);
			}
		}

		void Field::moveCardToFoundation(const solitaire::CardPosition& source, CardSuit foundationSuit) {
			if (foundationSuit != CardSuit::Clubs &&
				foundationSuit != CardSuit::Diamonds &&
				foundationSuit != CardSuit::Hearts &&
				foundationSuit != CardSuit::Spades)
			{
				throw std::invalid_argument("klondike::Field.moveCardToFoundation: Invalid argument 'foundationSuit' - must be entered correctly");
			}

			if (source.getPileType() == solitaire::PileType::Waste) {
				moveWasteToFoundation(foundationSuit);
			}

			else moveTableauToFoundation(source, foundationSuit);
		}

		void Field::moveCardFromWasteToCol(const solitaire::CardPosition& destination) {
			if (destination.getPileType() != solitaire::PileType::Tableau) {
				throw std::invalid_argument("klondike::Field.moveCardToFoundation: Invalid argument 'destination' - pile type must be Tableau");
			}

			if (!_wastePile.isEmpty()) {
				if (isValidMove(_wastePile.getTopCard(), destination)) {
					getPile(destination).append(_wastePile.getTopCard());
					_wastePile.erase();
				}
			}
		}

		void Field::returnCardFromFoundationToCol(const solitaire::CardPosition& destination, CardSuit foundationSuit) {
			if (foundationSuit != CardSuit::Clubs &&
				foundationSuit != CardSuit::Diamonds &&
				foundationSuit != CardSuit::Hearts &&
				foundationSuit != CardSuit::Spades)
			{
				throw std::invalid_argument("klondike::Field.returnCardFromFoundationToCol: Invalid argument 'foundationSuit' - must be entered correctly");
			}
			if (destination.getPileType() != solitaire::PileType::Tableau) {
				throw std::invalid_argument("klondike::Field.returnCardFromFoundationToCol: Invalid argument 'destination' - pile type must be Tableau");
			}

			Deck& foundationPile = getPile(foundation(foundationSuit));

			if (!foundationPile.isEmpty()) {
				if (isValidMove(foundationPile.getTopCard(), destination)) {
					getPile(destination).append(foundationPile.getTopCard());
					foundationPile.erase();
				}
			}
		}

// =============================================
// √≈““≈–€
// =============================================

		bool Field::foundationPilesIsFull() const {
			for (int i = 0; i < 4; i++) {
				if (!_foundationPiles[i].isFull()) return false;
			}
			return true;
		}

		const Deck& Field::getTableauPile(int col) const {
			if (col < 0 || col > 6) {
				throw std::invalid_argument("klondike::Field.getTableauPile: Invalid argument 'col' - must be in the range from 0 to 6");
			}
			return _tableauPiles[col];
		}

		const Deck& Field::getFoundationPile(CardSuit suit) const {
			if (suit != CardSuit::Clubs &&
				suit != CardSuit::Diamonds &&
				suit != CardSuit::Hearts &&
				suit != CardSuit::Spades)
			{
				throw std::invalid_argument("klondike::Field.getFoundationPile: Invalid argument 'suit' - must be entered correctly");
			}
			return _foundationPiles[static_cast<int>(suit)];
		}

		const Deck& Field::getStockPile() const {
			return _stockPile;
		}

		const Deck& Field::getWastePile() const {
			return _wastePile;
		}

		const Deck& Field::getPile(const solitaire::CardPosition& source) const {
			if (source.getSolitaireType() != solitaire::SolitaireType::Klondike) {
				throw std::invalid_argument("klondike::Field.getPile: Invalid argument 'source' - solitaire type must be Klondike");
			}

			switch (source.getPileType()) {

			case solitaire::PileType::Foundation:
				return _foundationPiles[source.getPileIndex()];

			case solitaire::PileType::Tableau:
				return _tableauPiles[source.getPileIndex()];

			case solitaire::PileType::Stock:
				return _stockPile;

			case solitaire::PileType::Waste:
				return _wastePile;

			default:
				throw std::invalid_argument("klondike::Field.getPile: Invalid argument 'source' - must be entered correctly");
			}
		}

		const Card& Field::getCard(const solitaire::CardPosition& source) const {
			const Deck& pile = getPile(source);
			return pile[source.getCardIndex()];
		}

// =============================================
// Œ¡Ÿ»… Ã≈“Œƒ »Õ»÷¿À»«¿÷»» Field
// =============================================

		void Field::fieldInit(Deck& deck) {
			for (int col = 0; col < 7; col++) {
				for (int row = 0; row < 18; row++) {
					if (row < col + 1) {
						if (row == col) deck.getTopCard().setState(CardState::FaceUp);
						_tableauPiles[col].append(deck.getTopCard());
						deck.erase();
					}
				}
			}
			for (int i = 0; i < 24; i++) {
				_stockPile.append(deck.getTopCard());
				deck.erase();
			}
		}

// =============================================
// œ–»¬¿“Õ€≈ Ã≈“Œƒ€ œ≈–≈Ã≈Ÿ≈Õ»ﬂ  ¿–“
// =============================================

		void Field::moveTableauToFoundation(const solitaire::CardPosition& source, CardSuit foundationSuit) {
			if (source.getPileType() != solitaire::PileType::Tableau) {
				throw std::invalid_argument("klondike::Field.moveTableauToFoundation: Invalid argument 'source' - pile type must be Tableau");
			}

			Deck& foundationPile = getPile(foundation(foundationSuit));

			if (isValidMoveToFoundation(_tableauPiles[source.getPileIndex()].getTopCard(), foundationSuit)) {
				foundationPile.append(_tableauPiles[source.getPileIndex()].getTopCard());
				_tableauPiles[source.getPileIndex()].erase();
				openTopCard(source);
			}
		}

		void Field::moveWasteToFoundation(CardSuit suit) {
			Deck& foundationPile = getPile(foundation(suit));

			if (isValidMoveToFoundation(_wastePile.getTopCard(), suit)) {
				foundationPile.append(_wastePile.getTopCard());
				_wastePile.erase();
			}
		}

// =============================================
// ƒŒœŒÀÕ»“≈À‹Õ€≈ ‘”Õ ÷»» ƒÀﬂ  Œ—€Õ »
// =============================================

		bool Field::isValidSuit(const Card& movingCard, const Card& targetCard) {
			if ((targetCard.isRed() && movingCard.isBlack()) ||
				(targetCard.isBlack() && movingCard.isRed()))
			{
				return true;
			}
			return false;
		}

		bool Field::isValidRank(const Card& movingCard, const Card& targetCard) {
			if (targetCard.rank() == CardRank::RA) return false;
			if (movingCard.rank() == CardRank::RA && targetCard.rank() == CardRank::R2) return true;
			if (static_cast<int>(targetCard.rank()) == static_cast<int>(movingCard.rank()) + 1) return true;
			return false;
		}

// =============================================
// Ã≈“Œƒ€ œ–Œ¬≈– » œ–¿¬»À‹ÕŒ—“» ’Œƒ¿
// =============================================

		bool Field::isValidMove(const Card& card, const solitaire::CardPosition& destination) {
			if (card.state() != CardState::FaceUp) {
				throw std::invalid_argument("klondike::Field.isValidMove: Invalid argument 'card' - state must be FaceUp");
			}
			if (destination.getPileType() != solitaire::PileType::Tableau) {
				throw std::invalid_argument("klondike::Field.isValidMove: Invalid argument 'destination' - pile type must be Tableau");
			}

			Deck& tableauPile = getPile(destination);

			if (!getPile(destination).isEmpty()) {
				if (isValidSuit(card, tableauPile.getTopCard()) &&
					isValidRank(card, tableauPile.getTopCard()))
				{
					return true;
				}
			}
			else {
				if (card.rank() == CardRank::RK) return true;
			}
			return false;
		}

		bool Field::isValidMoveToFoundation(const Card& card, CardSuit foundationSuit) {
			if (card.state() != CardState::FaceUp) {
				throw std::invalid_argument("klondike::Field.isValidMoveToFoundation: Invalid argument 'card' - state must be FaceUp");
			}
			if (foundationSuit != CardSuit::Clubs &&
				foundationSuit != CardSuit::Diamonds &&
				foundationSuit != CardSuit::Hearts &&
				foundationSuit != CardSuit::Spades)
			{
				throw std::invalid_argument("klondike::Field.isValidMoveToFoundation: Invalid argument 'foundationSuit' - must be entered correctly");
			}

			Deck& foundationPile = getPile(foundation(foundationSuit));

			if (card.suit() == foundationSuit) {
				if (!foundationPile.isEmpty())
				{
					if (foundationPile.getTopCard().rank() == CardRank::RA &&
						card.rank() == CardRank::R2) return true;
					else if (isValidRank(card, foundationPile.getTopCard())) {
						return true;
					}
				}
				else {
					if (card.rank() == CardRank::RA) return true;
				}
			}
			return false;
		}

// =============================================
// œ–Œ◊»≈ Ã≈“Œƒ€
// =============================================

		void Field::openTopCard(const solitaire::CardPosition& source) {
			if (source.getPileType() != solitaire::PileType::Tableau) {
				throw std::invalid_argument("klondike::Field.openTopCard: Invalid argument 'source' - pile type must be Tableau");
			}

			if (!_tableauPiles[source.getPileIndex()].isEmpty()) {
				if (_tableauPiles[source.getPileIndex()].getTopCard().state() == CardState::FaceDown) {
					_tableauPiles[source.getPileIndex()].getTopCard().flip();
				}
			}
		}

		int Field::getTopCardIndexFromLongestCol() const {
			int maxIndex = 0;
			for (int i = 0; i < 7; i++) {
				if (_tableauPiles[i].topIndex() > maxIndex) maxIndex = _tableauPiles[i].topIndex();
			}
			return maxIndex;
		}

// =============================================
// œ–»¬¿“Õ€… √≈““≈–
// =============================================

		Deck& Field::getPile(const solitaire::CardPosition& source) {
			if (source.getSolitaireType() != solitaire::SolitaireType::Klondike) {
				throw std::invalid_argument("klondike::Field.getPile: Invalid argument 'source' - solitaire type must be Klondike");
			}

			switch (source.getPileType()) {

			case solitaire::PileType::Foundation:
				return _foundationPiles[source.getPileIndex()];

			case solitaire::PileType::Tableau:
				return _tableauPiles[source.getPileIndex()];

			case solitaire::PileType::Stock:
				return _stockPile;

			case solitaire::PileType::Waste:
				return _wastePile;

			default:
				throw std::invalid_argument("klondike::Field.getPile: Invalid argument 'source' - pile type must match Klondike");
			}
		}
	}
}
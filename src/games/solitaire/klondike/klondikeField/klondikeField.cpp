#include "klondikeField.h"

namespace WGP {
	klondikeField::klondikeField() {
		deck deck;
		deck.shuffle();
		deckInit(deck);
	}

	klondikeField::klondikeField(std::mt19937& gen) {
		deck deck;
		deck.shuffle(gen);
		deckInit(deck);
	}

	void klondikeField::print() const {
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

	bool klondikeField::foundationPilesIsFull() const {
		for (int i = 0; i < 4; i++) {
			if (!_foundationPiles[i].isFull()) return false;
		}
		return true;
	}

	void klondikeField::openCardFromStock() {
		if (_stockPile.isEmpty() && _wastePile.isEmpty()) {
			throw std::logic_error("klondikeField.openCardFromStock: Can't open card from stock");
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

	void klondikeField::moveCardFromColToCol(int from, int to, int index) {
		if (from < 0 || from > 6) {
			throw std::invalid_argument("klondikeField.moveCardFromColToCol: Invalid argument 'from' - must be in the range from 0 to 6");
		}
		if (to < 0 || to > 6) {
			throw std::invalid_argument("klondikeField.moveCardFromColToCol: Invalid argument 'to' - must be in the range from 0 to 6");
		}
		if (index < 0 || index > 17) {
			throw std::invalid_argument("klondikeField.moveCardFromColToCol: Invalid argument 'index' - must be in range from 0 to 17");
		}
		if (_tableauPiles[from][index].state() != CardState::FaceUp) {
			throw std::invalid_argument("klondikeField.moveCardFromColToCol: Invalid argument 'index' - must be FaceUp");
		}

		if (isValidMove(_tableauPiles[from][index], to)) {
			deck temp(_tableauPiles[from], index, _tableauPiles[from].topIndex());
			for (int i = _tableauPiles[from].topIndex(); i >= index; i--) {
				_tableauPiles[from].erase();
			}
			_tableauPiles[to].append(temp);
			openTopCard(from);
		}
	}

	void klondikeField::moveCardToFoundation(int from, CardSuit foundationSuit) {
		if ((from < 0 || from > 6) && from != WASTE_COL) {
			throw std::invalid_argument("klondikeField.moveCardToFoundation: Invalid argument 'from' - must be in the range from 0 to 6 or WASTE_COL");
		}
		if (foundationSuit != CardSuit::Clubs &&
			foundationSuit != CardSuit::Diamonds &&
			foundationSuit != CardSuit::Hearts &&
			foundationSuit != CardSuit::Spades)
		{
			throw std::invalid_argument("klondikeField.moveCardToFoundation: Invalid argument 'foundationSuit' - must be entered correctly");
		}

		if (from == WASTE_COL) moveWasteToFoundation(foundationSuit);
		else moveTableauToFoundation(foundationSuit, from);
	}

	void klondikeField::moveCardFromWasteToCol(int to) {
		if (to < 0 || to > 6) {
			throw std::invalid_argument("klondikeField.moveCardFromWasteToCol: Invalid argument 'to' - must be in the range from 0 to 6");
		}

		if (!_wastePile.isEmpty()) {
			if (isValidMove(_wastePile.getTopCard(), to)) {
				_tableauPiles[to].append(_wastePile.getTopCard());
				_wastePile.erase();
			}
		}
	}

	void klondikeField::returnCardFromFoundationToCol(CardSuit foundationSuit, int to) {
		if (foundationSuit != CardSuit::Clubs &&
			foundationSuit != CardSuit::Diamonds &&
			foundationSuit != CardSuit::Hearts &&
			foundationSuit != CardSuit::Spades)
		{
			throw std::invalid_argument("klondikeField.returnCardFromFoundationToCol: Invalid argument 'foundationSuit' - must be entered correctly");
		}
		if (to < 0 || to > 6) {
			throw std::invalid_argument("klondikeField.returnCardFromFoundationToCol: Invalid argument 'to' - must be in the range from 0 to 6");
		}

		if (!_foundationPiles[static_cast<int>(foundationSuit)].isEmpty()) {
			if (isValidMove(_foundationPiles[static_cast<int>(foundationSuit)].getTopCard(), to)) {
				_tableauPiles[to].append(_foundationPiles[static_cast<int>(foundationSuit)].getTopCard());
				_foundationPiles[static_cast<int>(foundationSuit)].erase();
			}
		}
	}

	// Getters

	const deck& klondikeField::getTableauPile(int col) const {
		if (col < 0 || col > 6) {
			throw std::invalid_argument("klondikeField.getTableauPile: Invalid argument 'col' - must be in the range from 0 to 6");
		}
		return _tableauPiles[col];
	}

	const deck& klondikeField::getFoundationPile(CardSuit suit) const {
		if (suit != CardSuit::Clubs &&
			suit != CardSuit::Diamonds &&
			suit != CardSuit::Hearts &&
			suit != CardSuit::Spades)
		{
			throw std::invalid_argument("klondikeField.getFoundationPile: Invalid argument 'suit' - must be entered correctly");
		}
		return _foundationPiles[static_cast<int>(suit)];
	}

	const deck& klondikeField::getStockPile() const {
		return _stockPile;
	}

	const deck& klondikeField::getWastePile() const {
		return _wastePile;
	}

	// Auto functions TODO

	// Private functions

	void klondikeField::deckInit(deck& deck) {
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

	void klondikeField::moveTableauToFoundation(CardSuit suit, int from) {
		if (isValidMoveToFoundation(suit, _tableauPiles[from].getTopCard())) {
			_foundationPiles[static_cast<int>(suit)].append(_tableauPiles[from].getTopCard());
			_tableauPiles[from].erase();
			openTopCard(from);
		}
	}

	void klondikeField::moveWasteToFoundation(CardSuit suit) {
		if (isValidMoveToFoundation(suit, _wastePile.getTopCard())) {
			_foundationPiles[static_cast<int>(suit)].append(_wastePile.getTopCard());
			_wastePile.erase();
		}
	}

	bool klondikeField::isValidMove(card& card, int to) {
		if (card.state() != CardState::FaceUp) {
			throw std::invalid_argument("klondikeField.isValidMove: Invalid argument 'card' - state must be FaceUp");
		}
		if (to < 0 || to > 6) {
			throw std::invalid_argument("klondikeField.isValidMove: Invalid argument 'to' - state must be in range from 0 to 6");
		}

		if (!_tableauPiles[to].isEmpty()) {
			if ((solitaireIsValidSuit(card.suit(), _tableauPiles[to].getTopCard().suit()))
				&& (solitaireIsValidRank(card.rank(), _tableauPiles[to].getTopCard().rank()))) return true;
		}
		else {
			if (card.rank() == CardRank::RK) return true;
		}
		throw std::logic_error("klondikeField.isValidMove: Move is not valid");
	}

	bool klondikeField::isValidMoveToFoundation(CardSuit foundationSuit, card& card) {
		if (card.state() != CardState::FaceUp) {
			throw std::invalid_argument("klondikeField.isValidMoveToFoundation: Invalid argument 'card' - state must be FaceUp");
		}
		if (foundationSuit != CardSuit::Clubs &&
			foundationSuit != CardSuit::Diamonds &&
			foundationSuit != CardSuit::Hearts &&
			foundationSuit != CardSuit::Spades)
		{
			throw std::invalid_argument("klondikeField.isValidMoveToFoundation: Invalid argument 'foundationSuit' - must be entered correctly");
		}

		if (card.suit() == foundationSuit) {
			if (!_foundationPiles[static_cast<int>(foundationSuit)].isEmpty()) {
				if (_foundationPiles[static_cast<int>(foundationSuit)].getTopCard().rank() == CardRank::RA &&
					card.rank() == CardRank::R2) return true;
				else if (solitaireIsValidRank(_foundationPiles[static_cast<int>(foundationSuit)].getTopCard().rank(), card.rank())) {
					return true;
				}
			}
			else {
				if (card.rank() == CardRank::RA) return true;
			}
		}
		throw std::logic_error("klondikeField.isValidMoveToFoundation: Move is not valid");
	}

	void klondikeField::openTopCard(int col) {
		if (!_tableauPiles[col].isEmpty()) {
			if (_tableauPiles[col].getTopCard().state() == CardState::FaceDown) {
				_tableauPiles[col].getTopCard().flip();
			}
		}
	}

	int klondikeField::getTopCardIndexFromLongestCol() const {
		int maxIndex = 0;
		for (int i = 0; i < 7; i++) {
			if (_tableauPiles[i].topIndex() > maxIndex) maxIndex = _tableauPiles[i].topIndex();
		}
		return maxIndex;
	}
}
#include "deck.h"

// Самую верхнюю карту будем хранить в конце массива

namespace WGP {
	deck::deck() {
		_topIndex = 51;
		int i = 0;
		for (int suit = 0; suit < 4; suit++) {
			for (int rank = static_cast<int>(CardRank::R2); rank <= static_cast<int>(CardRank::RA); rank++) {
				_deck.push_back(card(static_cast<CardSuit>(suit), static_cast<CardRank>(rank), CardState::FaceDown));
				i++;
			}
		}
		_deck.shrink_to_fit();
	}

	deck::deck(int size) {
		if (size < 1) throw std::invalid_argument("deck: Invalid argument 'size' - must be > 0");
		_topIndex = -1;
		for (int i = 0; i < size; i++) _deck.push_back(card());
		_deck.shrink_to_fit();
	}

	deck::deck(int size, const card* data) {
		if (size < 1) throw std::invalid_argument("deck: Invalid argument 'size' - must be > 0");
		if (data == nullptr) throw std::invalid_argument("deck: Invalid argument 'data' - nullptr is passed");
		_topIndex = size - 1;
		int index = 0;
		for (int i = size - 1; i >= 0; i--) {
			_deck.push_back(data[index]);
			index++;
		}
		_deck.shrink_to_fit();
	}

	deck::deck(std::initializer_list<card> data) {
		if (data.size() < 1) throw std::invalid_argument("deck: Invalid argument 'data.size()' - must be > 0");
		_topIndex = static_cast<int>(data.size() - 1);
		auto it = data.begin();
		for (int i = _topIndex; i >= 0; i--) {
			_deck.push_back(*it);
			it++;
		}
		_deck.shrink_to_fit();
	}

	deck::deck(std::initializer_list<const char*> data) {
		if (data.size() < 1) throw std::invalid_argument("deck: Invalid argument 'data.size()' - must be > 0");
		_topIndex = static_cast<int>(data.size() - 1);
		auto it = data.begin();
		for (int i = _topIndex; i >= 0; i--) {
			_deck.push_back(card(*it));
			it++;
		}
		_deck.shrink_to_fit();
	}

	deck::deck(const deck& other) {
		_topIndex = other._topIndex;
		_deck = other._deck;
	}

	deck::deck(const deck& source, int fromIndex, int toIndex) {
		if (fromIndex < 0 || fromIndex > source.size() - 1) {
			throw std::invalid_argument("deck: Invalid argument 'fromIndex' - must be >= 0 and < size of source");
		}
		if (toIndex < 0 || toIndex > source.size() - 1) {
			throw std::invalid_argument("deck: Invalid argument 'toIndex' - must be >= 0 and < size of source");
		}
		if (fromIndex > toIndex) {
			throw std::invalid_argument("deck: Invalid argument 'fromIndex' & 'toIndex' - fromIndex cannot be greater than toIndex");
		}
		_topIndex = size() - 1;
		for (int i = fromIndex; i < toIndex + 1; i++) {
			_deck.push_back(source._deck[i]);
		}
		_deck.shrink_to_fit();
	}

	void deck::shuffle() {
		vectorShuffle(_deck);
	}

	void deck::shuffle(std::mt19937& gen) {
		vectorShuffle(_deck, gen);
	}

	void deck::print() const {
		for (int i = size() - 1; i >= 0; i--) {
			_deck[i].print();
			std::cout << " ";
		}
	}

	bool deck::isEmpty() const {
		if (_topIndex == -1) return true;
		return false;
	}

	bool deck::isFull() const {
		if (_topIndex == size() - 1) return true;
		return false;
	}

	bool deck::areAllCardsFaceUp() const {
		for (int i = 0; i <= _topIndex; i++) {
			if (_deck[i].state() == CardState::FaceDown) return false;
		}
		return true;
	}

	void deck::append(card card) {
		if (card.state() == CardState::Blank) {
			throw std::logic_error("deck.append: unable to append a card - card state is Blank");
		}
		if (isFull()) throw std::out_of_range("deck.append: unable to append - deck is full");
		_topIndex++;
		_deck[_topIndex] = card;
	}

	void deck::append(card* cards, int len) {
		if (_topIndex + len > size() - 1) {
			throw std::out_of_range("deck.append: unable to append - deck size will be out of range");
		}
		for (int i = 1; i < len + 1; i++) {
			_deck[_topIndex + i] = cards[i - 1];
		}
		_topIndex += len;
	}

	void deck::append(const deck& other) {
		if (_topIndex + other.size() > size() - 1) {
			throw std::out_of_range("deck.append: unable to append - deck size will be out of range");
		}
		for (int i = 1; i < other.size() + 1; i++) {
			_deck[_topIndex + i] = other._deck[i - 1];
		}
		_topIndex += other.size();
	}

	void deck::erase() {
		if (isEmpty()) throw std::logic_error("deck.erase: unable to erase - deck is empty");
		_deck[_topIndex].setState(CardState::Blank);
		_topIndex--;
	}

	void deck::clear() {
		if (!isEmpty()) {
			for (int i = _topIndex; i >= 0; i--) {
				erase();
			}
		}
	}

	void deck::assign(const deck& other, Direction dir) {
		this->resize(other.size());
		if (dir == Direction::Forward) {
			for (int i = 0; i < other.size(); i++) this->_deck[i] = other._deck[i];
			this->_topIndex = other._topIndex;
		}
		else {
			int index = 0;
			for (int i = other.size() - 1; i >= 0; i--) {
				this->_deck[index] = other._deck[i];
				index++;
			}
			this->_topIndex = size() - 1;
		}
	}

	void deck::shrinkToFit() {
		resize(_topIndex + 1);
	}

	void deck::resize(int newSize) {
		if (newSize <= 0) throw std::invalid_argument("deck.resize: Invalid argument 'newSize' - must be > 0");
		if (size() == newSize) return;
		_deck.resize(newSize);
		if (newSize < size()) _topIndex = newSize - 1;
		else {
			for (int i = size(); i < newSize; i++) {
				_deck.push_back(card());
			}
		}
	}

	int deck::size() const {
		return _deck.size();
	}

	int deck::topIndex() const {
		return _topIndex;
	}

	card& deck::getTopCard() {
		if (isEmpty()) {
			throw std::logic_error("deck.getTopCard: unable to get top card - deck is empty");
		}
		return _deck[_topIndex];
	}

	card& deck::getCard(int index) {
		if (index < 0 || index > size() - 1) {
			throw std::invalid_argument("deck.getCard: Invalid argument 'index' - must be >= 0 and < size of deck");
		}
		return _deck[index];
	}

	const card& deck::getTopCard() const {
		if (isEmpty()) {
			throw std::logic_error("deck.getTopCard const: unable to get top card - deck is empty");
		}
		return _deck[_topIndex];
	}

	const card& deck::getCard(int index) const {
		if (index < 0 || index > size() - 1) {
			throw std::invalid_argument("deck.getCard const: Invalid argument 'index' - must be >= 0 and < size of deck");
		}
		return _deck[index];
	}

	void deck::operator=(const deck& other) {
		this->assign(other, Direction::Forward);
	}

	card& deck::operator[](int index) {
		return getCard(index);
	}

	const card& deck::operator[](int index) const {
		return getCard(index);
	}
}
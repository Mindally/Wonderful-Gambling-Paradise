#include "Deck.hpp"

namespace wgp {

// =============================================
//  ŒÕ—“–” “Œ–€
// =============================================

	Deck::Deck() :
		_topIndex(51)
	{
		int i = 0;
		for (int suit = 0; suit < 4; suit++) {
			for (int rank = static_cast<int>(CardRank::R2); rank <= static_cast<int>(CardRank::RA); rank++) {
				_deck.push_back(Card(static_cast<CardSuit>(suit), static_cast<CardRank>(rank), CardState::FaceDown));
				i++;
			}
		}
		_deck.shrink_to_fit();
	}

	Deck::Deck(int size) :
		_topIndex(-1)
	{
		if (size < 1) throw std::invalid_argument("Deck: Invalid argument 'size' - must be > 0");
		for (int i = 0; i < size; i++) _deck.push_back(Card());
		_deck.shrink_to_fit();
	}

	Deck::Deck(int size, const Card* data) :
		_topIndex(size - 1)
	{
		if (size < 1) throw std::invalid_argument("Deck: Invalid argument 'size' - must be > 0");
		if (data == nullptr) throw std::invalid_argument("Deck: Invalid argument 'data' - nullptr is passed");
		int index = 0;
		for (int i = size - 1; i >= 0; i--) {
			_deck.push_back(data[index]);
			index++;
		}
		_deck.shrink_to_fit();
	}

	Deck::Deck(std::initializer_list<Card> data) :
		_topIndex(static_cast<int>(data.size() - 1))
	{
		if (data.size() < 1) throw std::invalid_argument("deck: Invalid argument 'data.size()' - must be > 0");
		auto it = data.begin();
		for (int i = _topIndex; i >= 0; i--) {
			_deck.push_back(*it);
			it++;
		}
		_deck.shrink_to_fit();
	}

	Deck::Deck(std::initializer_list<const char*> data) :
		_topIndex(static_cast<int>(data.size() - 1))
	{
		if (data.size() < 1) throw std::invalid_argument("deck: Invalid argument 'data.size()' - must be > 0");
		auto it = data.begin();
		for (int i = _topIndex; i >= 0; i--) {
			_deck.push_back(Card(*it));
			it++;
		}
		_deck.shrink_to_fit();
	}

	Deck::Deck(const Deck& other) :
		_topIndex(other._topIndex),
		_deck(other._deck)
	{}

	Deck::Deck(const Deck& source, int fromIndex, int toIndex) :
		_topIndex(size() - 1)
	{
		if (fromIndex < 0 || fromIndex > source.size() - 1) {
			throw std::invalid_argument("deck: Invalid argument 'fromIndex' - must be >= 0 and < size of source");
		}
		if (toIndex < 0 || toIndex > source.size() - 1) {
			throw std::invalid_argument("deck: Invalid argument 'toIndex' - must be >= 0 and < size of source");
		}
		if (fromIndex > toIndex) {
			throw std::invalid_argument("deck: Invalid argument 'fromIndex' & 'toIndex' - fromIndex cannot be greater than toIndex");
		}
		for (int i = fromIndex; i < toIndex + 1; i++) {
			_deck.push_back(source._deck[i]);
		}
		_deck.shrink_to_fit();
	}

// =============================================
// Ã≈“Œƒ€ »«Ã≈Õ≈Õ»ﬂ œŒ«»÷»…  ¿–“ ¬  ŒÀŒƒ≈
// =============================================

	void Deck::shuffle() {
		vectorShuffle(_deck);
	}

	void Deck::shuffle(std::mt19937& gen) {
		vectorShuffle(_deck, gen);
	}

	void Deck::sort() {
		// TODO
	}

// =============================================
// œ–Œ◊»≈ Ã≈“Œƒ€
// =============================================

	void Deck::flip() {
		for (int i = 0; i <= _topIndex; i++) {
			_deck[i].flip();
		}
	}

	void Deck::print() const {
		for (int i = _topIndex; i >= 1; i--) {
			_deck[i].print();
			std::cout << " ";
		}
		_deck[0].print();
	}

	void Deck::assign(const Deck& other, Direction dir) {
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

// =============================================
// Ã≈“Œƒ€ ƒŒ¡¿¬À≈Õ»ﬂ »À» ”ƒ¿À≈Õ»ﬂ  ¿–“
// =============================================

	void Deck::append(Card& Card) {
		if (Card.state() == CardState::Blank) {
			throw std::logic_error("deck.append: unable to append a card - card state is Blank");
		}
		if (isFull()) throw std::out_of_range("deck.append: unable to append - deck is full");
		_topIndex++;
		_deck[_topIndex] = Card;
	}

	void Deck::append(Card* cards, int len) {
		if (_topIndex + len > size() - 1) {
			throw std::out_of_range("deck.append: unable to append - deck size will be out of range");
		}
		for (int i = 1; i < len + 1; i++) {
			_deck[_topIndex + i] = cards[i - 1];
		}
		_topIndex += len;
	}

	void Deck::append(const Deck& other) {
		if (_topIndex + other.size() > size() - 1) {
			throw std::out_of_range("deck.append: unable to append - deck size will be out of range");
		}
		for (int i = 1; i < other.size() + 1; i++) {
			_deck[_topIndex + i] = other._deck[i - 1];
		}
		_topIndex += other.size();
	}

	void Deck::erase() {
		if (isEmpty()) throw std::logic_error("deck.erase: unable to erase - deck is empty");
		_deck[_topIndex].setState(CardState::Blank);
		_topIndex--;
	}

	void Deck::clear() {
		if (!isEmpty()) {
			for (int i = _topIndex; i >= 0; i--) {
				erase();
			}
		}
	}

// =============================================
// Ã≈“Œƒ€ ”œ–¿¬À≈Õ»ﬂ œ¿Ãﬂ“‹ﬁ
// =============================================

	void Deck::shrinkToFit() {
		resize(_topIndex + 1);
	}

	void Deck::resize(int newSize) {
		if (newSize <= 0) throw std::invalid_argument("deck.resize: Invalid argument 'newSize' - must be > 0");
		if (size() == newSize) return;
		_deck.resize(newSize);
		if (newSize < size()) _topIndex = newSize - 1;
		else {
			for (int i = size(); i < newSize; i++) {
				_deck.push_back(Card());
			}
		}
	}

// =============================================
// √≈““–€ «¿œŒÀÕ≈ÕŒ—“»  ŒÀŒƒ€ » —Œ—“ŒﬂÕ»ﬂ  ¿–“
// =============================================

	bool Deck::isEmpty() const {
		if (_topIndex == -1) return true;
		return false;
	}

	bool Deck::isFull() const {
		if (_topIndex == size() - 1) return true;
		return false;
	}

	bool Deck::areAllCardsFaceUp() const {
		for (int i = 0; i <= _topIndex; i++) {
			if (_deck[i].state() == CardState::FaceDown) return false;
		}
		return true;
	}

// =============================================
// √≈““–€
// =============================================

	Card& Deck::getTopCard() {
		if (isEmpty()) {
			throw std::logic_error("deck.getTopCard: unable to get top card - deck is empty");
		}
		return _deck[_topIndex];
	}

	Card& Deck::getCard(int index) {
		if (index < 0 || index > size() - 1) {
			throw std::invalid_argument("deck.getCard: Invalid argument 'index' - must be >= 0 and < size of deck");
		}
		return _deck[index];
	}

	const Card& Deck::getTopCard() const {
		if (isEmpty()) {
			throw std::logic_error("deck.getTopCard const: unable to get top card - deck is empty");
		}
		return _deck[_topIndex];
	}

	const Card& Deck::getCard(int index) const {
		if (index < 0 || index > size() - 1) {
			throw std::invalid_argument("deck.getCard const: Invalid argument 'index' - must be >= 0 and < size of deck");
		}
		return _deck[index];
	}

// =============================================
// œ≈–≈√–”« ¿ Œœ≈–¿“Œ–Œ¬
// =============================================

	void Deck::operator=(const Deck& other) {
		this->assign(other, Direction::Forward);
	}

	Card& Deck::operator[](int index) {
		return getCard(index);
	}

	const Card& Deck::operator[](int index) const {
		return getCard(index);
	}
}
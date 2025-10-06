#include "deck.h"

// Самую верхнюю карту будем хранить в конце массива

deck::deck() {
	_top_index = 51;
	int i = 0;
	for (int suit = Spades; suit >= Clubs; suit--) {
		for (int rank = R2; rank <= RA; rank++) {
			_deck.push_back(card(suit, rank, FaceDown));
			i++;
		}
	}
	_deck.shrink_to_fit();
}

deck::deck(int size) {
	if (size < 1) throw std::invalid_argument("deck: Invalid argument 'size' - must be > 0");
	_top_index = -1;
	for (int i = 0; i < size; i++) _deck.push_back(card());
	_deck.shrink_to_fit();
}

deck::deck(int size, const card* data) {
	if (size < 1) throw std::invalid_argument("deck: Invalid argument 'size' - must be > 0");
	if (data == nullptr) throw std::invalid_argument("deck: Invalid argument 'data' - nullptr is passed");
	_top_index = size - 1;
	int index = 0;
	for (int i = size - 1; i >= 0; i--) {
		_deck.push_back(data[index]);
		index++;
	}
	_deck.shrink_to_fit();
}

deck::deck(std::initializer_list<card> data) {
	if (data.size() < 1) throw std::invalid_argument("deck: Invalid argument 'data.size()' - must be > 0");
	_top_index = data.size() - 1;
	auto it = data.begin();
	for (int i = _top_index; i >= 0; i--) {
		_deck.push_back(*it);
		it++;
	}
	_deck.shrink_to_fit();
}

deck::deck(std::initializer_list<const char*> data) {
	if (data.size() < 1) throw std::invalid_argument("deck: Invalid argument 'data.size()' - must be > 0");
	_top_index = data.size() - 1;
	auto it = data.begin();
	for (int i = _top_index; i >= 0; i--) {
		_deck.push_back(card(*it));
		it++;
	}
	_deck.shrink_to_fit();
}

deck::deck(const deck& other) {
	_top_index = other._top_index;
	_deck = other._deck;
}

deck::deck(const deck& source, int from_index, int to_index) {
	if (from_index < 0 || from_index > source.size() - 1) throw std::invalid_argument("deck: Invalid argument 'from_index' - must be >= 0 and < size of source");
	if (to_index < 0 || to_index > source.size() - 1) throw std::invalid_argument("deck: Invalid argument 'to_index' - must be >= 0 and < size of source");
	if (from_index > to_index) throw std::invalid_argument("deck: Invalid argument 'from_index' & 'to_index' - from_index cannot be greater than to_index");
	_top_index = size() - 1;
	for (int i = from_index; i < to_index + 1; i++) {
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

void deck::print() {
	for (int i = size() - 1; i >= 0; i--) {
		_deck[i].print();
		std::cout << " ";
	}
}

bool deck::is_empty() {
	if (_top_index == -1) return true;
	else return false;
}

bool deck::is_full() {
	if (_top_index == size() - 1) return true;
	else return false;
}

void deck::append(card card) {
	if (card.state() == Blank) throw std::logic_error("deck.append: unable to append a card - card state is Blank");
	if (is_full()) throw std::out_of_range("deck.append: unable to append - deck is full");
	_top_index++;
	_deck[_top_index] = card;
}

void deck::append(card* cards, int len) {
	if (_top_index + len > size() - 1) throw std::out_of_range("deck.append: unable to append - deck size will be out of range");
	for (int i = 1; i < len + 1; i++) {
		_deck[_top_index + i] = cards[i - 1];
	}
	_top_index += len;
}

void deck::append(const deck& other) {
	if (_top_index + other.size() > size() - 1) throw std::out_of_range("deck.append: unable to append - deck size will be out of range");
	for (int i = 1; i < other.size() + 1; i++) {
		_deck[_top_index + i] = other._deck[i - 1];
	}
	_top_index += other.size();
}

void deck::erase() {
	if (is_empty()) throw std::logic_error("deck.erase: unable to erase - deck is empty");
	_deck[_top_index].set_state(Blank);
	_top_index--;
}

void deck::clear() {
	if (!is_empty()) for (int i = _top_index; i >= 0; i--) erase();
}

void deck::assign(const deck& other, Direction dir) {
	this->resize(other.size());
	if (dir == Forward) {
		for (int i = 0; i < other.size(); i++) this->_deck[i] = other._deck[i];
		this->_top_index = other._top_index;
	}
	else {
		int index = 0;
		for (int i = other.size() - 1; i >= 0; i--) {
			this->_deck[index] = other._deck[i];
			index++;
		}
		this->_top_index = size() - 1;
	}
}

void deck::shrink_to_fit() {
	resize(_top_index + 1);
}

void deck::resize(int new_size) {
	if (new_size <= 0) throw std::invalid_argument("deck.resize: Invalid argument 'new_size' - must be > 0");
	if (size() == new_size) return;
	_deck.resize(new_size);
	if (new_size < size()) _top_index = new_size - 1;
	else {	
		for (int i = size(); i < new_size; i++) _deck.push_back(card("H2B"));
	}
}

int deck::size() const {
	return _deck.size();
}

int deck::top_index() const {
	return _top_index;
}

card& deck::get_top_card() {
	if (is_empty()) throw std::logic_error("deck.get_top_card: unable to get top card - deck is empty");
	return _deck[_top_index];
}

card& deck::get_card(int index) {
	if (index < 0 || index > size() - 1) throw std::invalid_argument("deck.get_card: Invalid argument 'index' - must be >= 0 and < size of deck");
	return _deck[index];
}

void deck::operator=(const deck& other) {
	this->assign(other, Forward);
}

card& deck::operator[](int index) {
	return get_card(index);
}
#include "Field.hpp"

namespace wgp {

	namespace tricky_dungeon {

// =============================================
//  ŒÕ—“–” “Œ–€
// =============================================

		Field::Field() {
			dungeonInit();
			_dungeon.shuffle();
		}

		Field::Field(std::mt19937& gen) {
			dungeonInit();
			_dungeon.shuffle(gen);
		}

// =============================================
// Ã≈“Œƒ Œ“Œ¡–¿∆≈Õ»ﬂ ¬  ŒÕ—ŒÀ‹
// =============================================

		void Field::print() const {
			if (_dungeon.isEmpty()) std::cout << "DG ";
			else std::cout << _dungeon.topIndex() + 1 << " ";
			for (int i = 0; i < 4; i++) {
				_room[i].print();
				std::cout << " ";
			}
			std::cout << "DS" << std::endl;

			_equipedWeapon.print();
			std::cout << " ";
			_slainMonsters.print();
			std::cout << std::endl;
			_dungeon.print(); // “ÓÎ¸ÍÓ ‰Îˇ ÚÂÒÚ‡
			std::cout << std::endl;
			_discard.print(); // “ÓÎ¸ÍÓ ‰Îˇ ÚÂÒÚ‡
			std::cout << std::endl;
		}

// =============================================
// Ã≈“Œƒ€ œ–≈Ã≈Ÿ≈Õ»ﬂ  ¿–“ œŒ œŒÀﬁ (’Œƒ€)
// =============================================

		void Field::openFromDungeonToRoom() {
			for (int i = 0; i < 4; i++) {
				if (_room[i].state() == CardState::Blank && !_dungeon.isEmpty()) {
					_room[i] = _dungeon.getTopCard();
					_room[i].setState(CardState::FaceUp);
					_dungeon.erase();
				}
			}
		}

		void Field::equipWeapon(const CardPosition& source) {
			if (cardRoomIsEmpty(source)) return;

			if (source.getPileType() != PileType::Room) {
				throw std::invalid_argument("scoundrel::Field.equipWeapon: Invalid argument 'source' - pile type must be Room");
			}
			if (getCard(source).suit() != CardSuit::Diamonds) {
				throw std::invalid_argument("scoundrel::Field.equipWeapon: Invalid argument 'source_card' - suit must be Diamonds");
			}
			if (_equipedWeapon.state() != CardState::Blank) {
				discard(equipedWeapon());
				if (!_slainMonsters.isEmpty()) {
					discard(slainMonsters());
				}
			}
			_equipedWeapon = getCard(source);
			getCard(source).setState(CardState::Blank);
		}

		void Field::fightMonster(const CardPosition& source, bool bareHanded) {
			if (cardRoomIsEmpty(source)) return;

			if (source.getPileType() != PileType::Room) {
				throw std::invalid_argument("scoundrel::Field.fightMonster: Invalid argument 'source' - pile type must be Room");
			}
			if (getCard(source).suit() != CardSuit::Clubs && getCard(source).suit() != CardSuit::Spades) {
				throw std::invalid_argument("scoundrel::Field.fightMonster: Invalid argument 'source_card' - suit must be Clubs or Spades");
			}
			if (bareHanded || _equipedWeapon.state() == CardState::Blank) {
				discard(source);
			}
			else {
				if (_slainMonsters.isEmpty() || canFightMonster(source)) {
					_slainMonsters.append(getCard(source));
					getCard(source).setState(CardState::Blank);
				}
			}
		}

		void Field::useHealingPotion(const CardPosition& source) {
			if (cardRoomIsEmpty(source)) return;

			if (source.getPileType() != PileType::Room) {
				throw std::invalid_argument("scoundrel::Field.useHealingPotion: Invalid argument 'source' - pile type must be Room");
			}
			if (getCard(source).suit() != CardSuit::Hearts) {
				throw std::invalid_argument("scoundrel::Field.useHealingPotion: Invalid argument 'source_card' - suit must be Hearts");
			}
			discard(source);
		}

		void Field::skipRoom() {
			if (!roomIsFull()) return;
			Deck tempDungeon = _dungeon;
			_dungeon.clear();
			for (int i = 3; i >= 0; i--) {
				if (_room[i].state() != CardState::Blank) {
					_dungeon.append(_room[i]);
				}
			}
			_dungeon.append(tempDungeon);
			clearRoom();
		}

		void Field::testDiscard() {
			for (int i = 0; i < 4; i++) {
				discard(room(i));
			}
		}

// =============================================
// √≈““≈–€
// =============================================

		bool Field::cardRoomIsEmpty(const CardPosition& source) const {
			if (source.getPileType() != PileType::Room) {
				throw std::invalid_argument("scoundrel::Field.cardRoomIsEmpty: Invalid argument 'source' - pile type must be Room");
			}
			if (getCard(source).state() == CardState::Blank) {
				return true;
			}
			return false;
		}

		bool Field::roomIsEmpty() const {
			for (int i = 0; i < 4; i++) {
				if (_room[i].state() != CardState::Blank) {
					return false;
				}
			}
			return true;
		}

		bool Field::roomIsFull() const {
			for (int i = 0; i < 4; i++) {
				if (_room[i].state() == CardState::Blank) {
					return false;
				}
			}
			return true;
		}

		bool Field::canFightMonster(const CardPosition& source) const {
			if (source.getPileType() != PileType::Room) {
				throw std::invalid_argument("scoundrel::Field.canFightMonster: Invalid argument 'source' - pile type must be Room");
			}
			if (getCard(source).suit() != CardSuit::Clubs && getCard(source).suit() != CardSuit::Spades) {
				throw std::invalid_argument("scoundrel::Field.canFightMonster: Invalid argument 'source_card' - suit must be Clubs or Spades");
			}
			if (static_cast<int>(getCard(source).rank()) < static_cast<int>(_slainMonsters.getTopCard().rank())) {
				return true;
			}
			return false;

		}

		const Deck& Field::getDungeon() const {
			return _dungeon;
		}

		const Deck& Field::getDiscard() const {
			return _discard;
		}

		const Card& Field::getRoomCard(const CardPosition& source) const {
			if (source.getPileType() != PileType::Room) {
				throw std::invalid_argument("scoundrel::Field.getRoomCard: Invalid argument 'source' - pile type must be Room");
			}
			return _room[source.getPileIndex()];
		}

		const Card& Field::getEquipedWeapon() const {
			return _equipedWeapon;
		}

		const Deck& Field::getSlainMonsters() const {
			return _slainMonsters;
		}

		const Deck& Field::getPile(const CardPosition& source) const {
			switch (source.getPileType()) {

			case PileType::Dungeon:
				return _dungeon;

			case PileType::Discard:
				return _discard;

			case PileType::SlainMonsters:
				return _slainMonsters;

			default:
				throw std::invalid_argument("scoundrel::Field.getPile: Invalid argument 'source' - must be entered correctly");
			}
		}

		const Card& Field::getCard(const CardPosition& source) const {
			if (source.getPileType() != PileType::Room && source.getPileType() != PileType::EquippedWeapon) {
				const Deck& pile = getPile(source);
				return pile[source.getCardIndex()];
			}
			else if (source.getPileType() == PileType::Room) {
				return _room[source.getPileIndex()];
			}
			else if (source.getPileType() == PileType::EquippedWeapon) {
				return _equipedWeapon;
			}
			throw std::invalid_argument("scoundrel::Field.getCard: Invalid argument 'source' - must be entered correctly");
		}

// =============================================
// Œ¡Ÿ»… Ã≈“Œƒ »Õ»÷»¿À»«¿÷»» _dungeon
// =============================================

		void Field::dungeonInit() {
			for (int suit = 0; suit < 4; suit++) {
				for (int rank = 2; rank <= 14; rank++) {
					Card card(static_cast<CardSuit>(suit), static_cast<CardRank>(rank), CardState::FaceUp); // œÓ‰ÛÏ‡Ú¸, FaceUp ËÎË FaceDown
					if (!(card.isRed() && (card.isFaceCard() || card.rank() == CardRank::RA))) {
						_dungeon.append(card);
					}
				}
			}
		}

// =============================================
// œ–»¬¿“Õ€≈ Ã≈“Œƒ€ œ≈–≈Ã≈Ÿ≈Õ»ﬂ
// =============================================

		void Field::discard(const CardPosition& source) {
			if (source.getPileType() == PileType::Room || source.getPileType() == PileType::EquippedWeapon) {
				_discard.append(getCard(source));
				getCard(source).setState(CardState::Blank);
			}
			else if (source.getPileType() == PileType::SlainMonsters) {
				_discard.append(_slainMonsters);
				_slainMonsters.clear();
			}
			else {
				throw std::logic_error("scoundrel::Field.discard: Unable to discard 'Dungeon' or 'Discard' piles");
			}
		}

		void Field::clearRoom() {
			for (int i = 0; i < 4; i++) {
				_room[i].setState(CardState::Blank);
			}
		}

// =============================================
// œ–»¬¿“Õ€… √≈““≈–
// =============================================

		Card& Field::getCard(const CardPosition& source) {
			switch (source.getPileType()) {

			case PileType::Dungeon:
				return _dungeon[source.getCardIndex()];

			case PileType::Discard:
				return _discard[source.getCardIndex()];

			case PileType::Room:
				return _room[source.getPileIndex()];

			case PileType::EquippedWeapon:
				return _equipedWeapon;

			case PileType::SlainMonsters:
				return _slainMonsters[source.getCardIndex()];
			default:
				throw std::invalid_argument("scoundrel::Field.getPile: Invalid argument 'source' - must be entered correctly");
			}
		}
	}
}
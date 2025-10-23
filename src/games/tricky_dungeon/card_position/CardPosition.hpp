#pragma once

#include <stdexcept>

namespace wgp {

	namespace tricky_dungeon {

		enum class PileType {
			Empty,
			Dungeon,
			Room,
			Discard,
			EquippedWeapon,
			SlainMonsters
		};

		class CardPosition
		{
			PileType _pileType;
			int _pileIndex;
			int _cardIndex;
		public:
			// === Конструкторы ===
			CardPosition();
			CardPosition(PileType, int, int);
			CardPosition(const CardPosition&);

			// === Сеттер ===
			void setPosition(PileType, int, int);

			// === Методы ===
			void assign(const CardPosition&);
			bool isEqual(const CardPosition&) const;

			// === Геттеры ===
			inline PileType getPileType() const { return _pileType; };
			inline int getPileIndex() const { return _pileIndex; };
			inline int getCardIndex() const { return _cardIndex; };

			// === Перегрузка операторов ===
			void operator=(const CardPosition&);
			bool operator==(const CardPosition&) const;
			bool operator!=(const CardPosition&) const;

		private:
			// === Общий метод валидации полей класса ===
			void positionValidation() const;
		};
	}
}
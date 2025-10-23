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
			// === ������������ ===
			CardPosition();
			CardPosition(PileType, int, int);
			CardPosition(const CardPosition&);

			// === ������ ===
			void setPosition(PileType, int, int);

			// === ������ ===
			void assign(const CardPosition&);
			bool isEqual(const CardPosition&) const;

			// === ������� ===
			inline PileType getPileType() const { return _pileType; };
			inline int getPileIndex() const { return _pileIndex; };
			inline int getCardIndex() const { return _cardIndex; };

			// === ���������� ���������� ===
			void operator=(const CardPosition&);
			bool operator==(const CardPosition&) const;
			bool operator!=(const CardPosition&) const;

		private:
			// === ����� ����� ��������� ����� ������ ===
			void positionValidation() const;
		};
	}
}
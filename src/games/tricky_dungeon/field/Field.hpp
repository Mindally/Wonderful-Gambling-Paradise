#pragma once

#include "../../../core/model/card/Card.hpp"
#include "../../../core/model/deck/Deck.hpp"

#include "../card_position/CardPosition.hpp"
#include "../card_position/CardPositionPresets.hpp"

#include "../../../core/TVector/TVector.h"

#include <iostream>

namespace wgp {

	namespace tricky_dungeon {

		class Field {
			Deck _dungeon{ 44 };
			Deck _discard{ 44 };
			Card _room[4];
			Card _equipedWeapon;
			Deck _slainMonsters{ 13 };
		public:
			// === ������������ ===
			Field();
			Field(std::mt19937&);

			// === ����� ����������� � ������� ===
			void print() const;

			// === ������ ����������� ���� �� ���� (����) ===
			void openFromDungeonToRoom();
			void skipRoom();
			void fightMonster(const CardPosition&, bool); // bool �������� �� ��� ��� ������
			void equipWeapon(const CardPosition&);
			void useHealingPotion(const CardPosition&);

			void testDiscard(); // ��� �����

			// === ������� ===
			bool cardRoomIsEmpty(const CardPosition&) const;
			bool roomIsEmpty() const;
			bool roomIsFull() const;

			bool canFightMonster(const CardPosition&) const;

			const Deck& getDungeon() const;
			const Deck& getDiscard() const;
			const Card& getRoomCard(const CardPosition&) const;
			const Card& getEquipedWeapon() const;
			const Deck& getSlainMonsters() const;

			const Deck& getPile(const CardPosition&) const;
			const Card& getCard(const CardPosition&) const;


		private:
			// === ����� ����� ������������ _dungeon ===
			void dungeonInit();

			// === ��������� ������ ����������� === 
			void discard(const CardPosition&);
			void clearRoom();

			// === ��������� ������ ===
			Card& getCard(const CardPosition&);
		};
	}
}
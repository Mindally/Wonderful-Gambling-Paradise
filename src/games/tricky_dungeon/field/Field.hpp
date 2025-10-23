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
			// === Конструкторы ===
			Field();
			Field(std::mt19937&);

			// === Метод отображения в консоль ===
			void print() const;

			// === Медоты перемещения карт по полю (ходы) ===
			void openFromDungeonToRoom();
			void skipRoom();
			void fightMonster(const CardPosition&, bool); // bool отвечает за бой без оружия
			void equipWeapon(const CardPosition&);
			void useHealingPotion(const CardPosition&);

			void testDiscard(); // для теста

			// === Геттеры ===
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
			// === Общий метод инциализации _dungeon ===
			void dungeonInit();

			// === Приватные методы перемещения === 
			void discard(const CardPosition&);
			void clearRoom();

			// === Приватный геттер ===
			Card& getCard(const CardPosition&);
		};
	}
}
#pragma once

#include "CardPosition.hpp"

namespace wgp {

	namespace tricky_dungeon {

		inline CardPosition dungeon(int cardIndex = 0) {
			return CardPosition(PileType::Dungeon, 0, cardIndex);
		}

		inline CardPosition room(int pileIndex = 0) {
			return CardPosition(PileType::Room, pileIndex, 0);
		}

		inline CardPosition discard(int cardIndex = 0) {
			return CardPosition(PileType::Discard, 0, cardIndex);
		}

		inline CardPosition equipedWeapon() {
			return CardPosition(PileType::EquippedWeapon, 0, 0);
		}

		inline CardPosition slainMonsters(int cardIndex = 0) {
			return CardPosition(PileType::SlainMonsters, 0, cardIndex);
		}
	}
}
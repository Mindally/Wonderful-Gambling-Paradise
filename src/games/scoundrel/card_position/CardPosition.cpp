#include "CardPosition.hpp"

namespace wgp {

	namespace scoundrel {

// =============================================
//  ŒÕ—“–” “Œ–€
// =============================================

		CardPosition::CardPosition() :
			_pileType(PileType::Empty),
			_pileIndex(0),
			_cardIndex(0)
		{}

		CardPosition::CardPosition(PileType pileType, int pileIndex, int cardIndex) :
			_pileType(pileType),
			_pileIndex(pileIndex),
			_cardIndex(cardIndex)
		{
			positionValidation();
		}

		CardPosition::CardPosition(const CardPosition& other) :
			_pileType(other._pileType),
			_pileIndex(other._pileIndex),
			_cardIndex(other._cardIndex)
		{}

// =============================================
// —≈““≈–
// =============================================		

		void CardPosition::setPosition(PileType pileType, int pileIndex, int cardIndex) {
			_pileType = pileType;
			_pileIndex = pileIndex;
			_cardIndex = cardIndex;

			positionValidation();
		}

// =============================================
// Ã≈“Œƒ€
// =============================================

		void CardPosition::assign(const CardPosition& other) {
			_pileType = other._pileType;
			_pileIndex = other._pileIndex;
			_cardIndex = other._cardIndex;
		}

		bool CardPosition::isEqual(const CardPosition& other) const {
			if (_pileType == other._pileType &&
				_pileIndex == other._pileIndex &&
				_cardIndex == other._cardIndex)
			{
				return true;
			}
			return false;
		}

// =============================================
// œ≈–≈√–”« ¿ Œœ≈–¿“Œ–Œ¬
// =============================================

		void CardPosition::operator=(const CardPosition& other) {
			(this->assign(other));
		}

		bool CardPosition::operator==(const CardPosition& other) const {
			return this->isEqual(other);
		}

		bool CardPosition::operator!=(const CardPosition& other) const {
			return !(*this == other);
		}

// =============================================
// Œ¡Ÿ»… Ã≈“Œƒ ¬¿À»ƒ¿÷»» œŒÀ≈…  À¿——¿
// =============================================

		void CardPosition::positionValidation() const {
			if (_pileIndex < 0) {
				throw std::invalid_argument("scoundrel::CardPosition.positionValidation: Invalid argument '_pileIndex - must be >= 0");
			}
			if (_cardIndex < 0) {
				throw std::invalid_argument("scoundrel::CardPosition.positionValidation: Invalid argument '_cardIndex - must be >= 0");
			}

			switch (_pileType) {

			case PileType::Dungeon:
			case PileType::Discard:
				if (_pileIndex != 0) {
					throw std::invalid_argument("scoundrel::CardPosition.PositionValidator: Invalid argument '_pileIndex' (Dungeon/Discard) - must be 0");
				}
				if (_cardIndex > 43) {
					throw std::invalid_argument("scoundrel::CardPosition.positionValidation: Invalid argument '_cardIndex (Dungeon/Discard) - must be <= 43");
				}
				break;

			case PileType::Room:
				if (_pileIndex > 3) {
					throw std::invalid_argument("scoundrel::CardPosition.PositionValidator: Invalid argument '_pileIndex' (Room) - must be <= 3");
				}
				if (_cardIndex != 0) {
					throw std::invalid_argument("scoundrel::CardPosition.positionValidation: Invalid argument '_cardIndex (Room) - must be 0");
				}
				break;

			case PileType::EquippedWeapon:
				if (_pileIndex != 0) {
					throw std::invalid_argument("scoundrel::CardPosition.PositionValidator: Invalid argument '_pileIndex' (EquippedWeapon) - must be 0");
				}
				if (_cardIndex != 0) {
					throw std::invalid_argument("scoundrel::CardPosition.positionValidation: Invalid argument '_cardIndex (EquippedWeapon) - must be 0");
				}
				break;

			case PileType::SlainMonsters:
				if (_pileIndex != 0) {
					throw std::invalid_argument("scoundrel::CardPosition.PositionValidator: Invalid argument '_pileIndex' (SlainMonsters) - must be 0");
				}
				if (_cardIndex > 12) {
					throw std::invalid_argument("scoundrel::CardPosition.positionValidation: Invalid argument '_cardIndex (SlainMonsters) - must be <= 12");
				}
				break;

			default:
				throw std::invalid_argument("scoundrel::CardPosition.positionValidation: Invalid argument '_pileType'");
			}
		}
	}
}
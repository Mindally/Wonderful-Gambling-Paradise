#include "CardPosition.hpp"

namespace wgp {

	namespace solitaire {

// =============================================
// ������������
// =============================================

		CardPosition::CardPosition() :
			_gameType(SolitaireType::NotDefined),
			_pileType(PileType::Empty),
			_pileIndex(0),
			_cardIndex(0)
		{}

		CardPosition::CardPosition(SolitaireType gameType, PileType pileType, int pileIndex, int cardIndex) :
			_gameType(gameType),
			_pileType(pileType),
			_pileIndex(pileIndex),
			_cardIndex(cardIndex)
		{
			positionValidation();
		}

		CardPosition::CardPosition(const CardPosition& other) :
			_gameType(other._gameType),
			_pileType(other._pileType),
			_pileIndex(other._pileIndex),
			_cardIndex(other._cardIndex)
		{}

// =============================================
// ����� ����� ������������� ������
// =============================================

		void CardPosition::initialize(SolitaireType gameType, PileType pileType, int pileIndex, int cardIndex) {
			_gameType = gameType;
			_pileType = pileType;
			_pileIndex = pileIndex;
			_cardIndex = cardIndex;

			positionValidation();
		}

// =============================================
// ������
// =============================================		

		void CardPosition::setPosition(PileType pileType, int pileIndex, int cardIndex) {
			_pileType = pileType;
			_pileIndex = pileIndex;
			_cardIndex = cardIndex;

			positionValidation();
		}

// =============================================
// ������
// =============================================

		void CardPosition::assign(const CardPosition& other) {
			_gameType = other._gameType;
			_pileType = other._pileType;
			_pileIndex = other._pileIndex;
			_cardIndex = other._cardIndex;
		}

		bool CardPosition::isEqual(const CardPosition& other) const {
			if (_gameType == other._gameType &&
				_pileType == other._pileType &&
				_pileIndex == other._pileIndex &&
				_cardIndex == other._cardIndex)
			{
				return true;
			}
			return false;
		}

// =============================================
// ���������� ����������
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
// ����� ����� ��������� ����� ������
// =============================================

		void CardPosition::basicFieldsValidation() const {
			if (_pileIndex < 0) {
				throw std::invalid_argument("solitaire::CardPosition.basicFieldsValidation: Invalid argument '_pileIndex - must be >= 0");
			}
			if (_cardIndex < 0) {
				throw std::invalid_argument("solitaire::CardPosition.basicFieldsValidation: Invalid argument '_cardIndex - must be >= 0");
			}
		}

		void CardPosition::positionValidation() const {
			basicFieldsValidation();
			switch (_gameType) {

			case SolitaireType::Klondike:
				klondikePositionValidation();
				break;
				// ������ ��������

			default:
				throw std::invalid_argument("solitaire::CardPosition.positionValidation: Invalid argument '_gameType'");
			}
		}

// =============================================
// ��������� ����� ������ �� ��������� ���� ��������
// =============================================

		void CardPosition::klondikePositionValidation() const {
			switch (_pileType) {

			case PileType::Foundation:
				if (_pileIndex > 3) {
					throw std::invalid_argument("solitaire::CardPosition.klondikePositionValidator: Invalid argument '_pileIndex' (Foundation) - must be <= 3");
				}
				if (_cardIndex > 12) {
					throw std::invalid_argument("solitaire::CardPosition.klondikePositionValidator: Invalid argument '_cardIndex' (Tableau) - must be <= 12");
				}
				break;

			case PileType::Tableau:
				if (_pileIndex > 6) {
					throw std::invalid_argument("solitaire::CardPosition.klondikePositionValidator: Invalid argument '_pileIndex' (Tableau) - must be <= 6");
				}
				if (_cardIndex > 18) {
					throw std::invalid_argument("solitaire::CardPosition.klondikePositionValidator: Invalid argument '_cardIndex' (Tableau) - must be <= 18");
				}
				break;

			case PileType::Stock:
			case PileType::Waste:
				if (_pileIndex != 0) {
					throw std::invalid_argument("solitaire::CardPosition.klondikePositionValidator: Invalid argument '_pileIndex' (Stock/Waste) - must be 0");
				}
				if (_cardIndex > 23) {
					throw std::invalid_argument("solitaire::CardPosition.klondikePositionValidator: Invalid argument '_cardIndex' (Stock/Waste) - must be <= 23");
				}
				break;

			default:
				throw std::invalid_argument("solitaire::CardPosition.klondikePositionValidator: Invalid argument '_pileIndex' for klondike");
			}
		}
	}
}
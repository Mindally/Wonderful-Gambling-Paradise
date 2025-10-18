#pragma once

#include <stdexcept>

namespace wgp {

	namespace solitaire {

		enum class SolitaireType {
			NotDefined,
			Klondike
			// ���� ��������� �� ���� �������������
		};

		enum class PileType {
			Empty,
			Foundation,
			Tableau,
			Stock,
			Waste
			// ���� ��������� �� ���� �������������
		};

		class CardPosition
		{
			SolitaireType _gameType;
			PileType _pileType;
			int _pileIndex;
			int _cardIndex;
		public:
			// === ������������ ===
			CardPosition();
			CardPosition(SolitaireType, PileType, int, int);
			CardPosition(const CardPosition&);

			// === ����� ����� ������������� ������ ===
			void initialize(SolitaireType, PileType, int, int);

			// === ������ ===
			void setPosition(PileType, int, int);

			// === ������ ===
			void assign(const CardPosition&);
			bool isEqual(const CardPosition&) const;

			// === ������� ===
			inline SolitaireType getSolitaireType() const { return _gameType; };
			inline PileType getPileType() const { return _pileType; };
			inline int getPileIndex() const { return _pileIndex; };
			inline int getCardIndex() const { return _cardIndex; };

			// === ���������� ���������� ===
			void operator=(const CardPosition&);
			bool operator==(const CardPosition&) const;
			bool operator!=(const CardPosition&) const;

		private:
			// === ����� ����� ��������� ����� ������ (������������ ��������� ������� ���������) ===
			void basicFieldsValidation() const;
			void positionValidation() const;

			// === ��������� ����� ������ �� ��������� ���� �������� ===
			void klondikePositionValidation() const;
		};
	}
}
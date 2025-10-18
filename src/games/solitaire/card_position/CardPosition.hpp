#pragma once

#include <stdexcept>

namespace wgp {

	namespace solitaire {

		enum class SolitaireType {
			NotDefined,
			Klondike
			// Буду добавлять по мере необходимости
		};

		enum class PileType {
			Empty,
			Foundation,
			Tableau,
			Stock,
			Waste
			// Буду добавлять по мере необходимости
		};

		class CardPosition
		{
			SolitaireType _gameType;
			PileType _pileType;
			int _pileIndex;
			int _cardIndex;
		public:
			// === Конструкторы ===
			CardPosition();
			CardPosition(SolitaireType, PileType, int, int);
			CardPosition(const CardPosition&);

			// === Общий метод инициализации класса ===
			void initialize(SolitaireType, PileType, int, int);

			// === Сеттер ===
			void setPosition(PileType, int, int);

			// === Методы ===
			void assign(const CardPosition&);
			bool isEqual(const CardPosition&) const;

			// === Геттеры ===
			inline SolitaireType getSolitaireType() const { return _gameType; };
			inline PileType getPileType() const { return _pileType; };
			inline int getPileIndex() const { return _pileIndex; };
			inline int getCardIndex() const { return _cardIndex; };

			// === Перегрузка операторов ===
			void operator=(const CardPosition&);
			bool operator==(const CardPosition&) const;
			bool operator!=(const CardPosition&) const;

		private:
			// === Общий метод валидации полей класса (совокупность отдельных функций валидации) ===
			void basicFieldsValidation() const;
			void positionValidation() const;

			// === Валидация полей класса на основании типа Пасьянса ===
			void klondikePositionValidation() const;
		};
	}
}
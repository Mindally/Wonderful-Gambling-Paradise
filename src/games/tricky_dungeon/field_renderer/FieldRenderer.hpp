#pragma once

#include "../../../core/model/card/Card.hpp"
#include "../../../core/model/deck/Deck.hpp"

#include "../../../core/view/card_renderer/CardRenderer.hpp"
#include "../../../core/view/deck_renderer/DeckRenderer.hpp"

#include "../card_position/CardPosition.hpp"
#include "../card_position/CardPositionPresets.hpp"
#include "../field/Field.hpp"

#include "../../../core/TVector/TVector.h"

namespace wgp {

	namespace tricky_dungeon {

		class FieldRenderer {
			Field* _field;
			sf::Texture* _cardAtlas;
			sf::Texture* _scoundrelAtlas;
			const sf::Font _font;
			float _cardsScale;

			sf::Sprite _dungeonRender;
			sf::Sprite _discardRender;
			TVector<CardRenderer> _roomRender{ 4 };
			CardRenderer _equippedWeaponRender;
			DeckRenderer _slainMonstersRender;
			sf::Text _remainingCardsInDungeon{ _font };

			sf::Sprite _emptyDiscard;
			sf::Sprite _emptyRoomPiles[4] = { sf::Sprite(*_scoundrelAtlas), sf::Sprite(*_scoundrelAtlas), sf::Sprite(*_scoundrelAtlas), sf::Sprite(*_scoundrelAtlas) };

			float _cardsSpacing;
			float _columnSpacing;
			float _rowSpacing;
			float _DungeonAndDiscardSpacing;
			sf::Vector2f _startPosition;

			bool _isRendering;

		public:
			// === Конструктор ===
			FieldRenderer(sf::Texture&, sf::Texture&, Field*, const sf::Font&, float, float, float, float, float, sf::Vector2f);

			// === Сеттеры ===
			void setField(Field*);
			void setCardAtlas(sf::Texture&);
			void setScoundrelAtlas(sf::Texture&);
			void setScale(float);
			void setCardsSpacing(float);
			void setColumnSpacing(float);
			void setRowSpacing(float);
			void setDungeonAndDiscardSpacing(float);
			void setStartPosition(sf::Vector2f);
			void setRendering(bool);

			// === Геттеры ===
			inline float getScale() const { return _cardsScale; };
			inline float getCardsSpacing() const { return _cardsSpacing; };
			inline float getColumnSpacing() const { return _columnSpacing; };
			inline float getRowSpacing() const { return _rowSpacing; };
			inline float getDungeonAndDiscardSpacing() const { return _DungeonAndDiscardSpacing; };
			inline sf::Vector2f getStartPosition() const { return _startPosition; };
			//inline sf::Vector2f getEndPosition() const { return _tableauPilesRenders[6].getCardRender((*_field).getTableauPile(6).topIndex()).getPosition(); };
			inline bool isRendering() const { return _isRendering; };

			// === Методы отрисовки ===
			void draw(sf::RenderTarget&);
			void update();

		private:
			// === Инициализация спрайтов отрисовки ===
			void dungeonSpriteInit();
			void discardSpriteInit();
			void emptyDiscardSpriteInit();
			void emptyRoomCardSpritesInit();

			// === Инициализация текста отрисовки ===
			void dungeonTextInit();
			void dungeonCardsSetText();
		};

		// === Прочие функции ===
		sf::IntRect coordsToIntRectScoundrelAtlas(unsigned int);
		sf::Vector2f getLocalCentreOfText(sf::Text&);
		sf::Vector2f getGlobalCentreOfText(sf::Text&);
	}
}
#pragma once

#include "../../../../core/model/card/Card.hpp"
#include "../../../../core/model/deck/Deck.hpp"
#include "../field/Field.hpp"
#include "../../../../core/view/card_renderer/CardRenderer.hpp"
#include "../../../../core/view/deck_renderer/DeckRenderer.hpp"
#include "../../../../core//TVector/TVector.h"
#include <iostream>

namespace wgp {

	namespace klondike {

		class FieldRenderer
		{
			Field* _field;
			sf::Texture* _cardAtlas;
			sf::Texture* _klondikeAtlas;
			const sf::Font _font;
			float _cardsScale;

			TVector<DeckRenderer> _tableauPilesRenders{ 7 };
			TVector<DeckRenderer> _foundationPilesRenders{ 4 };
			sf::Sprite _stockPileRender;
			sf::Text _remainingCardsInStock{ _font };
			DeckRenderer _wastePileRender;

			sf::Sprite _emptyWastePile;
			sf::Sprite _emptyFoundationPiles[4] = { sf::Sprite(*_klondikeAtlas), sf::Sprite(*_klondikeAtlas), sf::Sprite(*_klondikeAtlas), sf::Sprite(*_klondikeAtlas) };

			float _cardsSpacing;
			float _columnSpacing;
			float _rowSpacing;
			sf::Vector2f _startPosition;

			bool _isRendering;

			bool _isStockSpriteNeedsChange = false;
		public:
			// === Конструктор ===
			FieldRenderer(sf::Texture&, sf::Texture&, Field*, const sf::Font&, float, float, float, float, sf::Vector2f);

			// === Сеттеры ===
			void setField(Field*);
			void setCardAtlas(sf::Texture&);
			void setKlondikeAtlas(sf::Texture&);
			void setScale(float);
			void setCardsSpacing(float);
			void setColumnSpacing(float);
			void setRowSpacing(float);
			void setStartPosition(sf::Vector2f);
			void setRendering(bool);

			// === Геттеры ===
			inline float getScale() const { return _cardsScale; };
			inline float getCardsSpacing() const { return _cardsSpacing; };
			inline float getColumnSpacing() const { return _columnSpacing; };
			inline float getRowSpacing() const { return _rowSpacing; };
			inline sf::Vector2f getStartPosition() const { return _startPosition; };
			inline sf::Vector2f getEndPosition() const { return _tableauPilesRenders[6].getCardRender((*_field).getTableauPile(6).topIndex()).getPosition(); };
			inline bool isRendering() const { return _isRendering; };

			// === Методы отрисовки ===
			void draw(sf::RenderTarget&);
			void update();

		private:
			// === Инициализация спрайтов отрисовки ===
			void stockPileSpriteInit();
			void emptyWastePileSpriteInit();
			void emptyFoundationPilesSpritesInit();

			// === Инициализация текста отрисовки ===
			void remainingCardsTextInit();
			void remainingCardsSetText();

			// === Проверка состояния для stockPile и wastePile ===
			void updateStockSprite();
		};

		// === Прочие функции ===
		sf::IntRect coordsToIntRectKlondikeAtlas(unsigned int);
		sf::Vector2f getLocalCentreOfText(sf::Text&);
		sf::Vector2f getGlobalCentreOfText(sf::Text&);
	}
}
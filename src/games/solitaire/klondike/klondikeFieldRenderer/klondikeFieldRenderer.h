#include "../../../../core/fundamental classes/logic/card/card.h"
#include "../../../../core/fundamental classes/logic/deck/deck.h"
#include "../klondikeField/klondikeField.h"
#include "../../../../core/fundamental classes/render/cardRenderer/cardRenderer.h"
#include "../../../../core/fundamental classes/render/deckRenderer/deckRenderer.h"
#include "../../../../core/fundamental classes/TVector/TVector.h"
#include <iostream>

#pragma once

namespace WGP {
	class klondikeFieldRenderer
	{
		klondikeField* _klondikeField;
		sf::Texture* _cardAtlas;
		sf::Texture* _klondikeAtlas;
		const sf::Font _font;
		float _cardsScale;

		TVector<deckRenderer> _tableauPilesRenders{ 7 };
		TVector<deckRenderer> _foundationPilesRenders{ 4 };
		sf::Sprite _stockPileRender;
		sf::Text _remainingCardsInStock{ _font };
		deckRenderer _wastePileRender;

		sf::Sprite _emptyWastePile;
		sf::Sprite _emptyFoundationPiles[4] = { sf::Sprite(*_klondikeAtlas), sf::Sprite(*_klondikeAtlas), sf::Sprite(*_klondikeAtlas), sf::Sprite(*_klondikeAtlas) };

		float _cardsSpacing;
		float _columnSpacing;
		float _rowSpacing;
		sf::Vector2f _startPosition;

		bool _isRendering;
	public:
		// Constructors
		klondikeFieldRenderer(sf::Texture&, sf::Texture&, klondikeField*, const sf::Font&, float, float, float, float, sf::Vector2f);

		// Setters
		void setKlondikeField(klondikeField*);
		void setCardAtlas(sf::Texture&);
		void setKlondikeAtlas(sf::Texture&);
		void setScale(float);
		void setCardsSpacing(float);
		void setColumnSpacing(float);
		void setRowSpacing(float);
		void setStartPosition(sf::Vector2f);
		void setRendering(bool);

		// Functions
		void draw(sf::RenderTarget&);
		void update();

		// Getters
		float getScale() const;
		float getCardsSpacing() const;
		float getColumnSpacing() const;
		float getRowSpacing() const;
		sf::Vector2f getStartPosition() const;
		bool isRendering() const;
	private:
		void stockPileSpriteInit();
		void emptyWastePileSpriteInit();
		void emptyFoundationPilesSpritesInit();
		void remainingCardsTextInit();
		void remainingCardsSetText();
	};

	sf::IntRect coordsToIntRectKlondikeAtlas(unsigned int);
	sf::Vector2f getLocalCentreOfText(sf::Text&);
	sf::Vector2f getGlobalCentreOfText(sf::Text&);
}
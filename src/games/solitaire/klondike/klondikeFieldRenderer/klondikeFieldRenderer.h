#include "../../../../core/fundamental classes/logic/card/card.h"
#include "../../../../core/fundamental classes/logic/deck/deck.h"
#include "../klondikeField/klondikeField.h"
#include "../../../../core/fundamental classes/render/cardRenderer/cardRenderer.h"
#include "../../../../core/fundamental classes/render/deckRenderer/deckRenderer.h"
#include "../../../../core/fundamental classes/TVector/TVector.h"
#include "../../../../main/constants.h"
#include <iostream>

#pragma once

namespace WGP {
	class klondikeFieldRenderer
	{
		klondikeField* _klondikeField;
		sf::Texture* _cardAtlas;
		sf::Texture* _klondikeAtlas;
		float _cardsScale;

		TVector<deckRenderer> _tableauPilesRenders{ 7 }; // 7
		TVector<deckRenderer> _foundationPilesRenders{ 4 }; // 4
		deckRenderer _stockPileRender;
		deckRenderer _wastePileRender;

		float _cardsSpacing;
		float _columnSpacing;
		float _rowSpacing;
		sf::Vector2f _startPosition;

		bool _isRendering;
	public:
		// Constructors
		klondikeFieldRenderer();
		klondikeFieldRenderer(sf::Texture&, sf::Texture&, klondikeField*, float, float, float, float, sf::Vector2f);

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
	};
}
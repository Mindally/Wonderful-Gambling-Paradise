#include <SFML/Graphics.hpp>
#include <cmath>
#define PI 3.14159265358979323846

#include "../../logic/card/card.h"
#include "../cardRenderer/cardRenderer.h"
#include "../../logic/deck/deck.h"
#include "../../TVector/TVector.h"

#pragma once

namespace WGP {
	class deckRenderer
	{
		sf::Texture* _cardAtlas;
		sf::Angle _deckRotation;
		sf::Vector2f _deckScale;

		deck* _deck;
		TVector<cardRenderer> _cardRenders;
		sf::Angle _angle;
		sf::Vector2f _startPos, _endPos;
		float _spacing;
		bool _isRendering;

	public:
		// Constructors
		deckRenderer();
		deckRenderer(sf::Texture&, deck*, sf::Vector2f);
		deckRenderer(sf::Texture&, deck*, sf::Vector2f, sf::Angle, float);
		deckRenderer(sf::Texture&, deck*, sf::Vector2f, sf::Vector2f);

		// Setters
		void setCardAtlas(sf::Texture&);
		void setDeck(deck*);
		void setAngle(sf::Angle);
		void setStartPosition(sf::Vector2f);
		void setEndPosition(sf::Vector2f);
		void setPosition(sf::Vector2f, sf::Vector2f);
		void setSpacing(float);
		void setRendering(bool);

		// Visualization functions
		void draw(sf::RenderTarget&);
		void update();

		// Actions with cards
		void setCardsScale(float);
		void setCardsRotation(sf::Angle);

		// Getters
		sf::Angle getAngle() const;
		sf::Vector2f getStartPosition() const;
		sf::Vector2f getEndPosition() const;
		float getSpacing() const;
		bool isRendering() const;
		sf::Angle getCardsRotation() const;
		sf::Vector2f getCardsScale() const;
	};

	float calculateAngle(sf::Vector2f, sf::Vector2f);
	float calculateLength(sf::Vector2f, sf::Vector2f);

	TVector<sf::Vector2f> getCoordinatesVectorFromAngle(int, sf::Vector2f, sf::Angle, float);
	TVector<sf::Vector2f> getCoordinatesVectorFromPosition(int, sf::Vector2f, sf::Vector2f);
}
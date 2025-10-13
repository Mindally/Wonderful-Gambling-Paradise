#include <SFML/Graphics.hpp>
#include "../../logic/card/card.h"

#define CARD_SPRITE_HEIGHT 96
#define CARD_SPRITE_WIDTH 70
#define CARD_ATLAS_SPACING 1
#define OUT_OF_BOUNDS -1000

#pragma once

namespace WGP {
	class cardRenderer
	{
		sf::Texture _cardPlaceholder;

		sf::Sprite _material;
		sf::Sprite _frontImage;
		const card* _card;
		bool _isRendering;
	public:
		cardRenderer();
		cardRenderer(sf::Texture&, const card*);
		cardRenderer(sf::Texture&, const card*, sf::Vector2f, sf::Angle, sf::Vector2f);
		cardRenderer(sf::Texture&, const card*, float, sf::Angle, sf::Vector2f);
		cardRenderer(const cardRenderer&);

		void initialize(sf::Texture&, const card*, float, sf::Vector2f, sf::Angle);
		void setCardAtlas(sf::Texture&);
		void setCard(const card*);
		void setScale(sf::Vector2f);
		void setScale(float);
		void setPosition(sf::Vector2f);
		void move(sf::Vector2f);
		void setRotation(sf::Angle);
		void setOrigin(sf::Vector2f);
		void setColor(sf::Color);
		void resetColor();

		sf::Vector2f getScale() const;
		bool isRendering() const;
		sf::Vector2f getPosition() const;
		sf::FloatRect getLocalBounds() const;
		sf::FloatRect getGlobalBounds() const;
		sf::Angle getRotation() const;

		void draw(sf::RenderTarget&);
		void update();
		void assign(const cardRenderer&);
	private:
		void setOriginToLocalCentre();
		void setOriginToGlobalCentre();
	};
	
	sf::Vector2f getLocalCentreOfSprite(sf::Sprite&);
	sf::Vector2f getGlobalCentreOfSprite(sf::Sprite&);
	sf::IntRect coordsToIntRectCardAtlas(sf::Vector2u);
	sf::IntRect cardToIntRectCardAtlas(const card);
}
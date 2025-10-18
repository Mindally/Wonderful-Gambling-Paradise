#pragma once

#include <SFML/Graphics.hpp>
#include "../../model/card/Card.hpp"

// ���������� ������� ������� ����� �����
#define CARD_SPRITE_HEIGHT 96
#define CARD_SPRITE_WIDTH 70

// ���������� ������� ����� ��������� ����� � ������
#define CARD_ATLAS_SPACING 1

// ����������, ����� ����� ������� �����, ������� ��������� �� �������� ���������
#define OUT_OF_BOUNDS -1000

namespace wgp {

	class CardRenderer
	{
		sf::Texture _cardPlaceholder;

		sf::Sprite _material;
		sf::Sprite _frontImage;
		const Card* _card;
		bool _isRendering;
	public:
		// === ������������ ===
		CardRenderer();
		CardRenderer(sf::Texture&, const Card*);
		CardRenderer(sf::Texture&, const Card*, sf::Vector2f, sf::Angle, sf::Vector2f);
		CardRenderer(sf::Texture&, const Card*, float, sf::Angle, sf::Vector2f);
		CardRenderer(const CardRenderer&);

		// === ����� ����� ������������� ������ ===
		void initialize(sf::Texture&, const Card*, float, sf::Vector2f, sf::Angle);

		// === ������� ===
		void setCardAtlas(sf::Texture&);
		void setCard(const Card*);
		void setScale(sf::Vector2f);
		void setScale(float);
		void setPosition(sf::Vector2f);
		void move(sf::Vector2f);
		void setRotation(sf::Angle);
		void setOrigin(sf::Vector2f);
		void setColor(sf::Color);
		void resetColor();

		// === ������� ===
		inline sf::Vector2f getScale() const { return _material.getScale(); };
		inline bool isRendering() const { return _isRendering; };
		inline sf::Vector2f getPosition() const { return _material.getPosition(); };
		inline sf::FloatRect getLocalBounds() const { return _material.getLocalBounds(); };
		inline sf::FloatRect getGlobalBounds() const { return _material.getGlobalBounds(); };
		inline sf::Angle getRotation() const { return _material.getRotation(); };

		// === ������ ��������� ===
		void draw(sf::RenderTarget&);
		void update();

		// === ������ ������ ===
		void assign(const CardRenderer&);

		// === ���������� ���������� ===
		void operator=(const CardRenderer&);

	private:
		// === ������, ����� ��������� origin �������� ���� � �� ����� ===
		void setOriginToLocalCentre();
		void setOriginToGlobalCentre();
	};
	
	// === ������� ����������� ������ sf::Sprite ===
	sf::Vector2f getLocalCentreOfSprite(sf::Sprite&);
	sf::Vector2f getGlobalCentreOfSprite(sf::Sprite&);

	// === �������������� ������� ��������� ��������� ��� ����� � sf::IntRect ===
	sf::IntRect coordsToIntRectCardAtlas(sf::Vector2u);
	sf::IntRect cardToIntRectCardAtlas(const Card&);
}
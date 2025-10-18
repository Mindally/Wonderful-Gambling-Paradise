#pragma once

#include <SFML/Graphics.hpp>
#include "../../model/card/Card.hpp"

// Определяем размеры спрайта одной карты
#define CARD_SPRITE_HEIGHT 96
#define CARD_SPRITE_WIDTH 70

// Определяем отступы между спрайтами карты в атласе
#define CARD_ATLAS_SPACING 1

// Определяем, какой будет позиция карты, которая находится за областью видимости
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
		// === Конструкторы ===
		CardRenderer();
		CardRenderer(sf::Texture&, const Card*);
		CardRenderer(sf::Texture&, const Card*, sf::Vector2f, sf::Angle, sf::Vector2f);
		CardRenderer(sf::Texture&, const Card*, float, sf::Angle, sf::Vector2f);
		CardRenderer(const CardRenderer&);

		// === Общий метод инициализации класса ===
		void initialize(sf::Texture&, const Card*, float, sf::Vector2f, sf::Angle);

		// === Сеттеры ===
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

		// === Геттеры ===
		inline sf::Vector2f getScale() const { return _material.getScale(); };
		inline bool isRendering() const { return _isRendering; };
		inline sf::Vector2f getPosition() const { return _material.getPosition(); };
		inline sf::FloatRect getLocalBounds() const { return _material.getLocalBounds(); };
		inline sf::FloatRect getGlobalBounds() const { return _material.getGlobalBounds(); };
		inline sf::Angle getRotation() const { return _material.getRotation(); };

		// === Методы отрисовки ===
		void draw(sf::RenderTarget&);
		void update();

		// === Прочие методы ===
		void assign(const CardRenderer&);

		// === Перегрузка операторов ===
		void operator=(const CardRenderer&);

	private:
		// === Сеттры, чтобы назначить origin спрайтов карт в их центр ===
		void setOriginToLocalCentre();
		void setOriginToGlobalCentre();
	};
	
	// === Функции определения центра sf::Sprite ===
	sf::Vector2f getLocalCentreOfSprite(sf::Sprite&);
	sf::Vector2f getGlobalCentreOfSprite(sf::Sprite&);

	// === Дополнительные функции пересчёта координат или карты в sf::IntRect ===
	sf::IntRect coordsToIntRectCardAtlas(sf::Vector2u);
	sf::IntRect cardToIntRectCardAtlas(const Card&);
}
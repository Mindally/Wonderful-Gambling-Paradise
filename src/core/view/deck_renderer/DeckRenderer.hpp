#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>
#include "../../model/card/Card.hpp"
#include "../card_renderer/CardRenderer.hpp"
#include "../../model/deck/Deck.hpp"
#include "../../TVector/TVector.h"

#define PI 3.14159265358979323846


namespace wgp {

	enum class DeckStyle {FromPosition, FromAngleSpacing};

	class DeckRenderer
	{
		sf::Texture* _cardAtlas;
		sf::Angle _deckRotation;
		sf::Vector2f _deckScale;

		const Deck* _deck;
		TVector<CardRenderer> _cardRenders;
		sf::Angle _angle;
		sf::Vector2f _startPos, _endPos;
		float _spacing;
		bool _isRendering;
		DeckStyle _deckStyle;

	public:
		// === ������������ ===
		DeckRenderer();
		DeckRenderer(sf::Texture&, const Deck*, sf::Vector2f);
		DeckRenderer(sf::Texture&, const Deck*, sf::Vector2f, sf::Angle, float);
		DeckRenderer(sf::Texture&, const Deck*, sf::Vector2f, sf::Vector2f);

		// === ����� ������ ������������� ������ ===
		void initializeFromAngle(sf::Texture&, const Deck*, sf::Vector2f, sf::Angle, float, float, sf::Angle);
		void initializeFromPosition(sf::Texture&, const Deck*, sf::Vector2f, sf::Vector2f, float, sf::Angle);

		// === ������� ===
		void setCardAtlas(sf::Texture&);
		void setDeck(const Deck*);
		void setAngle(sf::Angle);
		void setStartPosition(sf::Vector2f);
		void setEndPosition(sf::Vector2f);
		void setPosition(sf::Vector2f, sf::Vector2f);
		void setSpacing(float);
		void setRendering(bool);
		void setDeckStyle(DeckStyle);

		// === ��������� ����������� ���� � ������ ===
		void setCardsScale(float);
		void setCardsRotation(sf::Angle);
		void setCardsRandomRotation(std::mt19937&, float, float);
		void setCardsRandomRotation(float, float);

		// === ������� ===
		inline sf::Angle getCardsRotation() const { return _deckRotation; };
		inline const sf::Vector2f getCardsScale() const { return _deckScale; };
		inline const sf::Vector2f getStartPosition() const { return _startPos; };
		inline const sf::Vector2f getEndPosition() const { return _endPos; };
		inline sf::Angle getAngle() const { return _angle; };
		inline float getSpacing() const { return _spacing; };
		inline bool isRendering() const { return _isRendering; };
		inline DeckStyle getDeckStyle() const { return _deckStyle; };
		const CardRenderer& getCardRender(int) const;

		// === ������ ��������� ===
		void draw(sf::RenderTarget&);
		void update();

	private:
		// === ���������� ���� _spacing, ������ �� ��������� � �������� ������ ���� � ������ ===
		float spacingFromLength(int, sf::Vector2f, sf::Vector2f);
	};

	// === ������� ���������� ���� � �����, ������ �� ��������� � �������� ������� ===
	float calculateAngle(sf::Vector2f, sf::Vector2f);
	float calculateLength(sf::Vector2f, sf::Vector2f);

	// === �������, ������������ TVector<sf::Vector2f> � ������� ����������� ===
	TVector<sf::Vector2f> getCoordinatesVectorFromAngle(int, sf::Vector2f, sf::Angle, float);
	TVector<sf::Vector2f> getCoordinatesVectorFromPosition(int, sf::Vector2f, sf::Vector2f);
}
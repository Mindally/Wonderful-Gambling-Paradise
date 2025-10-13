#include "cardRenderer.h"

namespace WGP {
	cardRenderer::cardRenderer()
		: _material(_cardPlaceholder), _frontImage(_cardPlaceholder)
	{
		_card = nullptr;
		_isRendering = false;
	}

	cardRenderer::cardRenderer(sf::Texture& cardAtlas, const card* card)
		: _material(cardAtlas), _frontImage(cardAtlas)
	{
		if (card == nullptr) {
			throw std::invalid_argument("cardRenderer: Unable to set card - 'card' is nullptr");
		}
		_card = card;
		_isRendering = false;
		setOriginToLocalCentre();
		setScale(sf::Vector2f(1.f, 1.f));
		setPosition(sf::Vector2f(OUT_OF_BOUNDS, OUT_OF_BOUNDS));
		setRotation(sf::Angle(sf::degrees(0)));
		update();
	}

	cardRenderer::cardRenderer(sf::Texture& cardAtlas, const card* card, sf::Vector2f scale, sf::Angle rotation, sf::Vector2f pos)
		: _material(cardAtlas), _frontImage(cardAtlas)
	{
		if (card == nullptr) {
			throw std::invalid_argument("cardRenderer: Unable to set card - 'card' is nullptr");
		}
		_card = card;
		_isRendering = _card->state() != CardState::Blank;
		setOriginToLocalCentre();
		setScale(scale);
		setPosition(pos);
		setRotation(rotation);
		update();
	}

	cardRenderer::cardRenderer(sf::Texture& cardAtlas, const card* card, float scale, sf::Angle rotation, sf::Vector2f pos)
		: _material(cardAtlas), _frontImage(cardAtlas)
	{
		if (card == nullptr) {
			throw std::invalid_argument("cardRenderer: Unable to set card - 'card' is nullptr");
		}
		_card = card;
		_isRendering = _card->state() != CardState::Blank;
		setOriginToLocalCentre();
		setScale(scale);
		setPosition(pos);
		setRotation(rotation);
		update();
	}

	cardRenderer::cardRenderer(const cardRenderer& other)
		: _material(other._material), _frontImage(other._frontImage)
	{
		_card = other._card;
		_isRendering = other.isRendering();
		setOriginToLocalCentre();
		setScale(other.getScale());
		setPosition(other.getPosition());
		setRotation(other.getRotation());
	}

	void cardRenderer::initialize(sf::Texture& cardAtlas, const card* card, float scale, sf::Vector2f pos, sf::Angle rotation) {
		if (card == nullptr) {
			throw std::invalid_argument("cardRenderer.setCard: Unable to set card - 'card' is nullptr");
		}
		_material.setTexture(cardAtlas);
		_frontImage.setTexture(cardAtlas);
		_card = card;
		_material.setScale(sf::Vector2f(scale, scale));
		_frontImage.setScale(sf::Vector2f(scale, scale));
		_material.setPosition(pos);
		_frontImage.setPosition(pos);
		_material.setRotation(rotation);
		_frontImage.setRotation(rotation);
		_isRendering = true;

		update();
	}

	void cardRenderer::setCardAtlas(sf::Texture& cardAtlas) {
		_material.setTexture(cardAtlas);
		_frontImage.setTexture(cardAtlas);
		update();
	}

	void cardRenderer::setCard(const card* newCard) {
		if (newCard == nullptr) {
			throw std::invalid_argument("cardRenderer.setCard: Unable to set card - 'card' is nullptr");
		}
		_card = newCard;
		update();
	}

	void cardRenderer::setScale(sf::Vector2f scale) {
		_material.setScale(scale);
		_frontImage.setScale(scale);
	}

	void cardRenderer::setScale(float scale) {
		_material.setScale(sf::Vector2f(scale, scale));
		_frontImage.setScale(sf::Vector2f(scale, scale));
	}

	void cardRenderer::setPosition(sf::Vector2f pos) {
		_material.setPosition(pos);
		_frontImage.setPosition(pos);
	}

	void cardRenderer::move(sf::Vector2f shifting) {
		_material.move(shifting);
		_frontImage.move(shifting);
	}

	void cardRenderer::setRotation(sf::Angle rotation) {
		_material.setRotation(rotation);
		_frontImage.setRotation(rotation);
	}

	void cardRenderer::setOrigin(sf::Vector2f point) {
		_material.setOrigin(point);
		_frontImage.setOrigin(point);
	}

	void cardRenderer::setColor(sf::Color color) {
		_material.setColor(color);
		_frontImage.setColor(color);
	}

	void cardRenderer::resetColor() {
		setColor(sf::Color(255, 255, 255, 255));
	}



	sf::Vector2f cardRenderer::getScale() const {
		return _material.getScale();
	}

	bool cardRenderer::isRendering() const {
		return _isRendering;
	}

	sf::Vector2f cardRenderer::getPosition() const {
		return _material.getPosition();
	}

	sf::FloatRect cardRenderer::getLocalBounds() const {
		return _material.getLocalBounds();
	}

	sf::FloatRect cardRenderer::getGlobalBounds() const {
		return _material.getGlobalBounds();
	}

	sf::Angle cardRenderer::getRotation() const {
		return _material.getRotation();
	}

	void cardRenderer::draw(sf::RenderTarget& target) {
		if (!_isRendering) return;
		target.draw(_material);
		target.draw(_frontImage);
	}

	void cardRenderer::update() {
		_isRendering = _card->state() != CardState::Blank;
		if (_card->state() != CardState::FaceDown) _material.setTextureRect(coordsToIntRectCardAtlas(sf::Vector2u(1, 4)));
		else _material.setTextureRect(coordsToIntRectCardAtlas(sf::Vector2u(0, 4)));

		_frontImage.setTextureRect(cardToIntRectCardAtlas(*_card));
		if (_card->state() == CardState::FaceDown) _frontImage.setColor(sf::Color(255, 255, 255, 0));
		else _frontImage.setColor(sf::Color(255, 255, 255, 255));
		setOriginToLocalCentre();
	}

	void cardRenderer::assign(const cardRenderer& other) {
		_card = other._card;
		_isRendering = other.isRendering();
		_material = other._material;
		_frontImage = other._frontImage;
		setScale(other.getScale());
		setOriginToLocalCentre();
		setPosition(other.getPosition());
		setRotation(other.getRotation());
	}

	void cardRenderer::setOriginToLocalCentre() {
		setOrigin(getLocalCentreOfSprite(_material));
	}

	void cardRenderer::setOriginToGlobalCentre() {
		setOrigin(getGlobalCentreOfSprite(_material));
	}

	// Supportive functions

	sf::Vector2f getLocalCentreOfSprite(sf::Sprite& sprite) {
		sf::FloatRect bounds = sprite.getLocalBounds();
		return sf::Vector2f(bounds.getCenter());
	}

	sf::Vector2f getGlobalCentreOfSprite(sf::Sprite& sprite) {
		sf::FloatRect bounds = sprite.getGlobalBounds();
		return sf::Vector2f(bounds.getCenter());
	}

	sf::IntRect coordsToIntRectCardAtlas(sf::Vector2u indices) {
		sf::Vector2i size(CARD_SPRITE_WIDTH, CARD_SPRITE_HEIGHT);
		int posX = 0, posY = 0;
		if ((indices.x > 12 || indices.x < 0) || (indices.y > 4 || indices.y < 0)) {
			posX = CARD_ATLAS_SPACING + 2 * (CARD_SPRITE_WIDTH + CARD_ATLAS_SPACING);
			posY = CARD_ATLAS_SPACING + 4 * (CARD_SPRITE_HEIGHT + CARD_ATLAS_SPACING);
			throw std::out_of_range("coordscoordsToIntRectCardAtlas: Invalid argument 'indices' - coords out of range");
		}
		else {
			posX = CARD_ATLAS_SPACING + indices.x * (CARD_SPRITE_WIDTH + CARD_ATLAS_SPACING);
			posY = CARD_ATLAS_SPACING + indices.y * (CARD_SPRITE_HEIGHT + CARD_ATLAS_SPACING);
		}
		sf::Vector2i pos(posX, posY);
		return sf::IntRect(pos, size);
	}

	sf::IntRect cardToIntRectCardAtlas(const card card) {
		sf::Vector2i size(CARD_SPRITE_WIDTH, CARD_SPRITE_HEIGHT);
		int posX = CARD_ATLAS_SPACING + (static_cast<int>(card.rank()) - 2) * (CARD_SPRITE_WIDTH + CARD_ATLAS_SPACING);
		int posY = CARD_ATLAS_SPACING + static_cast<int>(card.suit()) * (CARD_SPRITE_HEIGHT + CARD_ATLAS_SPACING);
		sf::Vector2i pos(posX, posY);
		return sf::IntRect(pos, size);
	}
}
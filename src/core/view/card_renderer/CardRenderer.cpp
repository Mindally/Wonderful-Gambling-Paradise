#include "CardRenderer.hpp"

namespace wgp {

// =============================================
// ÊÎÍÑÒÐÓÊÒÎÐÛ
// =============================================

	CardRenderer::CardRenderer() : 
		_material(_cardPlaceholder),
		_frontImage(_cardPlaceholder),
		_card(nullptr),
		_isRendering(false)
	{}

	CardRenderer::CardRenderer(sf::Texture& cardAtlas, const Card* card) :
		_material(cardAtlas),
		_frontImage(cardAtlas),
		_card(card),
		_isRendering(false)
	{
		if (card == nullptr) {
			throw std::invalid_argument("CardRenderer: Unable to set card - 'card' is nullptr");
		}
		setOriginToLocalCentre();
		setScale(sf::Vector2f(1.f, 1.f));
		setPosition(sf::Vector2f(OUT_OF_BOUNDS, OUT_OF_BOUNDS));
		setRotation(sf::Angle(sf::degrees(0)));
		update();
	}

	CardRenderer::CardRenderer(sf::Texture& cardAtlas, const Card* card, sf::Vector2f scale, sf::Angle rotation, sf::Vector2f pos) :
		_material(cardAtlas),
		_frontImage(cardAtlas),
		_card(card),
		_isRendering(_card->state() != CardState::Blank)
	{
		if (card == nullptr) {
			throw std::invalid_argument("CardRenderer: Unable to set card - 'card' is nullptr");
		}
		setOriginToLocalCentre();
		setScale(scale);
		setPosition(pos);
		setRotation(rotation);
		update();
	}

	CardRenderer::CardRenderer(sf::Texture& cardAtlas, const Card* card, float scale, sf::Angle rotation, sf::Vector2f pos) :
		_material(cardAtlas),
		_frontImage(cardAtlas),
		_card(card),
		_isRendering(_card->state() != CardState::Blank)
	{
		if (card == nullptr) {
			throw std::invalid_argument("CardRenderer: Unable to set card - 'card' is nullptr");
		}
		setOriginToLocalCentre();
		setScale(scale);
		setPosition(pos);
		setRotation(rotation);
		update();
	}

	CardRenderer::CardRenderer(const CardRenderer& other) :
		_material(other._material),
		_frontImage(other._frontImage),
		_card(other._card),
		_isRendering(other._isRendering)
	{
		setOriginToLocalCentre();
		setScale(other.getScale());
		setPosition(other.getPosition());
		setRotation(other.getRotation());
	}

// =============================================
// ÎÁÙÈÉ ÌÅÒÎÄ ÈÍÈÖÈÀËÈÇÀÖÈÈ ÊËÀÑÑÀ
// =============================================

	void CardRenderer::initialize(sf::Texture& cardAtlas, const Card* card, float scale, sf::Vector2f pos, sf::Angle rotation) {
		if (card == nullptr) {
			throw std::invalid_argument("CardRenderer.setCard: Unable to set card - 'card' is nullptr");
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

// =============================================
// ÑÅÒÒÅÐÛ
// =============================================

	void CardRenderer::setCardAtlas(sf::Texture& cardAtlas) {
		_material.setTexture(cardAtlas);
		_frontImage.setTexture(cardAtlas);
		update();
	}

	void CardRenderer::setCard(const Card* newCard) {
		if (newCard == nullptr) {
			throw std::invalid_argument("CardRenderer.setCard: Unable to set card - 'card' is nullptr");
		}
		_card = newCard;
		update();
	}

	void CardRenderer::setScale(sf::Vector2f scale) {
		_material.setScale(scale);
		_frontImage.setScale(scale);
	}

	void CardRenderer::setScale(float scale) {
		_material.setScale(sf::Vector2f(scale, scale));
		_frontImage.setScale(sf::Vector2f(scale, scale));
	}

	void CardRenderer::setPosition(sf::Vector2f pos) {
		_material.setPosition(pos);
		_frontImage.setPosition(pos);
	}

	void CardRenderer::move(sf::Vector2f shifting) {
		_material.move(shifting);
		_frontImage.move(shifting);
	}

	void CardRenderer::setRotation(sf::Angle rotation) {
		_material.setRotation(rotation);
		_frontImage.setRotation(rotation);
	}

	void CardRenderer::setOrigin(sf::Vector2f point) {
		_material.setOrigin(point);
		_frontImage.setOrigin(point);
	}

	void CardRenderer::setColor(sf::Color color) {
		_material.setColor(color);
		_frontImage.setColor(color);
	}

	void CardRenderer::resetColor() {
		setColor(sf::Color(255, 255, 255, 255));
	}

// =============================================
// ÌÅÒÎÄÛ ÎÒÐÈÑÎÂÊÈ
// =============================================

	void CardRenderer::draw(sf::RenderTarget& target) {
		if (!_isRendering || _card == nullptr) return;
		target.draw(_material);
		target.draw(_frontImage);
	}

	void CardRenderer::update() {
		if (_card == nullptr) {
			throw std::logic_error("CardRenderer.update: Unable to update - '_card' is nullptr");
		}
		_isRendering = _card->state() != CardState::Blank;
		if (_card->state() != CardState::FaceDown) _material.setTextureRect(coordsToIntRectCardAtlas(sf::Vector2u(1, 4)));
		else _material.setTextureRect(coordsToIntRectCardAtlas(sf::Vector2u(0, 4)));

		_frontImage.setTextureRect(cardToIntRectCardAtlas(*_card));
		if (_card->state() == CardState::FaceDown) _frontImage.setColor(sf::Color(255, 255, 255, 0));
		else _frontImage.setColor(sf::Color(255, 255, 255, 255));
		setOriginToLocalCentre();
	}

// =============================================
// ÏÐÎ×ÈÅ ÌÅÒÎÄÛ
// =============================================

	void CardRenderer::assign(const CardRenderer& other) {
		_card = other._card;
		_isRendering = other.isRendering();
		_material = other._material;
		_frontImage = other._frontImage;
		setScale(other.getScale());
		setOriginToLocalCentre();
		setPosition(other.getPosition());
		setRotation(other.getRotation());
	}

// =============================================
// ÏÅÐÅÃÐÓÇÊÀ ÎÏÅÐÀÒÎÐÎÂ
// =============================================

	void CardRenderer::operator=(const CardRenderer& other) {
		this->assign(other);
	}

// =============================================
// ÑÅÒÒÅÐÛ, ×ÒÎÁÛ ÍÀÇÍÀ×ÈÒÜ origin ÑÏÐÀÉÒÎÂ ÊÀÐÒ Â ÈÕ ÖÅÍÒÐ
// =============================================

	void CardRenderer::setOriginToLocalCentre() {
		setOrigin(getLocalCentreOfSprite(_material));
	}

	void CardRenderer::setOriginToGlobalCentre() {
		setOrigin(getGlobalCentreOfSprite(_material));
	}

// =============================================
// ÔÓÍÊÖÈÈ ÎÏÅÐÅÄÅËÅÍÈß ÖÅÍÒÐÀ sf::Sprite
// =============================================

	sf::Vector2f getLocalCentreOfSprite(sf::Sprite& sprite) {
		sf::FloatRect bounds = sprite.getLocalBounds();
		return sf::Vector2f(bounds.getCenter());
	}

	sf::Vector2f getGlobalCentreOfSprite(sf::Sprite& sprite) {
		sf::FloatRect bounds = sprite.getGlobalBounds();
		return sf::Vector2f(bounds.getCenter());
	}

// =============================================
// ÄÎÏÎËÍÈÒÅËÜÍÛÅ ÔÓÍÊÖÈÈ ÏÅÐÅÑ×¨ÒÀ ÊÎÎÐÄÈÍÀÒ ÈËÈ ÊÀÐÒÛ Â sf::IntRect
// =============================================

	sf::IntRect coordsToIntRectCardAtlas(sf::Vector2u indices) {
		sf::Vector2i size(CARD_SPRITE_WIDTH, CARD_SPRITE_HEIGHT);
		int posX = 0, posY = 0;
		if ((indices.x > 12 || indices.x < 0) || (indices.y > 4 || indices.y < 0)) {
			posX = CARD_ATLAS_SPACING + 2 * (CARD_SPRITE_WIDTH + CARD_ATLAS_SPACING);
			posY = CARD_ATLAS_SPACING + 4 * (CARD_SPRITE_HEIGHT + CARD_ATLAS_SPACING);
			throw std::out_of_range("coordsToIntRectCardAtlas: Invalid argument 'indices' - coords out of range");
		}
		else {
			posX = CARD_ATLAS_SPACING + indices.x * (CARD_SPRITE_WIDTH + CARD_ATLAS_SPACING);
			posY = CARD_ATLAS_SPACING + indices.y * (CARD_SPRITE_HEIGHT + CARD_ATLAS_SPACING);
		}
		sf::Vector2i pos(posX, posY);
		return sf::IntRect(pos, size);
	}

	sf::IntRect cardToIntRectCardAtlas(const Card& card) {
		sf::Vector2i size(CARD_SPRITE_WIDTH, CARD_SPRITE_HEIGHT);
		int posX = CARD_ATLAS_SPACING + (static_cast<int>(card.rank()) - 2) * (CARD_SPRITE_WIDTH + CARD_ATLAS_SPACING);
		int posY = CARD_ATLAS_SPACING + static_cast<int>(card.suit()) * (CARD_SPRITE_HEIGHT + CARD_ATLAS_SPACING);
		sf::Vector2i pos(posX, posY);
		return sf::IntRect(pos, size);
	}
}
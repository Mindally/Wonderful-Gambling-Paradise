#include "cardRenderer.h"

//"../../../resources/textures/default/cardPlaceholder.png"

cardRenderer::cardRenderer()
	: _material(cardPlaceholder), _frontImage(cardPlaceholder)
{
	_card = new card;
	_isRendering = false;
}

cardRenderer::cardRenderer(sf::Texture& cardAtlas, card* card)
	: _material(cardPlaceholder), _frontImage(cardPlaceholder)
{
	_card = card;
	_isRendering = false;
	setCardAtlas(cardAtlas);
	setOriginToLocalCentre();
	setScale(sf::Vector2f(1, 1));
	setPosition(sf::Vector2f(OUT_OF_BOUNDS, OUT_OF_BOUNDS));
	setRotation(sf::Angle(sf::degrees(0)));
}

cardRenderer::cardRenderer(sf::Texture& cardAtlas, card* card, sf::Vector2f scale, sf::Angle rotation, sf::Vector2f pos)
	: _material(cardPlaceholder), _frontImage(cardPlaceholder)
{
	_card = card;
	_isRendering = _card->state() != Blank;
	setCardAtlas(cardAtlas);
	setOriginToLocalCentre();
	setScale(scale);
	setPosition(pos);
	setRotation(rotation);
}

cardRenderer::cardRenderer(sf::Texture& cardAtlas, card* card, float scale, sf::Angle rotation, sf::Vector2f pos)
	: _material(cardPlaceholder), _frontImage(cardPlaceholder)
{
	_card = card;
	_isRendering = _card->state() != Blank;
	setCardAtlas(cardAtlas);
	setOriginToLocalCentre();
	setScale(scale);
	setPosition(pos);
	setRotation(rotation);
}

cardRenderer::cardRenderer(const cardRenderer& other)
	: _material(other._material), _frontImage(other._frontImage)
{
	_card = other._card;
	_isRendering = other.isRendering();
	_material = other._material;
	_frontImage = other._frontImage;
	setOriginToLocalCentre();
	setScale(other.getScale());
	setPosition(other.getPosition());
	setRotation(other.getRotation());
}

void cardRenderer::setCardAtlas(sf::Texture& cardAtlas) {
	_material.setTexture(cardAtlas);
	_frontImage.setTexture(cardAtlas);
}

void cardRenderer::setCard(card* newCard) {
	_card = newCard;
}

void cardRenderer::setScale(sf::Vector2f scale) {
	_material.setScale(scale);
	_frontImage.setScale(scale);
}

void cardRenderer::setScale(float scale) {
	sf::Vector2f vecScale(scale, scale);
	_material.setScale(vecScale);
	_frontImage.setScale(vecScale);
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
	if (_material.getPosition().x < (-1) * getGlobalBounds().size.x || _material.getPosition().y < (-1) * getGlobalBounds().size.y) return;
	updateVisual();
	target.draw(_material);
	target.draw(_frontImage);
}

void cardRenderer::updateVisual() {
	_isRendering = _card->state() != Blank;
	if (_card->state() != FaceDown) _material.setTextureRect(recalculateCordsToIntRect(1, 4));
	else _material.setTextureRect(recalculateCordsToIntRect(0, 4));

	_frontImage.setTextureRect(recalculateCardToIntRect(*_card));
	if (_card->state() == FaceDown) _frontImage.setColor(sf::Color(255, 255, 255, 0));
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
	sf::FloatRect bounds = _material.getLocalBounds();
	float originX = std::round(bounds.size.x / 2.f);
	float originY = std::round(bounds.size.y / 2.f);
	setOrigin(sf::Vector2f(originX, originY));
}

void cardRenderer::setOriginToGlobalCentre() {
	sf::FloatRect bounds = _material.getGlobalBounds();
	float originX = std::round(bounds.size.x / 2.f);
	float originY = std::round(bounds.size.y / 2.f);
	setOrigin(sf::Vector2f(originX, originY));
}



sf::IntRect recalculateCordsToIntRect(unsigned indexX, unsigned indexY) {
	sf::Vector2i size(CARD_SPRITE_WIDTH, CARD_SPRITE_HEIGHT);
	int posX = CARD_ATLAS_SPACING + indexX * (CARD_SPRITE_WIDTH + CARD_ATLAS_SPACING);
	int posY = CARD_ATLAS_SPACING + indexY * (CARD_SPRITE_HEIGHT + CARD_ATLAS_SPACING);

	if ((indexX > 12 || indexX < 0) || (indexY > 4 || indexY < 0)) {
		posX = CARD_ATLAS_SPACING + 2 * (CARD_SPRITE_WIDTH + CARD_ATLAS_SPACING);
		posY = CARD_ATLAS_SPACING + 4 * (CARD_SPRITE_HEIGHT + CARD_ATLAS_SPACING);
	}
	sf::Vector2i pos(posX, posY);
	return sf::IntRect(pos, size);
}

sf::IntRect recalculateCardToIntRect(card card) {
	sf::Vector2i size(CARD_SPRITE_WIDTH, CARD_SPRITE_HEIGHT);
	int posX = CARD_ATLAS_SPACING + (card.rank() - 2) * (CARD_SPRITE_WIDTH + CARD_ATLAS_SPACING);
	int posY = CARD_ATLAS_SPACING + card.suit() * (CARD_SPRITE_HEIGHT + CARD_ATLAS_SPACING);
	sf::Vector2i pos(posX, posY);
	return sf::IntRect(pos, size);
}
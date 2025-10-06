#include "cardFieldRenderer.h"

// Constructors

cardFieldRenderer::cardFieldRenderer() :
	_klondikeField(nullptr),
	_cardAtlas(nullptr),
	_klondikeAtlas(nullptr),
	_cardsScale(1.f),
	_cardsSpacing(0.f),
	_columnSpacing(0.f),
	_rowSpacing(0.f),
	_startPosition(sf::Vector2f(OUT_OF_BOUNDS, OUT_OF_BOUNDS)),
	_isRendering(false)
{

}

cardFieldRenderer::cardFieldRenderer(sf::Texture& cardAtlas, sf::Texture& klondikeAtlas, card_field* field, float scale, float cardsSpacing, float colSpacing, float rowSpacing, sf::Vector2f startPos) :
	_cardAtlas(&cardAtlas),
	_klondikeAtlas(&klondikeAtlas),
	_startPosition(sf::Vector2f(OUT_OF_BOUNDS, OUT_OF_BOUNDS))
{
	setKlondikeField(field);
	setScale(scale);
	setCardsSpacing(cardsSpacing);
	setColumnSpacing(colSpacing);
	setRowSpacing(rowSpacing);
	setRendering(true);
}

// Setters

void cardFieldRenderer::setKlondikeField(card_field* newField) {
	if (newField == nullptr) {
		throw std::logic_error("klondikeFieldRenderer.setKlondikeField: Unable to set field - 'newField' is nullptr");
	}
	_klondikeField = newField;
	//update();
}

void cardFieldRenderer::setCardAtlas(sf::Texture& cardAtlas) {
	_cardAtlas = &cardAtlas;
	//for (int i = 0; i < 7; i++) _tableauPilesRenders[i].setCardAtlas(cardAtlas);
	//for (int i = 0; i < 4; i++) _foundationPilesRenders[i].setCardAtlas(cardAtlas);
	//_stockPileRender.setCardAtlas(cardAtlas);
	//_wastePileRender.setCardAtlas(cardAtlas);
	//update()
}

void cardFieldRenderer::setKlondikeAtlas(sf::Texture& klondikeAtlas) {
	_klondikeAtlas = &klondikeAtlas;
	// ???
	//update()
}

void cardFieldRenderer::setScale(float scale) {
	if (scale <= 0) {
		throw std::invalid_argument("klondikeFieldRenderer.setScale: Invalid argument 'scale' - must be > 0");
	}
	for (int i = 0; i < 7; i++) _tableauPilesRenders[i].setCardsScale(scale);
	for (int i = 0; i < 4; i++) _foundationPilesRenders[i].setScale(scale);
	_stockPileRender.setScale(scale);
	_wastePileRender.setScale(scale);
	//update()
}

void cardFieldRenderer::setCardsSpacing(float cardsSpacing) {
	if (cardsSpacing <= 0) {
		throw std::invalid_argument("klondikeFieldRenderer.setCardsSpacing: Invalid argument 'cardsSpacing' - must be > 0");
	}
	_cardsSpacing = cardsSpacing;
	//update()
}

void cardFieldRenderer::setColumnSpacing(float colSpacing) {
	if (colSpacing <= 0) {
		throw std::invalid_argument("klondikeFieldRenderer.setColumnSpacing: Invalid argument 'colSpacing' - must be > 0");
	}
	_columnSpacing = colSpacing;
	//update()
}

void cardFieldRenderer::setRowSpacing(float rowSpacing) {
	if (rowSpacing <= 0) {
		throw std::invalid_argument("klondikeFieldRenderer.setRowSpacing: Invalid argument 'rowSpacing' - must be > 0");
	}
	_rowSpacing = rowSpacing;
	//update()
}

void cardFieldRenderer::setStartPosition(sf::Vector2f startPos) {
	_startPosition = startPos;
	//update()
}

void cardFieldRenderer::setRendering(bool isRendering) {
	if (_klondikeField == nullptr || _cardAtlas == nullptr) _isRendering = false;
	else _isRendering = isRendering;
}

// Getters

float cardFieldRenderer::getScale() const {
	return _cardsScale;
}

float cardFieldRenderer::getCardsSpacing() const {
	return _cardsSpacing;
}

float cardFieldRenderer::getColumnSpacing() const {
	return _columnSpacing;
}

float cardFieldRenderer::getRowSpacing() const {
	return _rowSpacing;
}

sf::Vector2f cardFieldRenderer::getStartPosition() const {
	return _startPosition;
}

bool cardFieldRenderer::isRendering() const {
	return _isRendering;
}
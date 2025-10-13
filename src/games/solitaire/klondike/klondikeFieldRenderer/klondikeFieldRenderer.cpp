#include "klondikeFieldRenderer.h"

namespace WGP {
	// Constructor
	klondikeFieldRenderer::klondikeFieldRenderer(sf::Texture& cardAtlas, sf::Texture& klondikeAtlas, klondikeField* field, const sf::Font& font, float scale, float cardsSpacing, float colSpacing, float rowSpacing, sf::Vector2f startPos) :
		_stockPileRender(cardAtlas),
		_emptyWastePile(klondikeAtlas),
		_cardAtlas(&cardAtlas),
		_klondikeAtlas(&klondikeAtlas),
		_font(font),
		_startPosition(startPos)
	{
		setKlondikeField(field);
		setScale(scale);
		setCardsSpacing(cardsSpacing);
		setColumnSpacing(colSpacing);
		setRowSpacing(rowSpacing);
		setRendering(true);

		stockPileSpriteInit();
		_stockPileRender.setPosition(_startPosition);

		remainingCardsSetText();
		remainingCardsTextInit();

		sf::Vector2f wastePos = startPos + sf::Vector2f(colSpacing, 0.f);
		emptyWastePileSpriteInit();
		_emptyWastePile.setPosition(wastePos);

		_wastePileRender.initializeFromPosition(cardAtlas, &(_klondikeField->getWastePile()), wastePos, wastePos, scale, sf::Angle(sf::degrees(0)));

		TVector<sf::Vector2f> coords = getCoordinatesVectorFromAngle(4, wastePos + sf::Vector2f(2 * colSpacing, 0.f), sf::Angle(sf::degrees(0)), colSpacing);
		emptyFoundationPilesSpritesInit();
		for (int i = 0; i < coords.size(); i++) {
			_emptyFoundationPiles[i].setPosition(coords[i]);
			_foundationPilesRenders[i].initializeFromPosition(cardAtlas, &(_klondikeField->getFoundationPile(static_cast<CardSuit>(i))), coords[i], coords[i], scale, sf::Angle(sf::degrees(0)));
		}

		coords = getCoordinatesVectorFromAngle(7, startPos + sf::Vector2f(0.f, rowSpacing), sf::Angle(sf::degrees(0)), colSpacing);
		for (int i = 0; i < coords.size(); i++) {
			_tableauPilesRenders[i].initializeFromAngle(cardAtlas, &(_klondikeField->getTableauPile(i)), coords[i], sf::Angle(sf::degrees(90)), cardsSpacing, scale, sf::Angle(sf::degrees(0)));
		}
	}

	// Setters

	void klondikeFieldRenderer::setKlondikeField(klondikeField* newField) {
		if (newField == nullptr) {
			throw std::logic_error("klondikeFieldRenderer.setKlondikeField: Unable to set field - 'newField' is nullptr");
		}
		_klondikeField = newField;
		//update();
	}

	void klondikeFieldRenderer::setCardAtlas(sf::Texture& cardAtlas) {
		// Мб переписать
		_cardAtlas = &cardAtlas;
		for (int i = 0; i < 7; i++) _tableauPilesRenders[i].setCardAtlas(cardAtlas);
		for (int i = 0; i < 4; i++) _foundationPilesRenders[i].setCardAtlas(cardAtlas);
		_stockPileRender.setTexture(*_cardAtlas);
		_stockPileRender.setTextureRect(coordsToIntRectCardAtlas(sf::Vector2u(0, 4)));
		_wastePileRender.setCardAtlas(cardAtlas);
		//update();
	}

	void klondikeFieldRenderer::setKlondikeAtlas(sf::Texture& klondikeAtlas) {
		_klondikeAtlas = &klondikeAtlas;
		//emptyStockPileSpriteInit();
		//emptyFoundationPilesSpritesInit();
	}

	void klondikeFieldRenderer::setScale(float scale) {
		// Мб переписать
		_cardsScale = scale;
		if (scale <= 0) {
			throw std::invalid_argument("klondikeFieldRenderer.setScale: Invalid argument 'scale' - must be > 0");
		}
		/*for (int i = 0; i < 7; i++) _tableauPilesRenders[i].setCardsScale(scale);
		for (int i = 0; i < 4; i++) _foundationPilesRenders[i].setCardsScale(scale);
		_stockPileRender.setCardsScale(scale);
		_wastePileRender.setCardsScale(scale);*/
	}

	void klondikeFieldRenderer::setCardsSpacing(float cardsSpacing) {
		if (cardsSpacing <= 0) {
			throw std::invalid_argument("klondikeFieldRenderer.setCardsSpacing: Invalid argument 'cardsSpacing' - must be > 0");
		}
		_cardsSpacing = cardsSpacing;
		//update();
	}

	void klondikeFieldRenderer::setColumnSpacing(float colSpacing) {
		if (colSpacing <= 0) {
			throw std::invalid_argument("klondikeFieldRenderer.setColumnSpacing: Invalid argument 'colSpacing' - must be > 0");
		}
		_columnSpacing = colSpacing;
		//update();
	}

	void klondikeFieldRenderer::setRowSpacing(float rowSpacing) {
		if (rowSpacing <= 0) {
			throw std::invalid_argument("klondikeFieldRenderer.setRowSpacing: Invalid argument 'rowSpacing' - must be > 0");
		}
		_rowSpacing = rowSpacing;
		//update();
	}

	void klondikeFieldRenderer::setStartPosition(sf::Vector2f startPos) {
		_startPosition = startPos;
		//update();
	}

	void klondikeFieldRenderer::setRendering(bool isRendering) {
		_isRendering = isRendering;
	}

	// Functions

	void klondikeFieldRenderer::draw(sf::RenderTarget& target) {
		// Разделить draw и update
		if (!_isRendering) return;
		if (!_klondikeField->getStockPile().isEmpty()) {
			target.draw(_stockPileRender);
		}
		remainingCardsSetText();
		target.draw(_remainingCardsInStock);
		if (_klondikeField->getWastePile().isEmpty()) {
			target.draw(_emptyWastePile);
		}
		_wastePileRender.draw(target);
		for (int i = 0; i < 4; i++) {
			if (_klondikeField->getFoundationPile(static_cast<CardSuit>(i)).isEmpty()) {
				target.draw(_emptyFoundationPiles[i]);
			}
			_foundationPilesRenders[i].draw(target);
		}
		for (int i = 0; i < 7; i++) {
			_tableauPilesRenders[i].draw(target);
		}
	}


	void klondikeFieldRenderer::update() {
		// Переписать
		for (int i = 0; i < 7; i++) {
			_tableauPilesRenders[i].update();
		}
		for (int i = 0; i < 4; i++) {
			_foundationPilesRenders[i].update();
		}
		//_stockPileRender.update();
		_wastePileRender.update();
	}

	// Getters

	float klondikeFieldRenderer::getScale() const {
		return _cardsScale;
	}

	float klondikeFieldRenderer::getCardsSpacing() const {
		return _cardsSpacing;
	}

	float klondikeFieldRenderer::getColumnSpacing() const {
		return _columnSpacing;
	}

	float klondikeFieldRenderer::getRowSpacing() const {
		return _rowSpacing;
	}

	sf::Vector2f klondikeFieldRenderer::getStartPosition() const {
		return _startPosition;
	}

	bool klondikeFieldRenderer::isRendering() const {
		return _isRendering;
	}

	// Private function

	void klondikeFieldRenderer::stockPileSpriteInit() {
		_stockPileRender.setTexture(*_cardAtlas);
		_stockPileRender.setTextureRect(coordsToIntRectCardAtlas(sf::Vector2u(0, 4)));
		_stockPileRender.setOrigin(getLocalCentreOfSprite(_stockPileRender));
		_stockPileRender.setRotation(sf::Angle(sf::degrees(0)));
		_stockPileRender.setScale(sf::Vector2f(_cardsScale, _cardsScale));
	}

	void klondikeFieldRenderer::emptyWastePileSpriteInit() {
		_emptyWastePile.setTexture(*_klondikeAtlas);
		_emptyWastePile.setTextureRect(coordsToIntRectKlondikeAtlas(0));
		_emptyWastePile.setOrigin(getLocalCentreOfSprite(_emptyWastePile));
		_emptyWastePile.setRotation(sf::Angle(sf::degrees(0)));
		_emptyWastePile.setScale(sf::Vector2f(_cardsScale, _cardsScale));

	}

	void klondikeFieldRenderer::emptyFoundationPilesSpritesInit() {
		for (int i = 0; i < 4; i++) {
			_emptyFoundationPiles[i].setTexture(*_klondikeAtlas);
			_emptyFoundationPiles[i].setTextureRect(coordsToIntRectKlondikeAtlas(1));
			_emptyFoundationPiles[i].setOrigin(getLocalCentreOfSprite(_emptyWastePile));
			_emptyFoundationPiles[i].setRotation(sf::Angle(sf::degrees(0)));
			_emptyFoundationPiles[i].setScale(sf::Vector2f(_cardsScale, _cardsScale));
		}
	}

	void klondikeFieldRenderer::remainingCardsTextInit() {
		_remainingCardsInStock.setFont(_font);
		_remainingCardsInStock.setFillColor(sf::Color(0, 0, 0, 255));
		_remainingCardsInStock.setOrigin(getLocalCentreOfText(_remainingCardsInStock));
		_remainingCardsInStock.setScale(sf::Vector2f(_cardsScale, _cardsScale));
		_remainingCardsInStock.setPosition(_startPosition);
	}

	void klondikeFieldRenderer::remainingCardsSetText() {
		_remainingCardsInStock.setString(std::to_string(_klondikeField->getStockPile().topIndex() + 1));
		_remainingCardsInStock.setOrigin(getLocalCentreOfText(_remainingCardsInStock));
	}

	// Supporitive functions

	sf::IntRect coordsToIntRectKlondikeAtlas(unsigned int index) {
		sf::Vector2i size(CARD_SPRITE_WIDTH, CARD_SPRITE_HEIGHT);
		int posX = 0, posY = 0;
		if (index != 0 && index != 1) {
			throw std::out_of_range("coordscoordsToIntRectKlondikeAtlas: Invalid argument 'index' - coords out of range");
		}
		else {
			posX = CARD_ATLAS_SPACING + index * (CARD_SPRITE_WIDTH + CARD_ATLAS_SPACING);
			posY = CARD_ATLAS_SPACING + 0 * (CARD_SPRITE_HEIGHT + CARD_ATLAS_SPACING);
		}
		sf::Vector2i pos(posX, posY);
		return sf::IntRect(pos, size);
	}

	sf::Vector2f getLocalCentreOfText(sf::Text& text) {
		sf::FloatRect bounds = text.getLocalBounds();
		return sf::Vector2f(bounds.getCenter());
	}

	sf::Vector2f getGlobalCentreOfText(sf::Text& text) {
		sf::FloatRect bounds = text.getGlobalBounds();
		return sf::Vector2f(bounds.getCenter());
	}
}
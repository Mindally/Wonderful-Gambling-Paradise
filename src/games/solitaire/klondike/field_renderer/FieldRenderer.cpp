#include "FieldRenderer.hpp"

namespace wgp {

	namespace klondike {

// =============================================
//  ŒÕ—“–” “Œ–
// =============================================

		FieldRenderer::FieldRenderer(sf::Texture& cardAtlas, sf::Texture& klondikeAtlas, Field* field, const sf::Font& font, float scale, float cardsSpacing, float colSpacing, float rowSpacing, sf::Vector2f startPos) :
			_field(field),
			_stockPileRender(cardAtlas),
			_emptyWastePile(klondikeAtlas),
			_cardAtlas(&cardAtlas),
			_klondikeAtlas(&klondikeAtlas),
			_font(font),
			_cardsScale(scale),
			_cardsSpacing(cardsSpacing),
			_columnSpacing(colSpacing),
			_rowSpacing(rowSpacing),
			_startPosition(startPos),
			_isRendering(true)
		{
			if (field == nullptr) {
				throw std::invalid_argument("klondike::FieldRenderer: Unable to set field - 'field' is nullptr");
			}
			if (scale <= 0) {
				throw std::invalid_argument("klondike::FieldRenderer: Unable to set scale - 'scale' must be > 0");
			}
			if (cardsSpacing <= 0) {
				throw std::invalid_argument("klondike::FieldRenderer: Unable to set cardSpacing - 'cardSpacing' must be > 0");
			}
			if (colSpacing <= 0) {
				throw std::invalid_argument("klondike::FieldRenderer: Unable to set colSpacing - 'colSpacing' must be > 0");
			}
			if (rowSpacing <= 0) {
				throw std::invalid_argument("klondike::FieldRenderer: Unable to set rowSpacing - 'rowSpacing' must be > 0");
			}

			stockPileSpriteInit();
			_stockPileRender.setPosition(_startPosition);

			remainingCardsSetText();
			remainingCardsTextInit();

			sf::Vector2f wastePos = startPos + sf::Vector2f(colSpacing, 0.f);
			emptyWastePileSpriteInit();
			_emptyWastePile.setPosition(wastePos);

			_wastePileRender.initializeFromPosition(cardAtlas, &(_field->getWastePile()), wastePos, wastePos, scale, sf::Angle(sf::degrees(0)));

			TVector<sf::Vector2f> coords = getCoordinatesVectorFromAngle(4, wastePos + sf::Vector2f(2 * colSpacing, 0.f), sf::Angle(sf::degrees(0)), colSpacing);
			emptyFoundationPilesSpritesInit();
			for (int i = 0; i < coords.size(); i++) {
				_emptyFoundationPiles[i].setPosition(coords[i]);
				_foundationPilesRenders[i].initializeFromPosition(cardAtlas, &(_field->getFoundationPile(static_cast<CardSuit>(i))), coords[i], coords[i], scale, sf::Angle(sf::degrees(0)));
			}

			coords = getCoordinatesVectorFromAngle(7, startPos + sf::Vector2f(0.f, rowSpacing), sf::Angle(sf::degrees(0)), colSpacing);
			for (int i = 0; i < coords.size(); i++) {
				_tableauPilesRenders[i].initializeFromAngle(cardAtlas, &(_field->getTableauPile(i)), coords[i], sf::Angle(sf::degrees(90)), cardsSpacing, scale, sf::Angle(sf::degrees(0)));
			}
		}

// =============================================
// —≈““≈–€
// =============================================

		void FieldRenderer::setField(Field* newField) {
			if (newField == nullptr) {
				throw std::logic_error("klondikeFieldRenderer.setKlondikeField: Unable to set field - 'newField' is nullptr");
			}
			_field = newField;
			//update();
		}

		void FieldRenderer::setCardAtlas(sf::Texture& cardAtlas) {
			// Ã· ÔÂÂÔËÒ‡Ú¸
			_cardAtlas = &cardAtlas;
			for (int i = 0; i < 7; i++) _tableauPilesRenders[i].setCardAtlas(cardAtlas);
			for (int i = 0; i < 4; i++) _foundationPilesRenders[i].setCardAtlas(cardAtlas);
			_stockPileRender.setTexture(*_cardAtlas);
			_stockPileRender.setTextureRect(coordsToIntRectCardAtlas(sf::Vector2u(0, 4)));
			_wastePileRender.setCardAtlas(cardAtlas);
			//update();
		}

		void FieldRenderer::setKlondikeAtlas(sf::Texture& klondikeAtlas) {
			_klondikeAtlas = &klondikeAtlas;
			//emptyStockPileSpriteInit();
			//emptyFoundationPilesSpritesInit();
		}

		void FieldRenderer::setScale(float scale) {
			// Ã· ÔÂÂÔËÒ‡Ú¸
			_cardsScale = scale;
			if (scale <= 0) {
				throw std::invalid_argument("klondikeFieldRenderer.setScale: Invalid argument 'scale' - must be > 0");
			}
			/*for (int i = 0; i < 7; i++) _tableauPilesRenders[i].setCardsScale(scale);
			for (int i = 0; i < 4; i++) _foundationPilesRenders[i].setCardsScale(scale);
			_stockPileRender.setCardsScale(scale);
			_wastePileRender.setCardsScale(scale);*/
		}

		void FieldRenderer::setCardsSpacing(float cardsSpacing) {
			if (cardsSpacing <= 0) {
				throw std::invalid_argument("klondikeFieldRenderer.setCardsSpacing: Invalid argument 'cardsSpacing' - must be > 0");
			}
			_cardsSpacing = cardsSpacing;
			//update();
		}

		void FieldRenderer::setColumnSpacing(float colSpacing) {
			if (colSpacing <= 0) {
				throw std::invalid_argument("klondikeFieldRenderer.setColumnSpacing: Invalid argument 'colSpacing' - must be > 0");
			}
			_columnSpacing = colSpacing;
			//update();
		}

		void FieldRenderer::setRowSpacing(float rowSpacing) {
			if (rowSpacing <= 0) {
				throw std::invalid_argument("klondikeFieldRenderer.setRowSpacing: Invalid argument 'rowSpacing' - must be > 0");
			}
			_rowSpacing = rowSpacing;
			//update();
		}

		void FieldRenderer::setStartPosition(sf::Vector2f startPos) {
			_startPosition = startPos;
			//update();
		}

		void FieldRenderer::setRendering(bool isRendering) {
			_isRendering = isRendering;
		}

// =============================================
// Ã≈“Œƒ€ Œ“–»—Œ¬ »
// =============================================

		void FieldRenderer::draw(sf::RenderTarget& target) {
			// –‡Á‰ÂÎËÚ¸ draw Ë update
			// ÕÂ˝ÙÙÂÍÚË‚ÌÓ, ÔÂÂÔËÒ‡Ú¸
			if (!_isRendering) return;
			remainingCardsSetText();

			if ((_field->getStockPile().isEmpty() || _field->getStockPile().isFull()) && _isStockSpriteNeedsChange == false) _isStockSpriteNeedsChange = true;

			if (_isStockSpriteNeedsChange) {
				//std::cout << "Entered!" << std::endl;
				updateStockSprite();
				_isStockSpriteNeedsChange = false;
			}

			target.draw(_stockPileRender);
			target.draw(_remainingCardsInStock);

			if (_field->getWastePile().isEmpty()) {
				target.draw(_emptyWastePile);
			}
			_wastePileRender.draw(target);
			for (int i = 0; i < 4; i++) {
				if (_field->getFoundationPile(static_cast<CardSuit>(i)).isEmpty()) {
					target.draw(_emptyFoundationPiles[i]);
				}
				_foundationPilesRenders[i].draw(target);
			}
			for (int i = 0; i < 7; i++) {
				_tableauPilesRenders[i].draw(target);
			}
		}

		void FieldRenderer::update() {
			// œÂÂÔËÒ‡Ú¸
			for (int i = 0; i < 7; i++) {
				_tableauPilesRenders[i].update();
			}
			for (int i = 0; i < 4; i++) {
				_foundationPilesRenders[i].update();
			}
			//_stockPileRender.update();
			_wastePileRender.update();
		}

// =============================================
// »Õ»÷»¿À»«¿÷»ﬂ —œ–¿…“Œ¬ Œ“–»—Œ¬ »
// =============================================

		void FieldRenderer::stockPileSpriteInit() {
			_stockPileRender.setTexture(*_cardAtlas);
			_stockPileRender.setTextureRect(coordsToIntRectCardAtlas(sf::Vector2u(0, 4)));
			_stockPileRender.setOrigin(getLocalCentreOfSprite(_stockPileRender));
			_stockPileRender.setRotation(sf::Angle(sf::degrees(0)));
			_stockPileRender.setScale(sf::Vector2f(_cardsScale, _cardsScale));
		}

		void FieldRenderer::emptyWastePileSpriteInit() {
			_emptyWastePile.setTexture(*_klondikeAtlas);
			_emptyWastePile.setTextureRect(coordsToIntRectKlondikeAtlas(0));
			_emptyWastePile.setOrigin(getLocalCentreOfSprite(_emptyWastePile));
			_emptyWastePile.setRotation(sf::Angle(sf::degrees(0)));
			_emptyWastePile.setScale(sf::Vector2f(_cardsScale, _cardsScale));

		}

		void FieldRenderer::emptyFoundationPilesSpritesInit() {
			for (int i = 0; i < 4; i++) {
				_emptyFoundationPiles[i].setTexture(*_klondikeAtlas);
				_emptyFoundationPiles[i].setTextureRect(coordsToIntRectKlondikeAtlas(1));
				_emptyFoundationPiles[i].setOrigin(getLocalCentreOfSprite(_emptyWastePile));
				_emptyFoundationPiles[i].setRotation(sf::Angle(sf::degrees(0)));
				_emptyFoundationPiles[i].setScale(sf::Vector2f(_cardsScale, _cardsScale));
			}
		}

// =============================================
// »Õ»÷»¿À»«¿÷»ﬂ “≈ —“¿ Œ“–»—Œ¬ »
// =============================================

		void FieldRenderer::remainingCardsTextInit() {
			_remainingCardsInStock.setFont(_font);
			_remainingCardsInStock.setFillColor(sf::Color(0, 0, 0, 255));
			_remainingCardsInStock.setOrigin(getLocalCentreOfText(_remainingCardsInStock));
			_remainingCardsInStock.setScale(sf::Vector2f(_cardsScale, _cardsScale));
			_remainingCardsInStock.setPosition(_startPosition);
		}

		void FieldRenderer::remainingCardsSetText() {
			_remainingCardsInStock.setString(std::to_string(_field->getStockPile().topIndex() + 1));
			_remainingCardsInStock.setOrigin(getLocalCentreOfText(_remainingCardsInStock));
		}

// =============================================
// œ–Œ¬≈– ¿ —Œ—“ŒﬂÕ»ﬂ ƒÀﬂ stockPile » wastePile
// =============================================

		void FieldRenderer::updateStockSprite() {
			if (_field->getStockPile().isEmpty()) {
				_stockPileRender.setTexture(*_klondikeAtlas);
				_stockPileRender.setTextureRect(coordsToIntRectKlondikeAtlas(0));
			}
			else {
				_stockPileRender.setTexture(*_cardAtlas);
				_stockPileRender.setTextureRect(coordsToIntRectCardAtlas(sf::Vector2u(0, 4)));
			}
		}

// =============================================
// œ–Œ◊»≈ ‘”Õ ÷»»
// =============================================

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
}
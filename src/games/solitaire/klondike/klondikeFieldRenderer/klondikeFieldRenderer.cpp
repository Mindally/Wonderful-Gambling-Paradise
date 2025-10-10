#include "klondikeFieldRenderer.h"

namespace WGP {
	// Constructors

	klondikeFieldRenderer::klondikeFieldRenderer() :
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

	klondikeFieldRenderer::klondikeFieldRenderer(sf::Texture& cardAtlas, sf::Texture& klondikeAtlas, klondikeField* field, float scale, float cardsSpacing, float colSpacing, float rowSpacing, sf::Vector2f startPos) :
		_cardAtlas(&cardAtlas),
		_klondikeAtlas(&klondikeAtlas),
		_startPosition(startPos)
	{
		setKlondikeField(field);
		setScale(scale);
		setCardsSpacing(cardsSpacing);
		setColumnSpacing(colSpacing);
		setRowSpacing(rowSpacing);
		setRendering(true);
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
		_cardAtlas = &cardAtlas;
		//for (int i = 0; i < 7; i++) _tableauPilesRenders[i].setCardAtlas(cardAtlas);
		//for (int i = 0; i < 4; i++) _foundationPilesRenders[i].setCardAtlas(cardAtlas);
		//_stockPileRender.setCardAtlas(cardAtlas);
		//_wastePileRender.setCardAtlas(cardAtlas);
		//update()
	}

	void klondikeFieldRenderer::setKlondikeAtlas(sf::Texture& klondikeAtlas) {
		_klondikeAtlas = &klondikeAtlas;
		// ???
		//update()
	}

	void klondikeFieldRenderer::setScale(float scale) {
		if (scale <= 0) {
			throw std::invalid_argument("klondikeFieldRenderer.setScale: Invalid argument 'scale' - must be > 0");
		}
		for (int i = 0; i < 7; i++) _tableauPilesRenders[i].setCardsScale(scale);
		for (int i = 0; i < 4; i++) _foundationPilesRenders[i].setCardsScale(scale);
		_stockPileRender.setCardsScale(scale);
		_wastePileRender.setCardsScale(scale);
		//update()
	}

	void klondikeFieldRenderer::setCardsSpacing(float cardsSpacing) {
		if (cardsSpacing <= 0) {
			throw std::invalid_argument("klondikeFieldRenderer.setCardsSpacing: Invalid argument 'cardsSpacing' - must be > 0");
		}
		_cardsSpacing = cardsSpacing;
		//update()
	}

	void klondikeFieldRenderer::setColumnSpacing(float colSpacing) {
		if (colSpacing <= 0) {
			throw std::invalid_argument("klondikeFieldRenderer.setColumnSpacing: Invalid argument 'colSpacing' - must be > 0");
		}
		_columnSpacing = colSpacing;
		//update()
	}

	void klondikeFieldRenderer::setRowSpacing(float rowSpacing) {
		if (rowSpacing <= 0) {
			throw std::invalid_argument("klondikeFieldRenderer.setRowSpacing: Invalid argument 'rowSpacing' - must be > 0");
		}
		_rowSpacing = rowSpacing;
		//update()
	}

	void klondikeFieldRenderer::setStartPosition(sf::Vector2f startPos) {
		_startPosition = startPos;
		//update()
	}

	void klondikeFieldRenderer::setRendering(bool isRendering) {
		_isRendering = isRendering;
	}

	// Functions

	void klondikeFieldRenderer::draw(sf::RenderTarget&) {

	}


	void klondikeFieldRenderer::update() {
		for (int i = 0; i < 7; i++) {
			_tableauPilesRenders[i].update();
		}
		// ??
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
}
#include "DeckRenderer.hpp"

namespace wgp {

// =============================================
//  ŒÕ—“–” “Œ–€
// =============================================

	DeckRenderer::DeckRenderer() :
		_cardAtlas(nullptr),
		_deckRotation(sf::degrees(0)),
		_deckScale(sf::Vector2f(1.f, 1.f)),
		_deck(nullptr),
		_angle(sf::Angle(sf::degrees(0))),
		_startPos(sf::Vector2f(OUT_OF_BOUNDS, OUT_OF_BOUNDS)),
		_endPos(sf::Vector2f(OUT_OF_BOUNDS, OUT_OF_BOUNDS)),
		_spacing(0.f),
		_isRendering(false),
		_deckStyle(DeckStyle::FromPosition)
	{}

	DeckRenderer::DeckRenderer(sf::Texture& cardAtlas, const Deck* deck, sf::Vector2f position) :
		_cardAtlas(&cardAtlas),
		_deckRotation(sf::degrees(0)),
		_deckScale(sf::Vector2f(1.f, 1.f)),
		_deck(deck),
		_angle(sf::Angle(sf::degrees(0))),
		_startPos(position),
		_endPos(position),
		_spacing(0.f),
		_isRendering(true),
		_deckStyle(DeckStyle::FromPosition)
	{
		if (deck == nullptr) throw std::logic_error("DeckRenderer: Unable to set deck - 'deck' is nullptr");
		update();
	}

	DeckRenderer::DeckRenderer(sf::Texture& cardAtlas, const Deck* deck, sf::Vector2f startPos, sf::Angle angle, float spacing) :
		_cardAtlas(&cardAtlas),
		_deckRotation(sf::degrees(0)),
		_deckScale(sf::Vector2f(1.f, 1.f)),
		_deck(deck),
		_angle(angle),
		_startPos(startPos),
		_spacing(spacing),
		_isRendering(true),
		_deckStyle(DeckStyle::FromAngleSpacing)
	{
		if (deck == nullptr) throw std::logic_error("DeckRenderer: Unable to set deck - 'deck' is nullptr");
		if (spacing < 0) throw std::invalid_argument("DeckRenderer: Invalid argument 'spacing' - must be > 0");
		update();
	}

	DeckRenderer::DeckRenderer(sf::Texture& cardAtlas, const Deck* deck, sf::Vector2f startPos, sf::Vector2f endPos) :
		_cardAtlas(&cardAtlas),
		_deckRotation(sf::degrees(0)),
		_deckScale(sf::Vector2f(1.f, 1.f)),
		_deck(deck),
		_angle(sf::Angle(sf::degrees(calculateAngle(_startPos, _endPos)))),
		_startPos(startPos),
		_endPos(endPos),
		_isRendering(true),
		_deckStyle(DeckStyle::FromPosition)
	{
		if (deck == nullptr) throw std::logic_error("DeckRenderer: Unable to set deck - 'deck' is nullptr");
		update();
	}

// =============================================
// Œ¡Ÿ»≈ Ã≈“Œƒ€ »Õ»÷»¿À»«¿÷»»  À¿——¿
// =============================================

	void DeckRenderer::initializeFromAngle(sf::Texture& cardAtlas, const Deck* deck, sf::Vector2f startPos, sf::Angle angle, float spacing, float scale, sf::Angle rotation) {
		if (deck == nullptr) {
			throw std::logic_error("DeckRenderer.initializeFromAngle: Unable to set deck - 'deck' is nullptr");
		}
		if (spacing < 0) {
			throw std::invalid_argument("DeckRenderer.initializeFromAngle: Invalid argument 'spacing' - must be > 0");
		}
		if (scale <= 0) {
			throw std::invalid_argument("DeckRenderer.setCardsScale: Invalid argument 'scale' - must be > 0");
		}
		_cardAtlas = &cardAtlas;
		_deckRotation = rotation;
		_deckScale = sf::Vector2f(scale, scale);
		_deck = deck;
		_angle = angle;
		_startPos = startPos;
		_spacing = spacing;
		_isRendering = true;
		_deckStyle = DeckStyle::FromAngleSpacing;
		update();
	}

	void DeckRenderer::initializeFromPosition(sf::Texture& cardAtlas, const Deck* deck, sf::Vector2f startPos, sf::Vector2f endPos, float scale, sf::Angle rotation) {
		if (deck == nullptr) {
			throw std::logic_error("DeckRenderer.initializeFromAngle: Unable to set deck - 'deck' is nullptr");
		}
		if (scale <= 0) {
			throw std::invalid_argument("DeckRenderer.setCardsScale: Invalid argument 'scale' - must be > 0");
		}
		_cardAtlas = &cardAtlas;
		_deckRotation = rotation;
		_deckScale = sf::Vector2f(scale, scale);
		_deck = deck;
		_angle = sf::Angle(sf::degrees(calculateAngle(_startPos, _endPos)));
		_startPos = startPos;
		_endPos = endPos;
		_isRendering = true;
		_deckStyle = DeckStyle::FromPosition;
		update();
	}

// =============================================
// —≈““≈–€
// =============================================

	void DeckRenderer::setCardAtlas(sf::Texture& cardAtlas) {
		_cardAtlas = &cardAtlas;
		for (int i = 0; i <= _deck->topIndex(); i++) _cardRenders[i].setCardAtlas(*_cardAtlas);
	}

	void DeckRenderer::setDeck(const Deck* newDeck) {
		if (newDeck == nullptr) throw std::logic_error("DeckRenderer.setDeck: Unable to set deck - 'newDeck' is nullptr");
		_deck = newDeck;
		update();
	}

	void DeckRenderer::setAngle(sf::Angle angle) {
		_deckStyle = DeckStyle::FromAngleSpacing;
		_angle = angle;
		update();
	}

	void DeckRenderer::setStartPosition(sf::Vector2f startPos) {
		_startPos = startPos;
		update();
	}

	void DeckRenderer::setEndPosition(sf::Vector2f endPos) {
		_deckStyle = DeckStyle::FromPosition;
		_endPos = endPos;
		update();
	}

	void DeckRenderer::setPosition(sf::Vector2f startPos, sf::Vector2f endPos) {
		_deckStyle = DeckStyle::FromPosition;
		setStartPosition(startPos);
		setEndPosition(endPos);
		update();
	}

	void DeckRenderer::setSpacing(float spacing) {
		if (spacing < 0) throw std::invalid_argument("DeckRenderer.setSpacing: Invalid argument 'spacing' - must be > 0");
		_deckStyle = DeckStyle::FromAngleSpacing;
		_spacing = spacing;
		update();
	}

	void DeckRenderer::setRendering(bool isRendering) {
		_isRendering = isRendering;
	}

	void DeckRenderer::setDeckStyle(DeckStyle style) {
		if (style != DeckStyle::FromPosition &&
			style != DeckStyle::FromAngleSpacing)
		{
			throw std::invalid_argument("DeckRenderer.setDeckStyle: Invalid argument 'style' - must be entered correctly");
		}
		_deckStyle = style;
		update();
	}

// =============================================
// »«Ã≈Õ≈Õ»≈ Œ“Œ¡–¿∆≈Õ»ﬂ  ¿–“ ¬  ŒÀŒƒ≈
// =============================================

	void DeckRenderer::setCardsScale(float scale) {
		if (scale <= 0) {
			throw std::invalid_argument("DeckRenderer.setCardsScale: Invalid argument 'scale' - must be > 0");
		}
		_deckScale = sf::Vector2f(scale, scale);
		for (int i = 0; i < _cardRenders.size(); i++) {
			_cardRenders[i].setScale(_deckScale);
		}
	}

	void DeckRenderer::setCardsRotation(sf::Angle rotation) {
		_deckRotation = rotation;
		for (int i = 0; i < _cardRenders.size(); i++) {
			_cardRenders[i].setRotation(_deckRotation);
		}
	}

	void DeckRenderer::setCardsRandomRotation(std::mt19937& gen, float min, float max) {
		_deckRotation = sf::Angle(sf::degrees(0));
		std::uniform_real_distribution<float> distrib(min, max);

		for (int i = 0; i < _cardRenders.size(); i++) {
			_cardRenders[i].setRotation(sf::Angle(sf::degrees(distrib(gen))));
		}
	}

	void DeckRenderer::setCardsRandomRotation(float min, float max) {
		_deckRotation = sf::Angle(sf::degrees(0));
		std::mt19937 gen(std::random_device{}());
		std::uniform_real_distribution<float> distrib(min, max);

		for (int i = 0; i < _cardRenders.size(); i++) {
			_cardRenders[i].setRotation(sf::Angle(sf::degrees(distrib(gen))));
		}
	}

// =============================================
// √≈““≈–€
// =============================================

	const CardRenderer& DeckRenderer::getCardRender(int index) const {
		if (index >= _cardRenders.size() || index < 0) {
			throw std::out_of_range("DeckRenderer.getCardRender: 'index' out of range");
		}
		return _cardRenders[index];
	}

// =============================================
// Ã≈“Œƒ€ Œ“–»—Œ¬ »
// =============================================

	void DeckRenderer::draw(sf::RenderTarget& target) {
		if (_isRendering && _deck != nullptr && _cardAtlas != nullptr) {
			for (int i = 0; i < _cardRenders.size(); i++) {
				_cardRenders[i].draw(target);
			}
		}
	}

	void DeckRenderer::update() {
		if (_deck == nullptr) {
			throw std::logic_error("DeckRenderer.update: Unable to update - '_deck' is nullptr");
		}
		if (_cardAtlas == nullptr) {
			throw std::logic_error("DeckRenderer.update: Unable to update - '_cardAtlas' is nullptr");
		}

		if (!_cardRenders.is_empty()) _cardRenders.clear();
		TVector<sf::Vector2f> coords;
		if (_deckStyle == DeckStyle::FromPosition) {
			coords = getCoordinatesVectorFromPosition(_deck->topIndex() + 1, _startPos, _endPos);
			_spacing = spacingFromLength(_deck->topIndex() + 1, _startPos, _endPos);
		}
		if (_deckStyle == DeckStyle::FromAngleSpacing) {
			coords = getCoordinatesVectorFromAngle(_deck->topIndex() + 1, _startPos, _angle, _spacing);
			_endPos = coords[coords.size() - 1];
		}
		for (int i = 0; i < coords.size(); i++) {
			CardRenderer test(*_cardAtlas, &(_deck->getCard(i)), _deckScale, _deckRotation, coords[i]);
			_cardRenders.push_back(test);
		}
	}

// =============================================
// ¬€◊»—À≈Õ»≈ œŒÀﬂ _spacing, »—’Œƒﬂ »« Õ¿◊¿À‹ÕŒ… »  ŒÕ≈◊ÕŒ… œŒ«»÷»»  ¿–“ ¬  ŒÀŒƒ≈
// =============================================

	float DeckRenderer::spacingFromLength(int elements, sf::Vector2f startPos, sf::Vector2f endPos) {
		if (elements <= 1) return 0.f;
		else {
			float length = calculateLength(startPos, endPos);
			_spacing = length / (elements - 1);
		}
	}

// =============================================
// ‘”Õ ÷»» ¬€◊»—À≈Õ»ﬂ ”√À¿ » ƒÀ»Õ€, »—’Œƒﬂ »« Õ¿◊¿À‹ÕŒ… »  ŒÕ≈◊ÕŒ… œŒ«»÷»»
// =============================================

	float calculateAngle(sf::Vector2f startPos, sf::Vector2f endPos) {
		float dx = endPos.x - startPos.x;
		float dy = endPos.y - startPos.y;
		float angle_rad = std::atan2(dy, dx);
		float angle_deg = static_cast<float>(angle_rad * (180.0 / PI));
		return angle_deg;
	}

	float calculateLength(sf::Vector2f startPos, sf::Vector2f endPos) {
		float dx = endPos.x - startPos.x;
		float dy = endPos.y - startPos.y;
		return std::sqrt(dx * dx + dy * dy);
	}

// =============================================
//	‘”Õ ÷»», ¬Œ«¬–¿Ÿ¿ﬁŸ»≈ TVector<sf::Vector2f>	— –¿«Õ€Ã» ¿–√”Ã≈Õ“¿Ã»
// =============================================

	TVector<sf::Vector2f> getCoordinatesVectorFromAngle(int elements, sf::Vector2f startPos, sf::Angle angle, float spacing) {
		if (elements < 0) throw std::logic_error("getCoordinatesVectorFromAngle: Number of elements must >= 0");
		if (spacing < 0) throw std::invalid_argument("getCoordinatesVectorFromAngle: Invalid argument 'spacing' - must be > 0");
		TVector<sf::Vector2f> coordinatesVector;
		if (elements == 0 || elements == 1) {
			coordinatesVector.push_back(startPos);
		}
		else {
			float angle_rad = angle.asRadians();
			float dx = std::cos(angle_rad);
			float dy = std::sin(angle_rad);
			for (int i = 0; i < elements; i++) {
				float distance = i * spacing;
				coordinatesVector.push_back(sf::Vector2f(startPos.x + distance * dx, startPos.y + distance * dy));
			}
		}
		return coordinatesVector;
	}

	TVector<sf::Vector2f> getCoordinatesVectorFromPosition(int elements, sf::Vector2f startPos, sf::Vector2f endPos) {
		if (elements < 0) throw std::logic_error("getCoordinatesVectorFromPosition: Number of elements must >= 0");
		TVector<sf::Vector2f> coordinatesVector;

		sf::Angle angle(sf::degrees(calculateAngle(startPos, endPos)));
		float length = calculateLength(startPos, endPos);
		float dx = endPos.x - startPos.x;
		float dy = endPos.y - startPos.y;


		if (elements == 0 || elements == 1) {
			coordinatesVector.push_back(sf::Vector2f(startPos.x + dx * 0.5f, startPos.y + dy * 0.5f));
		}
		else {
			float dx = endPos.x - startPos.x;
			float dy = endPos.y - startPos.y;

			float stepX = dx / (elements - 1);
			float stepY = dy / (elements - 1);

			for (int i = 0; i < elements; i++) {
				coordinatesVector.push_back(sf::Vector2f(startPos.x + i * stepX, startPos.y + i * stepY));
			}
		}
		return coordinatesVector;
	}
}
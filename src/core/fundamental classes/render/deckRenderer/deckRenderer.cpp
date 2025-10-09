#include "deckRenderer.h"

namespace WGP {
	// Constructors

	deckRenderer::deckRenderer() :
		_cardAtlas(nullptr),
		_deck(nullptr),
		_startPos(sf::Vector2f(OUT_OF_BOUNDS, OUT_OF_BOUNDS)),
		_endPos(sf::Vector2f(OUT_OF_BOUNDS, OUT_OF_BOUNDS)),
		_angle(sf::Angle(sf::degrees(0))),
		_spacing(0.f),
		_deckRotation(sf::degrees(0)),
		_deckScale(sf::Vector2f(1.f, 1.f)),
		_isRendering(false)
	{
	}

	deckRenderer::deckRenderer(sf::Texture& cardAtlas, deck* deck, sf::Vector2f position) :
		_cardAtlas(&cardAtlas),
		_startPos(position),
		_endPos(position),
		_angle(sf::Angle(sf::degrees(0))),
		_spacing(0.f),
		_deckRotation(sf::degrees(0)),
		_deckScale(sf::Vector2f(1.f, 1.f))
	{
		setDeck(deck);
		setRendering(true);
		for (int i = 0; i <= _deck->topIndex(); i++) {
			_cardRenders.push_back(cardRenderer(*_cardAtlas, &(_deck->getCard(i)), _deckScale, _deckRotation, position));
		}
	}

	deckRenderer::deckRenderer(sf::Texture& cardAtlas, deck* deck, sf::Vector2f startPos, sf::Angle angle, float spacing) :
		_cardAtlas(&cardAtlas),
		_startPos(startPos),
		_angle(angle),
		_deckRotation(sf::degrees(0)),
		_deckScale(sf::Vector2f(1.f, 1.f))
	{
		setDeck(deck);
		setSpacing(spacing);
		setRendering(true);
		TVector<sf::Vector2f> coords = getCoordinatesVectorFromAngle(_deck->topIndex() + 1, _startPos, _angle, _spacing);
		for (int i = 0; i < coords.size(); i++) {
			_cardRenders.push_back(cardRenderer(*_cardAtlas, &(_deck->getCard(i)), 1.f, sf::Angle(sf::degrees(0)), coords[i]));
		}
		_endPos = coords[coords.size() - 1];
	}

	deckRenderer::deckRenderer(sf::Texture& cardAtlas, deck* deck, sf::Vector2f startPos, sf::Vector2f endPos) :
		_cardAtlas(&cardAtlas),
		_startPos(startPos),
		_endPos(endPos),
		_deckRotation(sf::degrees(0)),
		_deckScale(sf::Vector2f(1.f, 1.f))
	{
		setDeck(deck);
		setRendering(true);

		_angle = sf::Angle(sf::degrees(calculateAngle(_startPos, _endPos)));
		float length = calculateLength(_startPos, _endPos);
		_spacing = length / (_deck->topIndex());
		TVector<sf::Vector2f> coords = getCoordinatesVectorFromPosition(_deck->topIndex() + 1, _startPos, _endPos);
		for (int i = 0; i < coords.size(); i++) {
			_cardRenders.push_back(cardRenderer(*_cardAtlas, &(_deck->getCard(i)), 1.f, sf::Angle(sf::degrees(0)), coords[i]));
		}
	}

	// Setters

	void deckRenderer::setCardAtlas(sf::Texture& cardAtlas) {
		_cardAtlas = &cardAtlas;
		for (int i = 0; i <= _deck->topIndex(); i++) _cardRenders[i].setCardAtlas(*_cardAtlas);
		update();
	}

	void deckRenderer::setDeck(deck* newDeck) {
		if (newDeck == nullptr) throw std::logic_error("deckRenderer.setDeck: Unable to set deck - 'newDeck' is nullptr");
		_deck = newDeck;
		update();
	}

	void deckRenderer::setAngle(sf::Angle angle) {
		_angle = angle;
		update();
	}

	void deckRenderer::setStartPosition(sf::Vector2f startPos) {
		_startPos = startPos;
		update();
	}

	void deckRenderer::setEndPosition(sf::Vector2f endPos) {
		_endPos = endPos;
		update();
	}

	void deckRenderer::setPosition(sf::Vector2f startPos, sf::Vector2f endPos) {
		setStartPosition(startPos);
		setEndPosition(endPos);
		update();
	}

	void deckRenderer::setSpacing(float spacing) {
		if (spacing < 0) throw std::invalid_argument("deckRenderer.setSpacing: Invalid argument 'spacing' - must be > 0");
		_spacing = spacing;
		update();
	}

	void deckRenderer::setRendering(bool isRendering) {
		if (_deck->isEmpty() || _deck == nullptr || _cardAtlas == nullptr) _isRendering = false;
		else _isRendering = isRendering;
	}

	// Visualization functions

	void deckRenderer::draw(sf::RenderTarget& target) {
		if (_isRendering && _deck != nullptr && _cardAtlas != nullptr) {
			for (int i = 0; i < _cardRenders.size(); i++) {
				_cardRenders[i].draw(target);
			}
		}
	}

	void deckRenderer::update() {
		if (_deck == nullptr) {
			throw std::logic_error("deckRenderer.update: Unable to update - '_deck' is nullptr");
		}
		if (_cardAtlas == nullptr) {
			throw std::logic_error("deckRenderer.update: Unable to update - '_cardAtlas' is nullptr");
		}
		_cardRenders.clear();
		setRendering(true);

		if (_deck->topIndex() == 0) {
			_endPos = _startPos;
			_cardRenders.push_back(cardRenderer(*_cardAtlas, &(_deck->getCard(0)), _deckScale, _deckRotation, _startPos));
		}
		else {
			float angle_rad = _angle.asRadians();
			float dx = std::cos(angle_rad);
			float dy = std::sin(angle_rad);
			for (int i = 0; i <= _deck->topIndex(); i++) {
				float distance = i * _spacing;
				_cardRenders.push_back(cardRenderer(*_cardAtlas, &(_deck->getCard(i)), _deckScale, _deckRotation, sf::Vector2f(_startPos.x + distance * dx, _startPos.y + distance * dy)));
			}
			float totalDistance = (_deck->topIndex()) * _spacing;
			_endPos = sf::Vector2f(_startPos.x + totalDistance * dx, _startPos.y + totalDistance * dy);
		}
	}

	// Actions with cards

	void deckRenderer::setCardsScale(float scale) {
		if (scale <= 0) {
			throw std::invalid_argument("deckRenderer.setCardsScale: Invalid argument 'scale' - must be > 0");
		}
		_deckScale = sf::Vector2f(scale, scale);
		for (int i = 0; i < _cardRenders.size(); i++) {
			_cardRenders[i].setScale(_deckScale);
		}
	}

	void deckRenderer::setCardsRotation(sf::Angle rotation) {
		_deckRotation = rotation;
		for (int i = 0; i < _cardRenders.size(); i++) {
			_cardRenders[i].setRotation(_deckRotation);
		}
	}

	// Getters

	sf::Angle deckRenderer::getAngle() const {
		return _angle;
	}

	sf::Vector2f deckRenderer::getStartPosition() const {
		return _startPos;
	}

	sf::Vector2f deckRenderer::getEndPosition() const {
		return _endPos;
	}

	float deckRenderer::getSpacing() const {
		return _spacing;
	}

	bool deckRenderer::isRendering() const {
		return _isRendering;
	}

	sf::Angle deckRenderer::getCardsRotation() const {
		return _deckRotation;
	}

	sf::Vector2f deckRenderer::getCardsScale() const {
		return _deckScale;
	}

	// Supportive functions

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

	TVector<sf::Vector2f> getCoordinatesVectorFromAngle(int elements, sf::Vector2f startPos, sf::Angle angle, float spacing) {
		if (elements <= 0) throw std::logic_error("getCoordinatesVectorFromAngle: Number of elements must > 0");
		if (spacing < 0) throw std::invalid_argument("getCoordinatesVectorFromAngle: Invalid argument 'spacing' - must be > 0");
		TVector<sf::Vector2f> coordinatesVector;
		if (elements == 1) {
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
		if (elements <= 0) throw std::logic_error("getCoordinatesVectorFromPosition: Number of elements must > 0");
		TVector<sf::Vector2f> coordinatesVector;

		sf::Angle angle(sf::degrees(calculateAngle(startPos, endPos)));
		float length = calculateLength(startPos, endPos);
		float dx = endPos.x - startPos.x;
		float dy = endPos.y - startPos.y;

		if (elements == 1) {
			coordinatesVector.push_back(sf::Vector2f(startPos.x + dx * 0.5f, startPos.y + dy * 0.5f));
		}
		else {
			int spacing = static_cast<int>(length / (elements - 1));
			float unit_dx = dx / length;
			float unit_dy = dy / length;

			for (int i = 0; i < elements; i++) {
				float t = static_cast<float>(i * spacing);
				coordinatesVector.push_back(sf::Vector2f(startPos.x + t * unit_dx, startPos.y + t * unit_dy));
			}
		}

		return coordinatesVector;
	}
}
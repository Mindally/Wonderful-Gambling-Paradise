# Changelog

Все изменения, которые я делаю с проектом я буду документировать в этом файле.

## [Version: alpha 0.0.4] - 09.10.2025

### Изменения

- Переименовал класс card_field в klondikeField.
- Переименовал класс cardFieldRenderer в klondikeFieldRenderer.
- Переписал класс klondikeField с использованием TVector<deck> вместо простого массива.
- Добавил константность необходимым методам для классов: card, deck, klondikeField.
- Исправил ошибку в deckRenderer.setCardAtlas
- Исправил 'warning' компилятора для классов: TVector, deck, deckRenderer.
- Заменил во всех классах enum на enum class
- Добавил для всех моих классов namespace 'WGP'
- В старых классах card, deck и klondikeField изменил стиль названия с snake_case на camelCase

## [Version: alpha 0.0.4.1] - 10.10.2025

### Изменения

- добавил функции setCardsRandomRotation для класса deckRenderer.
- добавил функцию flip для класса deck.
- переделал функцию openCardFromStock так, чтобы в _stockPile хранились только FaceDown карты, а в _wastePile только FaceUp.
- переделал логику update у класса cardRenderer так, чтобы при каждом  draw не вызывался update, а только когда необходимо.
- переделал функцию update у класса deckRenderer, заменив вычисления на функцию getCoordinatesVectorFromAngle.
- переделал конструкторы класса deckRenderer так, чтобы инициализация полей проходила не в сторонних функциях, а в теле конструктора.
- переделал функции рандома класса card с использованием std::mt19937.
- Добавил классу deckRenderer стиль колоды (FromPosition, FromAngleSpacing) для корректного изменения характеристик расположения колоды.
- Добавил метод initialize классу cardRenderer, который инициализирует поля класса из одной функции.
- Добавил методы initializeFromAngle и initializeFromPosition классу deckRenderer, которые инициализируют все поля класса из одной функции.
- Добавил метод spacingFromLength класса deckRenderer.

## [Version: alpha 0.0.4.2] - 13.10.2025

### Изменения

- добавил текст поверх _stockPileRender, который отражает количество карт, которое осталось в _stockPile.
- добавил много вспомогательных методов.
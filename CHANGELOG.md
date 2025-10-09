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
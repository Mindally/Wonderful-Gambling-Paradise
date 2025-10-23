# Changelog

Все изменения, которые я делаю с проектом я буду документировать в этом файле.

## [ВЕРСИЯ: Альфа 0.0.4] - 09.10.2025

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

## [ВЕРСИЯ: Альфа 0.0.4.1] - 10.10.2025

### Изменения

- Добавил функции setCardsRandomRotation для класса deckRenderer.
- Добавил функцию flip для класса deck.
- Переделал функцию openCardFromStock так, чтобы в _stockPile хранились только FaceDown карты, а в _wastePile только FaceUp.
- Переделал логику update у класса cardRenderer так, чтобы при каждом  draw не вызывался update, а только когда необходимо.
- Переделал функцию update у класса deckRenderer, заменив вычисления на функцию getCoordinatesVectorFromAngle.
- Переделал конструкторы класса deckRenderer так, чтобы инициализация полей проходила не в сторонних функциях, а в теле конструктора.
- Переделал функции рандома класса card с использованием std::mt19937.
- Добавил классу deckRenderer стиль колоды (FromPosition, FromAngleSpacing) для корректного изменения характеристик расположения колоды.
- Добавил метод initialize классу cardRenderer, который инициализирует поля класса из одной функции.
- Добавил методы initializeFromAngle и initializeFromPosition классу deckRenderer, которые инициализируют все поля класса из одной функции.
- Добавил метод spacingFromLength класса deckRenderer.

## [ВЕРСИЯ: Альфа 0.0.4.2] - 13.10.2025

### Изменения

- добавил текст поверх _stockPileRender, который отражает количество карт, которое осталось в _stockPile.
- обновил каталог папок resources и поменял klondike.png.
- добавил много вспомогательных методов.

## [ВЕРСИЯ: Альфа 0.0.4.3] - 18.10.2025

### Изменения

- Привёл все классы к единому стилю оформления.
- Переименовал namespace 'WGP' в 'wgp'.
- Добавил вложенный в namespace 'wgp' namespace 'klondike' для классов, работающих с Косынкой.
- Переименовал все классы, чтобы они назывались с большой буквы.
- Переименовал классы KlondikeField в Field, KlondikeFieldRenderer в FieldRenderer, Klondike в Game, так как для отличия был добавлен namespace 'klondike'.
- Переписал комментарии на русский язык.
- Добавил namespace 'solitaire' для общий классов Пасьянсов.
- Добавил класс solitaire::CardPosition как хранилище позиции карт на поле.
- Переписал класс klondike::Field, используя solitaire::CardPosition вместо int аргументов.
- Добавил методы классу Card: isRed(), isBlack() - проверяют цвет масти и возвращают bool, isFaceCard - проверяет является ли карта Вальтом, Дамой или Королём и возвращает bool.
- Добавил методы сравнения значений двух карт (ранг, масть): compareByRank(const Card&, const Card&), compareBySuit(const Card&, const Card&)
для дальнейшей реализации метода сортировки у класса Deck.
- Добавил классы без реализации для игры "tricky dungeon"
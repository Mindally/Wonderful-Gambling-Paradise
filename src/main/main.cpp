#include <SFML/Graphics.hpp>

#include "../core/model/card/Card.hpp"
#include "../core/view/card_renderer/CardRenderer.hpp"
#include "../core/model/deck/Deck.hpp"
#include "../core/view/deck_renderer/DeckRenderer.hpp"

#include "../games/solitaire/klondike/field/Field.hpp"
#include "../games/solitaire/klondike/field_renderer/FieldRenderer.hpp"

#include "../games/tricky_dungeon/card_position/CardPosition.hpp"
#include "../games/tricky_dungeon/card_position/CardPositionPresets.hpp"
#include "../games/tricky_dungeon/field/Field.hpp"

#include "constants.hpp"

//#define DECK_TESTING
#ifdef DECK_TESTING


int main()
{
    try {
        sf::RenderWindow window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), GAME_TITLE, sf::Style::Titlebar | sf::Style::Close);
        window.setFramerateLimit(60);
        sf::Texture defaultCardAtlas;
        if (!defaultCardAtlas.loadFromFile("../../../resources/textures/default/card.png")) return -1;
        defaultCardAtlas.setSmooth(false);

        sf::Texture customCardAtlas;
        if (!customCardAtlas.loadFromFile("../../../resources/textures/customizable/card.png")) return -2;
        customCardAtlas.setSmooth(false);

        WGP::deck testDeck;
        //WGP::deckRenderer testDeckRenderer(defaultCardAtlas, &testDeck, sf::Vector2f(200.f, 200.f), sf::Angle(sf::degrees(90)), 26);
        WGP::deckRenderer testDeckRenderer(defaultCardAtlas, &testDeck, sf::Vector2f(200.f, 200.f), sf::Vector2f(800, 200));

        float i = 0;
        sf::Angle testAngle(sf::degrees(i));
        float j = 1;
        bool lever1 = true;
        bool lever2 = false;
        float padding = 26;
        while (window.isOpen())
        {
            while (const std::optional event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                    window.close();

                if (event->is<sf::Event::KeyPressed>()) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) { // Поворот карт по часовой стрелке
                        i++;
                        testAngle = sf::degrees(i * 15);
                        testDeckRenderer.setCardsRotation(testAngle);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) { // Уменьшение размера
                        j -= 0.04;
                        testDeckRenderer.setCardsScale(j);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) { // Увеличение размера
                        j += 0.04;
                        testDeckRenderer.setCardsScale(j);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F)) { // Удаление карты
                        testDeck.erase();
                        testDeckRenderer.update();
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H)) { // Добавление карты
                        WGP::card test("H2U");
                        test.setRandom();
                        testDeck.append(test);
                        testDeckRenderer.update();
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G)) { // Изменение атласа карт
                        if (lever1) {
                            testDeckRenderer.setCardAtlas(customCardAtlas);
                            lever1 = false;
                        }
                        else {
                            testDeckRenderer.setCardAtlas(defaultCardAtlas);
                            lever1 = true;
                        }
                    }


                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) { // Изменение стиля deckRenderer
                        if (lever2) {
                            testDeckRenderer.setDeckStyle(WGP::DeckStyle::FromPosition);
                            lever2 = false;
                        }
                        else {
                            testDeckRenderer.setDeckStyle(WGP::DeckStyle::FromAngleSpacing);
                            lever2 = true;
                        }
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) { // Уменьшение угла размещения карт
                        i--;
                        testDeckRenderer.setAngle(sf::degrees(i * 15));
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) { // Увеличение угла размещения карт
                        i++;
                        testDeckRenderer.setAngle(sf::degrees(i * 15));
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C)) { // Уменьшение spacing
                        padding--;
                        testDeckRenderer.setSpacing(padding);
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::V)) { // Увеличение spacing
                        padding++;
                        testDeckRenderer.setSpacing(padding);
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O)) {
                        testDeckRenderer.setCardsRotation(sf::Angle(sf::degrees(0)));
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) {
                        testDeckRenderer.setCardsRandomRotation(-360.f, 360.f);
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L)) {
                        testDeck.flip();
                        testDeckRenderer.update();
                    }
                }

            }
            window.clear(POKER_GREEN);
            testDeckRenderer.draw(window);
            window.display();

        }

    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}

#endif // DECK_TESTING

#define KLONDIKE_TESTING
#ifdef KLONDIKE_TESTING

void consolePrint(wgp::klondike::Field& field) {
    system("cls");
    field.print();
}

int main()
{
    try {
        sf::RenderWindow window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), GAME_TITLE, sf::Style::Titlebar | sf::Style::Close);
        window.setFramerateLimit(60);
        sf::Texture defaultCardAtlas;
        if (!defaultCardAtlas.loadFromFile("../../../resources/default/textures/card.png")) return -1;
        defaultCardAtlas.setSmooth(false);

        sf::Texture KlondikeAtlas;
        if (!KlondikeAtlas.loadFromFile("../../../resources/default/textures/klondike.png")) return -2;
        KlondikeAtlas.setSmooth(false);

        sf::Font font;
        if (!font.openFromFile("../../../resources/default/fonts/VCR_OSD_MONO.ttf")) return -3;
        font.setSmooth(false);

        wgp::klondike::Field testField;
        // sf::Texture& cardAtlas, sf::Texture& klondikeAtlas, klondikeField* field, float scale, float cardsSpacing, float colSpacing, float rowSpacing, sf::Vector2f startPos
        wgp::klondike::FieldRenderer testFieldRender(defaultCardAtlas, KlondikeAtlas, &testField, font, 1.f, 24.f, 80.f, 120.f, sf::Vector2f(60.f, 80.f));

        while (window.isOpen())
        {
            while (const std::optional event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                    window.close();
                if (event->is<sf::Event::KeyPressed>()) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O)) { // Открыть карту из Stock
                        testField.openCardFromStock();
                        testFieldRender.update();
                        consolePrint(testField);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) { // Напечатать поле в консоли
                        consolePrint(testField);
                        //std::cout << testFieldRender.getEndPosition().x << " " << testFieldRender.getEndPosition().y << std::endl;
                    }
                }
            }
            window.clear(POKER_GREEN);
            testFieldRender.draw(window);
            window.display();
        }

    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

#endif // KLONDIKE_TESTING

//#define TRICKY_DUNGEON_TESTING
#ifdef TRICKY_DUNGEON_TESTING

void consolePrint(wgp::klondike::Field& field) {
    system("cls");
    field.print();
}

int main()
{
    try {
        std::random_device rd;
        std::mt19937 gen(rd());
        wgp::tricky_dungeon::Field testField(gen);
        std::string input;
        while (true) {
            system("cls");
            testField.print();
            std::cout << "Enter command: ";
            std::cin >> input;

            if (input.empty()) continue;

            int room = -1;
            if (input.length() > 1 && isdigit(input[1])) {
                room = input[1] - '0';
            }

            switch (input[0]) {
            case 'o': testField.openFromDungeonToRoom(); break;
            case 's': testField.skipRoom(); break;
            case 'd': testField.testDiscard(); break; // Для теста

            case 'e': case 'b': case 'f': case 'h':
                if (room >= 0 && room <= 3) {
                    auto roomObj = wgp::tricky_dungeon::room(room);
                    switch (input[0]) {
                    case 'e': testField.equipWeapon(roomObj); break;
                    case 'b': testField.fightMonster(roomObj, true); break;
                    case 'f': testField.fightMonster(roomObj, false); break;
                    case 'h': testField.useHealingPotion(roomObj); break;
                    }
                }
                break;
            }
        }
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

#endif // TRICKY_DUNGEON_TESTING
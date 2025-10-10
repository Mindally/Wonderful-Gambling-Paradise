#include <SFML/Graphics.hpp>

#include "../core/fundamental classes/logic/card/card.h"
#include "../core/fundamental classes/render/cardRenderer/cardRenderer.h"
#include "../core/fundamental classes/logic/deck/deck.h"
#include "../core/fundamental classes/render/deckRenderer/deckRenderer.h"
#include "../games/solitaire/klondike/klondikeField/klondikeField.h"
#include "../games/solitaire/klondike/klondike/klondike_console.h"

#include "constants.h"

int main()
{
    try {
        sf::RenderWindow window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), GAME_TITLE, sf::Style::Titlebar | sf::Style::Close);
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
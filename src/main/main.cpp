#include <SFML/Graphics.hpp>

#include "../core/fundamental classes/logic/card/card.h"
#include "../core/fundamental classes/render/cardRenderer/cardRenderer.h"
#include "../core/fundamental classes/logic/deck/deck.h"
#include "../core/fundamental classes/render/deckRenderer/deckRenderer.h"
#include "../games/solitaire/klondike/cardField/card_field.h"
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

        deck testDeck;
        deckRenderer testDeckRenderer(defaultCardAtlas, &testDeck, sf::Vector2f(200.f, 200.f), sf::Angle(sf::degrees(90)), 26);


        int i = 0;
        sf::Angle testAngle(sf::degrees(i));
        float j = 1;
        bool lever = true;
        float padding = 26;
        while (window.isOpen())
        {
            while (const std::optional event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                    window.close();

                if (event->is<sf::Event::KeyPressed>()) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
                        i++;
                        testAngle = sf::degrees(i * 15);
                        testDeckRenderer.setCardsRotation(testAngle);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
                        j -= 0.04;
                        testDeckRenderer.setCardsScale(j);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
                        j += 0.04;
                        testDeckRenderer.setCardsScale(j);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F)) {
                        testDeck.erase();
                        testDeckRenderer.update();
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H)) {
                        testDeck.append(card("SA1"));
                        testDeckRenderer.update();
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G)) {
                        if (lever) {
                            testDeckRenderer.setCardAtlas(customCardAtlas);
                            lever = false;
                        }
                        else {
                            testDeckRenderer.setCardAtlas(defaultCardAtlas);
                            lever = true;
                        }
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
                        i--;
                        testDeckRenderer.setAngle(sf::degrees(i * 15));
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) {
                        i++;
                        testDeckRenderer.setAngle(sf::degrees(i * 15));
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C)) {
                        padding--;
                        testDeckRenderer.setSpacing(padding);
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::V)) {
                        padding++;
                        testDeckRenderer.setSpacing(padding);
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
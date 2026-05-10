#pragma once
#include <SFML/Graphics.hpp>
#include <string>



inline std::string sfmlInput(sf::RenderWindow& window,
    sf::Font& font,
    const std::string& message,
    int               maxLen = 500)
{
    std::string input;

    sf::Color BG{ 15,  20,  35 };
    sf::Color PANEL{ 25,  32,  55 };
    sf::Color ACCENT{ 72, 149, 239 };
    sf::Color TEXT_COL{ 230, 235, 245 };
    sf::Color SUB_COL{ 130, 140, 165 };
    sf::Color INPUT_BG{ 35,  44,  68 };

    float winW = static_cast<float>(window.getSize().x);
    float winH = static_cast<float>(window.getSize().y);

    float boxW = std::min(winW - 80.f, 500.f);
    float boxH = 160.f;
    float boxX = (winW - boxW) / 2.f;
    float boxY = (winH - boxH) / 2.f;

    sf::Clock blinkClock;
    bool cursorVisible = true;

    while (window.isOpen())
    {
        if (blinkClock.getElapsedTime().asSeconds() >= 0.5f)
        {
            cursorVisible = !cursorVisible;
            blinkClock.restart();
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return "";
            }

            if (event.type == sf::Event::TextEntered)
            {
                uint32_t ch = event.text.unicode;

                if (ch == '\b')                              // backspace
                {
                    if (!input.empty()) input.pop_back();
                }
                else if (ch == '\r' || ch == '\n')          // Enter → done
                {
                    return input;
                }
                else if (ch >= 32 && ch < 127)              // printable ASCII
                {
                    if ((int)input.size() < maxLen)
                        input += static_cast<char>(ch);
                }
            }
        }

        window.clear(sf::Color(10, 14, 26));

        sf::RectangleShape overlay({ winW, winH });
        overlay.setFillColor(sf::Color(0, 0, 0, 160));
        window.draw(overlay);

        sf::RectangleShape card({ boxW, boxH });
        card.setPosition(boxX, boxY);
        card.setFillColor(PANEL);
        card.setOutlineThickness(1.f);
        card.setOutlineColor(ACCENT);
        window.draw(card);

        sf::RectangleShape bar({ boxW, 3.f });
        bar.setPosition(boxX, boxY);
        bar.setFillColor(ACCENT);
        window.draw(bar);

        sf::Text prompt(message, font, 16u);
        prompt.setFillColor(TEXT_COL);
        prompt.setPosition(boxX + 20.f, boxY + 20.f);
        window.draw(prompt);

        sf::Text hint("Press Enter to confirm", font, 12u);
        hint.setFillColor(SUB_COL);
        hint.setPosition(boxX + 20.f, boxY + 44.f);
        window.draw(hint);

        float ibX = boxX + 20.f;
        float ibY = boxY + 75.f;
        float ibW = boxW - 40.f;
        float ibH = 40.f;

        sf::RectangleShape inputBox({ ibW, ibH });
        inputBox.setPosition(ibX, ibY);
        inputBox.setFillColor(INPUT_BG);
        inputBox.setOutlineThickness(1.5f);
        inputBox.setOutlineColor(ACCENT);
        window.draw(inputBox);

        std::string displayed = input + (cursorVisible ? "|" : " ");
        sf::Text typed(displayed, font, 17u);
        typed.setFillColor(TEXT_COL);
        typed.setPosition(ibX + 10.f, ibY + 9.f);
        window.draw(typed);

        window.display();
    }

    return input;
}
#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

inline string displaySlotsSFML(string slots[], int count)
{
    sf::Texture blurr;
    blurr.loadFromFile("imageblurr.png");

    sf::Sprite bgSprite;
    bgSprite.setTexture(blurr);

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::Vector2u texSize = blurr.getSize();

    bgSprite.setScale(
        (float)desktop.width / texSize.x,
        (float)desktop.height / texSize.y
    );

    sf::RenderWindow window(
        sf::VideoMode::getDesktopMode(),
        "Available Slots",
        sf::Style::Fullscreen
    );

    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");

    sf::Text title;
    title.setFont(font);
    title.setString("Select Time Slot");
    title.setCharacterSize(34);
    title.setFillColor(sf::Color::White);
    title.setPosition(100, 60);

    sf::RectangleShape boxes[50];
    sf::Text texts[50];

    for (int i = 0; i < count; i++)
    {
        boxes[i].setSize(sf::Vector2f(400, 50));
        boxes[i].setPosition(100, 150 + i * 70);

        boxes[i].setFillColor(sf::Color(40, 40, 40));
        boxes[i].setOutlineThickness(2);
        boxes[i].setOutlineColor(sf::Color::White);

        texts[i].setFont(font);
        texts[i].setString(slots[i]);
        texts[i].setCharacterSize(24);
        texts[i].setFillColor(sf::Color::White);

        texts[i].setPosition(
            120,
            160 + i * 70
        );
    }

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return "";
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f mousePos =
                        window.mapPixelToCoords(
                            sf::Mouse::getPosition(window)
                        );

                    for (int i = 0; i < count; i++)
                    {
                        if (boxes[i].getGlobalBounds().contains(mousePos))
                        {
                            window.close();

                            return slots[i];
                        }
                    }
                }
            }
        }

        sf::Vector2f mousePos =
            window.mapPixelToCoords(
                sf::Mouse::getPosition(window)
            );

        for (int i = 0; i < count; i++)
        {
            if (boxes[i].getGlobalBounds().contains(mousePos))
            {
                boxes[i].setFillColor(sf::Color(70, 120, 255));
            }
            else
            {
                boxes[i].setFillColor(sf::Color(40, 40, 40));
            }
        }

        window.clear(sf::Color(20, 20, 20));
        window.draw(bgSprite);
        window.draw(title);

        for (int i = 0; i < count; i++)
        {
            window.draw(boxes[i]);
            window.draw(texts[i]);
        }

        window.display();
    }

    return "";
}